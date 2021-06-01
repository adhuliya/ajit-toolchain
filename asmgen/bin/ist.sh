#!/usr/bin/env bash

# BASH script to run the tests for AJIT insns.
#
# (C) Abhijat Vichare, 2021

#####
# The basic idea is quite simple.  We have a python (3.x) program that
# reads in  the CSV database  of SPARC  + AJIT instructions  and their
# format details, and generates the opcodes in hexadecimal and binary,
# and also the  ASM instruction.  This program is  exhaustive in terms
# of the  various combinations of  operations and the  arguments.  (At
# times it may generate invalid instruction combinations too.)
# 
# This  program can  be run  in various  modes.  In  particular it  is
# possible to generate all combinations of a specific instruction.  We
# use this mode.  We have a list of all the SPARC and AJIT operations.
#####

function print_sym_val ()
{
    local sym=$1
    local val=${!sym}           # Use one level of indirection in bash.
    local cmt=$2

    pval=$(make_compact_dir_names $val)
    
    printf "%-25s : %-15s : %s\n" "${cmt}" ${sym} "${pval}"
}

function make_compact_dir_names ()
{
    local val=$1

    local pval=
    local rhome=$(echo $RUNDIR | sed -e "s/\//\\\\\//g")
    local ahome=$(echo $ASMGENTOPDIR | sed -e "s/\//\\\\\//g")
    local bhome=$(echo $AJITTOOLSTOPDIR | sed -e "s/\//\\\\\//g")
    local chome=$(echo $AJITTOOLSBINDIR | sed -e "s/\//\\\\\//g")

    pval=$(echo $val | sed -e "s/${rhome}/\${RUNDIR}/g"         | \
                       sed -e "s/${ahome}/\${ASMGENTOPDIR}/g"   | \
                       sed -e "s/${chome}/\${AJITTOOLSBINDIR}/g"| \
                       sed -e "s/${bhome}/\${AJITTOOLSTOPDIR}/g")
    
    echo $pval
}

function setup ()
{
    MASTERTOPDIR=/lindata/My-work/Professional/iitb/development
    BRANCHTOPDIR=${MASTERTOPDIR}/isa-v2-branch
    ASMGENTOPDIR=${BRANCHTOPDIR}/ajit-toolchain/as-dis-test/asmgen
    ASMGENBINDIR=${ASMGENTOPDIR}/bin
    ASMGENSRCDIR=${ASMGENTOPDIR}/code/python
    ASMGENDATADIR=${ASMGENTOPDIR}/data
    ASMGENRUNDIR=${ASMGENTOPDIR}/runs

    AJITTOOLSTOPDIR=${MASTERTOPDIR}/../build/buildroot-2014.08
    AJITTOOLSOUTDIR=${AJITTOOLSTOPDIR}/output/host
    AJITTOOLSBINDIR=${AJITTOOLSOUTDIR}/usr/bin
    AJITTOOLSPREFIX=sparc-buildroot-linux-uclibc

    # Tools
    # Insn generator tool
    INSNGEN=${ASMGENSRCDIR}/opcode-generator.py
    ASMTOOL=${AJITTOOLSBINDIR}/${AJITTOOLSPREFIX}-as
    ASMTOOLARGS=-Av8
    ODTOOL=${AJITTOOLSBINDIR}/${AJITTOOLSPREFIX}-objdump
    ODTOOLARGS="-d -z"

    # Data files
    INSNLST=${ASMGENDATADIR}/the-insns.lst
    INSNDATA=${ASMGENDATADIR}/all-insns.csv
    INSNFMTS=${ASMGENDATADIR}/all-formats.csv

    # Colour variables
    RED="\033[1;31m"
    GREEN="\033[1;32m"
    NOCOLOR="\033[0m"
    GREENONYELLOW="\033[1;32;1;43m"
    YELLOWONRED="\033[1;33;0;41m"
    YELLOWONGREEN="\033[1;33;1;42m"
    REDONGREEN="\033[1;31;1;42m"

    OKCOLOR=${GREENONYELLOW}
    FAILCOLOR=${YELLOWONRED}
    RUNCOLOR=${REDONGREEN}
    OKMESG="${OKCOLOR}[ OK ]${NOCOLOR}"
    FAILMESG="${FAILCOLOR}[FAIL]${NOCOLOR}"
    DONEMESG="${OKCOLOR}[Done]${NOCOLOR}"
    BLDERRMESG="${FAILCOLOR}[Build ERROR]${NOCOLOR}"
    CPERRMESG="${FAILCOLOR}[Copy ERROR]${NOCOLOR}"

    # Processing states of the script
    DOLISTINSTRUCTIONS=0
    DOINSNEXPANSION=0
    DOASMGENERATION=0
    DOOBJGENERATION=0
    DODISASMGENERATION=0
    DOCOMPARISON=0
    DOGETFOLDER=""
    
    # Misc. variables
    STARTTIME=
    ENDTIME=

    RUNDATE=$(date +%A-%B-%d-%Y-%H-%M-%S)
    RUNDIR=${ASMGENRUNDIR}/${RUNDATE}

    # Now do the main setup
    process_options $*
    RUNLOG=${RUNDIR}/run.log
    
    STARTTIME=$(date +%s)
    [ ! -d ${RUNDIR} ] && mkdir -p ${RUNDIR}
}

function process_options ()
{
    local args=$*
    local optstr="r:vhliaodc"
    local argvar                # where we collect the argument

    printf "II == %-40s: \"%s\" : " "Processing command line" "$args"
    DOLISTINSTRUCTIONS=1
    DOINSNEXPANSION=1
    DOASMGENERATION=1
    DOOBJGENERATION=1
    DODISASMGENERATION=1
    DOCOMPARISON=1
    DOGETFOLDER=""

    # Option      Meaning
    # h           Help
    # l           Stop after listing instructions
    # i           Stop after expanding instructions
    # a           Stop after ASM generation
    # o           Stop after assembling files to OBJ files
    # d           Stop after disassembling OBJ files
    # c           Stop after comparing
    while getopts $optstr argvar $args
    do
        case $argvar in
            "h") script_help;              exit;;
            "l") DOLISTINSTRUCTIONS=0; mesg="${mesg} list instructions,"; continue;;
            "i") DOINSNEXPANSION=0;    mesg="${mesg} expand instructions,"; continue;;
            "a") DOASMGENERATION=0;    mesg="${mesg} generate ASM code,"; continue;;
            "o") DOOBJGENERATION=0;    mesg="${mesg} assemble to object code,"; continue;;
            "d") DODISASMGENERATION=0; mesg="${mesg} disassemble the object code,"; continue;;
            "c") DOCOMPARISON=0;       mesg="${mesg} compare all,"; continue;;
            "r") DOGETFOLDER=$OPTARG;  mesg="${mesg} using folder: ${DOGETFOLDER},"; continue;;
            *) printf "Unknown option: %s\n" $OPTARG; exit;;
        esac
    done
    
    mesg="Will: "
    [ $DOLISTINSTRUCTIONS ==  1  ] && mesg="${mesg} list instructions,"
    [ $DOINSNEXPANSION    ==  1  ] && mesg="${mesg} expand instructions,"
    [ $DOASMGENERATION    ==  1  ] && mesg="${mesg} generate ASM code,"
    [ $DOOBJGENERATION    ==  1  ] && mesg="${mesg} assemble to object code,"
    [ $DODISASMGENERATION ==  1  ] && mesg="${mesg} disassemble the object code,"
    [ $DOCOMPARISON       ==  1  ] && mesg="${mesg} compare all,"
    [ x$DOGETFOLDER       != x"" ] && RUNDIR=${ASMGENRUNDIR}/${DOGETFOLDER}
    [ x$DOGETFOLDER       != x"" ] && mesg="${mesg} using folder: ${DOGETFOLDER},"
    
    printf "Done.\n${mesg}\b.\n"
}

function script_help ()
{
    printf "Command line options\n"
    printf "   -h        This brief help.\n"
    printf "   -l        Do instructions listing.\n"
    printf "   -i        Do instructions expansion.\n"
    printf "   -a        Do ASM generation.\n"
    printf "   -o        Do assembling of files to OBJ files.\n"
    printf "   -d        Do disassembling of OBJ files.\n"
    printf "   -c        Do comparisons.\n"
    printf "   -r <dir>  Use the folder given as <dir>.\n"
    printf "\nThe default - no arguments - is to do all of the above.\n"

    return;
}

function ui_header ()
{
    local thecolor=$1
    local mesg=$2
    
    printf "${!thecolor} ${mesg} $NOCOLOR\n" | tee -a ${RUNLOG}
}

function print_setup ()
{
    ui_header FAILCOLOR "*** AJIT ASM Static Testing ***"
    ui_header OKCOLOR "ASM Tools directory structure"
    printf "%-25s : %-15s : %s\n" "Top level directory" ASMGENTOPDIR ${ASMGENTOPDIR}
    print_sym_val ASMGENBINDIR  "Tools directory"
    print_sym_val ASMGENSRCDIR  "Tools sources directory"
    print_sym_val ASMGENDATADIR "Data directory for tools"
    print_sym_val ASMGENRUNDIR  "Top level runs directory"
    
    ui_header OKCOLOR "AJIT Tools directory structure"
    printf "%-25s : %-15s : %s\n" "Top level directory" AJITTOOLSTOPDIR ${AJITTOOLSTOPDIR}
    print_sym_val AJITTOOLSOUTDIR "Buildroot output in"
    print_sym_val AJITTOOLSBINDIR "AJIT tools in"
    print_sym_val AJITTOOLSPREFIX "AJIT tools prefix"
    
    ui_header OKCOLOR "Details of Testing Tools"
    print_sym_val INSNGEN     "INSN Generator tool"
    print_sym_val ASMTOOL     "AJIT Assembler tool"
    print_sym_val ASMTOOLARGS "AJIT Assembler arguments"
    print_sym_val ODTOOL      "AJIT Objdump tool"
    print_sym_val ODTOOLARGS  "AJIT Objdump arguments"

    ui_header OKCOLOR "Details of input and output files"
    print_sym_val INSNLST  "List of INSNS"
    print_sym_val INSNDATA "INSN Details file"
    print_sym_val INSNFMTS "INSN Bit layouts file"

    ui_header OKCOLOR "Testing run details"
    print_sym_val RUNDATE "Run date and time"
}

function genoutheader ()
{
    local f=$1
    cat <<EOF
        .file           ".${f}"
        .section        ".text"
        .align 4
        .psize          0,200
        .global main
        .type   main, #function
main:
        nop
EOF
}

function genouttail ()
{
    cat <<EOF
        nop
        .ident  "GCC: (Buildroot 2014.08) 4.7.4"
        .section  .note.GNU-stack,"",@progbits
EOF
}

function insn_list ()
{
    ${INSNGEN} -l -i ${INSNDATA} -f ${INSNFMTS} -o ${INSNLST}
    sort ${INSNLST} | uniq > /tmp/a
    mv /tmp/a ${INSNLST}
}

function insn_gen ()
{
    count=0
    ok=0
    failed=0
    usedir=${RUNDIR}/insns
    [ ! -d ${usedir} ] && mkdir -p ${usedir}
    
    for insn in $(cat ${INSNLST})
    do
        outname=${insn}.out
        outfile=${usedir}/${outname}
        errfile=${usedir}/${insn}.err
        count=$(expr $count + 1)
        
        printf "#%03d : %-20s : %-20s : " ${count} ${insn} ${outname} | tee -a ${RUNLOG}

        ${INSNGEN} -i ${INSNDATA} -f ${INSNFMTS} -e ${insn} > ${outfile} 2> ${errfile}
        
        if [ ${insn} == "cswap" ];
        then
            cat ${outfile}                                 | \
                sed -e "s/cswap \(\[.*\]\), /cswap \1 0,/" | \
                sed -e "/cswap %[goli].*, %[goli].* #;/d"  > ${outfile}.1
            cp ${outfile}.1 ${outfile}
        fi
        
        if [ ${insn} == "fstoh" ]     || \
               [ ${insn} == "fhtos" ] || \
               [ ${insn} == "lddf" ]  || \
               [ ${insn} == "stdf" ];
        then
            cp ${outfile} ${outfile}.0
            cat ${outfile} | sed -e "/%f[13579][13579]*/d"  | sed -e "/%f[2468][13579]*/d" > ${outfile}.1
            cp ${outfile}.1 ${outfile}
        fi
        
        if [ -s ${errfile} ];
        then
            printf "ERROR.\n" | tee -a ${RUNLOG}
            failed=$(expr ${failed} + 1)
        else
            printf "Done. \r"
            printf "Done. \n" >> ${RUNLOG}
            ok=$(expr ${ok} + 1)
        fi
        printf "   Command used was: " ${count} ${insn}                                           >> ${RUNLOG}
        printf "${INSNGEN} -i ${INSNDATA} -f ${INSNFMTS} -e ${insn} > ${outfile} 2> ${errfile}\n" >> ${RUNLOG}
    done

    printf "\n"
    printf "=== Instruction details generated: %03d ok and %03d failed.\n" ${ok} ${failed} | tee -a ${RUNLOG}
}

function make_asm ()
{
    count=0
    ok=0
    failed=0
    asmdir=${RUNDIR}/asms
    [ ! -d ${asmdir} ] && mkdir -p ${asmdir}
    
    for insn in $(cat ${INSNLST})
    do
        infile=${asmdir}/../insns/${insn}.out
        inname=$(basename ${infile})

        if [ -s ${infile} ];
        then
            opcfile=${asmdir}/${insn}.opc # OPcode and bit pattern that have been generated.
            outfile=${asmdir}/${insn}.s
            errfile=${asmdir}/${insn}.err
            outname=$(basename ${outfile})
            count=$(expr $count + 1)

            printf "#%03d : %-20s : %-20s : " ${count} ${inname} ${outname} | tee -a ${RUNLOG}
            
            genoutheader                                                    > ${outfile}
            cat $infile | grep "^0x"                                        >> ${opcfile} 2>  ${errfile}
            cat $opcfile                                                    | \
                awk -F\| '{printf ("\t%s\n\tnop\n", gensub (" #;", "", "g", $3))}' >> ${outfile} 2>> ${errfile}
            genouttail                                                      >> ${outfile}

            if [ -s ${errfile} ];
            then
                printf "ERROR.\n" | tee -a ${RUNLOG}
                failed=$(expr ${failed} + 1)
            else
                printf "Done. \r"
                printf "Done. \n" >> ${RUNLOG}
                ok=$(expr ${ok} + 1)
            fi
        else
            failed=$(expr ${failed} + 1)
            printf "%-20s    %-20s NOT FOUND.\n" ${inname} " " | tee -a ${RUNLOG}
        fi
    done
    
    printf "\n"
    printf "=== ASM code for Instructions generated: %03d ok and %03d failed.\n" ${ok} ${failed} | tee -a ${RUNLOG}
}

function make_objs ()
{
    count=0
    objok=0
    objfailed=0
    objdir=${RUNDIR}/objs
    [ ! -d ${objdir} ] && mkdir -p ${objdir}

    asmdir=${RUNDIR}/asms
    objdir=${RUNDIR}/objs
    
    [ ! -d ${objdir} ] && mkdir -p ${objdir}
    
    for insn in $(cat ${INSNLST})
    do
        asmfile=${asmdir}/${insn}.s
        asmname=$(basename ${asmfile})

        if [ -s ${asmfile} ];
        then
            objfile=${objdir}/${insn}.o
            errfile=${objdir}/${insn}.err
            lstfile=${objdir}/${insn}.lst
            objname=$(basename ${objfile})
            
            count=$(expr $count + 1)

            printf "#%03d : %-20s : %-20s : " ${count} ${asmname} ${objname} | tee -a ${RUNLOG}
            ${ASMTOOL} ${ASMTOOLARGS} -ahls=${lstfile} ${asmfile} -o ${objfile} 2> ${errfile}
            retval=$?
            [ -s ${errfile} ]                                                    && \
                printf "ERROR. (See: %s)\n" $(make_compact_dir_names ${errfile}) || \
                printf "Done.\r"
            ([ -s ${errfile} ]                                                    && \
                 printf "ERROR. (See: %s)\n" $(make_compact_dir_names ${errfile}) || \
                 printf "Done.\n")                                                 >> ${RUNLOG}
            # [ -s ${errfile} ]                                                    && \
            #   printf "ERROR. (See: %s)\n" $(make_compact_dir_names ${errfile}) || \
            #       printf "Done.\r"                                                 | tee -a ${RUNLOG}
            [ -s ${errfile} ] && objfailed=$(expr ${objfailed} + 1) || objok=$(expr ${objok} + 1)
        else
            objfailed=$(expr ${objfailed} + 1)
            printf "%-20s    %-20s NOT FOUND.\n" ${asmname} " " | tee -a ${RUNLOG}
        fi
    done
    
    printf "\n"
    printf "=== OBJ code for Instructions generated: %03d ok and %03d failed.\n" ${objok} ${objfailed} | tee -a  ${RUNLOG}
}

function make_disasms ()
{
    count=0
    disok=0
    disfailed=0

    objdir=${RUNDIR}/objs
    disdir=${RUNDIR}/disasm
    [ ! -d ${disdir} ] && mkdir -p ${disdir}
    
    for insn in $(cat ${INSNLST})
    do
        objfile=${objdir}/${insn}.o
        objname=$(basename ${objfile})

        if [ -s ${objfile} ];
        then
            disfile=${disdir}/${insn}.dis.s
            errfile=${disdir}/${insn}.err
            lstfile=${disdir}/${insn}.lst
            disname=$(basename ${disfile})
            
            count=$(expr $count + 1)
            printf " %-20s : %-20s : " ${objname} ${disname} | tee -a ${RUNLOG}
            ${ODTOOL} ${ODTOOLARGS} ${objfile} > ${disfile} 2> ${errfile}
            retval=$?
            ([ -s ${errfile} ] && printf "ERROR. (See: %s)\n" ${errfile} || printf "Done.\r")
            ([ -s ${errfile} ] && printf "ERROR. (See: %s)\n" ${errfile} || printf "Done.\n") | tee -a ${RUNLOG}
            [ -s ${errfile} ] && disfailed=$(expr ${disfailed} + 1) || disok=$(expr ${disok} + 1)
        else
            disfailed=$(expr ${disfailed} + 1)
            printf "%-20s    %-20s NOT FOUND.\n" ${objname} " " | tee -a ${RUNLOG}
        fi
    done
    
    printf "\n"
    printf "=== DISASM for Instructions generated: %03d ok and %03d failed.\n" ${disok} ${disfailed} | tee -a ${RUNLOG}
}

function make_cmps ()
{
    asmdir=${RUNDIR}/asms
    objdir=${RUNDIR}/objs
    disdir=${RUNDIR}/disasm
    resdir=${RUNDIR}/results
    
    [ ! -d ${objdir} ] && mkdir -p ${objdir}
    [ ! -d ${disdir} ] && mkdir -p ${disdir}
    [ ! -d ${resdir} ] && mkdir -p ${resdir}
    
    for insn in $(cat ${INSNLST})
    do
        printf "Insn: %-20s: " ${insn} | tee -a ${RUNLOG}
        
        asmfile=${asmdir}/${insn}.s
        opcfile=${asmdir}/${insn}.opc # OPcode and bit pattern that have been generated.
        objfile=${objdir}/${insn}.o
        lstfile=${objdir}/${insn}.lst
        errfile=${objdir}/${insn}.err
        disfile=${disdir}/${insn}.dis.s
        resfile=${resdir}/${insn}.res
        [ ${insn} == "nop" ] && togrep="AMV" || togrep="nop"
        #printf "Grep: %-20s: \n" ${togrep} | tee -a ${RUNLOG}
        
        asmname=$(basename ${asmfile})
        opcname=$(basename ${opcfile})
        objname=$(basename ${objfile})
        lstname=$(basename ${lstfile})
        disname=$(basename ${disfile})
        resname=$(basename ${resfile})
        
        opctmp=${resdir}/${insn}-opc.tmp
        lsttmp=${resdir}/${insn}-lst.tmp
        distmp=${resdir}/${insn}-disasm.tmp

        if [ -s ${opcfile} ];
        then
            count=$(expr $count + 1)
            printf " %-20s : " ${opcname} | tee -a ${RUNLOG}

            cat ${opcfile}                                   | \
                awk -F\| '{printf ("%s|%s|%s\n",               \
                         gensub ("0x", "", "g", $1),           \
                         gensub ("[#;][#;]*", "", "g", $3),    \
                          $2)}'                              | \
                sed -e "s/ | /|/g"                           | \
                sort -t \| -k 1                              | \
                uniq                                           > ${opctmp}
        else
            failed=$(expr ${failed} + 1)
            printf "%-18s NF " ${opcname} | tee -a ${RUNLOG}
        fi
        
        if [ ! -s ${errfile} -a -s ${lstfile} ];
        then
            count=$(expr $count + 1)
            printf " %-20s : " ${lstname} | tee -a ${RUNLOG}

            cat ${lstfile}             | \
                sed -e "1,7d"          | \
                grep -v ${togrep}      | \
                sed -e "s/^  *//"      | \
                sed -e "/^$/d"         | \
                grep "^[0-9]"          | \
                grep -v ".ident"       | \
                grep -v ".section"     | \
                awk -F"\t+" '{x=split ($1, f, " "); printf ("%s|%s\n", f[3], gensub("^  *", "", "g", $2))}'  > ${lsttmp}.1

            # create a binary output column
            cat ${lsttmp}.1                                  | \
                awk -F\| '{print $1}'                        | \
                ~amv/bin/pbx                                 | \
                sed -e "s/ /|/"                              | \
                sort -t \| -k 1                              | \
                uniq                                         | \
                join -t\| -j 1 -o 1.1,1.2,2.2 ${lsttmp}.1 -    > ${lsttmp}
        else
            failed=$(expr ${failed} + 1)
            printf "%-18sNF " ${lstname} | tee -a ${RUNLOG}
        fi
        
        if [ -s ${disfile} ];
        then
            count=$(expr $count + 1)
            printf " %-20s : " ${disname} | tee -a ${RUNLOG}

            cat ${disfile}                                                                    | \
                sed -e "1,7d"                                                                 | \
                grep -v ${togrep}                                                             | \
                awk -F"\t" '{printf ("%s|%s\n", toupper(gensub (" ", "", "g", $2)), $3)}'       > ${distmp}.1

            # create a binary output column
            cat ${distmp}.1                                  | \
                awk -F\| '{print $1}'                        | \
                ~amv/bin/pbx                                 | \
                sed -e "s/ /|/"                              | \
                sort -t \| -k 1                              | \
                uniq                                         | \
                join -t\| -j 1 -o 1.1,1.2,2.2 ${distmp}.1 -    > ${distmp}
        else
            failed=$(expr ${failed} + 1)
            printf "%-18sNF " ${disname} | tee -a ${RUNLOG}
        fi
        
        printf "\r"
        printf "\n" >> ${RUNLOG}
    done
    
    printf "\n" | tee -a ${RUNLOG}
    return
}

function make_res ()
{
    asmdir=${RUNDIR}/asms
    objdir=${RUNDIR}/objs
    disdir=${RUNDIR}/disasm
    resdir=${RUNDIR}/results
    
    for insn in $(cat ${INSNLST})
    do
        asmfile=${asmdir}/${insn}.s
        opcfile=${asmdir}/${insn}.opc # OPcode and bit pattern that have been generated.
        objfile=${objdir}/${insn}.o
        lstfile=${objdir}/${insn}.lst
        disfile=${disdir}/${insn}.dis.s
        resfile=${resdir}/${insn}.res
        inffile=${resdir}/${insn}.inf
        
        asmname=$(basename ${asmfile})
        opcname=$(basename ${opcfile})
        objname=$(basename ${objfile})
        lstname=$(basename ${lstfile})
        disname=$(basename ${disfile})
        resname=$(basename ${resfile})
        
        opctmp=${resdir}/${insn}-opc.tmp
        lsttmp=${resdir}/${insn}-lst.tmp
        distmp=${resdir}/${insn}-disasm.tmp
        restmp=${resdir}/${insn}-res.tmp

        opclines=$(wc -l ${opcfile} | awk '{print $1}')
        lstlines=$(wc -l ${lstfile} | awk '{print $1}')
        dislines=$(wc -l ${disfile} | awk '{print $1}')

        count=$(expr $count + 1)
        printf "Insn: %-14s : %-32s : %-32s : %-32s\n"   \
               ${insn}                                   \
               $(make_compact_dir_names ${opcfile})      \
               $(make_compact_dir_names ${lstfile})      \
               $(make_compact_dir_names ${disfile})      | tee -a ${RUNLOG}

        printf "Insn: %-14s : %-15s : %-5d : %-15s : %-5d : %-15s : %-5d\n"   \
               ${insn}                    \
               ${opcname}   ${opclines}   \
               ${lstname}   ${lstlines}   \
               ${disname}   ${dislines}   | tee -a ${inffile}

        # join -t\| -a 1 -a 2 -j 1 -o 1.1,1.2,2.1,2.2 ${lsttmp} ${distmp} > ${restmp} 2> ${restmp}.err
        # join -t\| -a 1 -a 2 -j 1 -o 1.1,1.2,1.3,1.4,2.1,2.2,2.3 ${restmp} ${opctmp} > ${restmp}.1 2> ${restmp}.err

        # join -t\| -j 1 -o 1.1,1.2,2.1,2.2             ${lsttmp} ${distmp} | uniq > ${restmp}   2> ${restmp}.err

        # printf "%-8s|%-30s|%-8s|%-30s|%s\n"  "AsmOpC"  "AsmInsn" "DisOpC" "DisAsmInsn" "Result"   > ${resfile}
        # cat ${restmp}                                                                  | \
        #     awk -F\| '{if ($1 == $3) r="PASS"; else r="FAIL";              \
        #                   printf ("%8s|%-30s|%8s|%-30s|%s\n", $1, $2, $3, $4, r)}'   >> ${resfile}
        
        join -t\| -j 1 -o 1.1,1.2,1.3,2.1,2.2,2.3             ${lsttmp} ${distmp} | uniq > ${restmp}   2> ${restmp}.err
        join -t\| -j 1 -o 1.1,1.2,1.3,1.4,1.5,1.6,2.1,2.2,2.3 ${restmp} ${opctmp} | uniq > ${restmp}.1 2> ${restmp}.err

        printf "%-8s|%-30s|%-40s|" "AsmOpC" "AsmInsn" "AsmBin"    > ${resfile}
        printf "%-8s|%-30s|%-40s|" "DisOpC" "DisInsn" "DisBin"   >> ${resfile}
        printf "%-8s|%-30s|%-40s|" "GenOpC" "GenInsn" "GenBin"   >> ${resfile}
        printf "%s\n"              "Result"                      >> ${resfile}
        cat ${restmp}.1                                                                         | \
            awk -F\| '{if (($1 == $4) && ($4 == $7)) r="PASS"; else r="FAIL";                     \
                          printf ("%4s|%14s|%8s|%-30s|%-40s|%8s|%-30s|%-40s|%-8s|%-30s|%-40s\n",  \
                                   r,insn, $1, $2, $3, $4, $5, $6, $7, $8, $9)}'                  >> ${resfile}
        
        # printf "%-8s|%-30s|%-8s|"  "AsmOpC"      "AsmInsn" "DisOpC"      > ${resfile}
        # printf "%-30s|%-8s|%-30s|" "DisAsmInsn"  "GenOpC"  "GenAsmInsn" >> ${resfile}
        # printf "%-32s|%s\n"        "Binary Code" "Result"               >> ${resfile}
        # cat ${restmp}.1                                                                  | \
        #     awk -F\| '{if (($1 == $3) && ($3 == $5)) r="PASS"; else r="FAIL";              \
        #                   printf ("%8s|%-30s|%8s|%-30s|%-8s|%-30s|%-32s|%s\n", $1, $2, $3, $4, $5, $6, $7, r)}'   >> ${resfile}

        # /bin/rm -f ${restmp} ${restmp}.1
    done
    
    return
}

function make_table ()
{
    # local insntolook=$1
    # local filetocheck=$2
    local status=0
    local numpats=0
    local numpass=0
    local numfail=0
    local count=0

    asmdir=${RUNDIR}/asms
    objdir=${RUNDIR}/objs
    disdir=${RUNDIR}/disasm
    resdir=${RUNDIR}/results
    
    tabfile=${resdir}/all-insns.tab

    cat <<EOF > ${tabfile}

EOF
    
    printf "%3s: %-15s : %-15s : %-15s : %-15s : %10s\n" "Num" "INSN" "PASS" "FAIL" "TOTAL" "STATUS" | tee ${tabfile}
    for insn in $(cat ${INSNLST})
    do
        resfile=${resdir}/${insn}.res
        resname=$(basename ${resfile})
        restmp=${resdir}/${insn}-res.tmp

        numpats=$(wc -l $resfile | awk '{printf ("%d", ($1 - 1))}') # Skip the header line.
        count=$(expr $count + 1)
        if [ $numpats -gt 0 ];
        then
            grep ${insn} ${resfile} | grep FAIL
            [ $? == 0 ] && status="FAIL" || status="PASS"
        fi
        numfail=$(grep ${insn} ${resfile} | grep FAIL | wc -l | awk '{print $1}')
        numpass=$(grep ${insn} ${resfile} | grep PASS | wc -l | awk '{print $1}')
        [ $numpats == "0" ] && status="FAIL" || status=${status}

        printf "%03d: %-15s : %-15d : %-15d : %-15d : %-10s\n"  \
               ${count} ${insn} ${numpass} ${numfail} ${numpats} ${status} | tee -a ${tabfile}
    done
    numfail=$(cat ${tabfile} | grep -v Num | grep FAIL | wc -l | awk '{print $1}')
    numpass=$(cat ${tabfile} | grep -v Num | grep PASS | wc -l | awk '{print $1}')
    numpats=$(cat ${tabfile} | grep -v Num | wc -l | awk '{print $1}')

    printf "Summary: Total instructions checked: %-15s : Total Passed : %-15d : Total Failed : %-10s\n"  \
            ${numpats} ${numpass} ${numfail} | tee -a ${tabfile}
    
    return
}

function cleanup ()
{
    ENDTIME=$(date +%s)
    TIMETAKEN=$(expr $ENDTIME - $STARTTIME)
    TIMEMINS=$(expr $TIMETAKEN / 60)
    TIMESECS=$(expr $TIMETAKEN % 60)

    echo
    ui_header OKCOLOR "End of Run"
    printf "%-25s : %s m %s s\n" "Time taken" ${TIMEMINS} ${TIMESECS}
}

function main ()
{
    setup $*
    print_setup | tee -a ${RUNLOG}
    printf "\n" | tee -a ${RUNLOG}
    
    ui_header RUNCOLOR "Listing the instructions."
    insn_list
    printf "\n" | tee -a ${RUNLOG}
    
    ui_header RUNCOLOR "Generating all instruction patterns."
    insn_gen
    printf "\n" | tee -a ${RUNLOG}
    
    ui_header RUNCOLOR "Generating ASM test files."
    make_asm
    printf "\n" | tee -a ${RUNLOG}
    
    ui_header RUNCOLOR "Generating OBJ files."
    make_objs
    printf "\n" | tee -a ${RUNLOG}
    
    ui_header RUNCOLOR "Generating DISASM files."
    make_disasms
    printf "\n" | tee -a ${RUNLOG}
    
    ui_header RUNCOLOR "Generating Comparison data files."
    make_cmps
    printf "\n" | tee -a ${RUNLOG}
    
    ui_header RUNCOLOR "Generating Comparison results files."
    make_res
    printf "\n" | tee -a ${RUNLOG}
    
    ui_header RUNCOLOR "Generating Results table."
    make_table
    printf "\n" | tee -a ${RUNLOG}
    
    cleanup
}

main $*
exit
