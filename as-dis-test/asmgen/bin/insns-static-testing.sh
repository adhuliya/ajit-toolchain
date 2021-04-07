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

# MASTERTOPDIR=/lindata/My-work/Professional/iitb/development
# BRANCHTOPDIR=${MASTERTOPDIR}/isa-v2-branch
# ASMGENTOPDIR=${BRANCHTOPDIR}/ajit-toolchain/as-dis-test/asmgen
# ASMGENBINDIR=${ASMGENTOPDIR}/bin
# ASMGENSRCDIR=${ASMGENTOPDIR}/code/python
# ASMGENDATADIR=${ASMGENTOPDIR}/data
# ASMGENRUNDIR=${ASMGENTOPDIR}/runs

# AJITTOOLSTOPDIR=${MASTERTOPDIR}/../build/buildroot-2014.08
# AJITTOOLSOUTDIR=${AJITTOOLSTOPDIR}/output/host
# AJITTOOLSBINDIR=${AJITTOOLSOUTDIR}/usr/bin
# AJITTOOLSPREFIX=sparc-buildroot-linux-uclibc

# # Tools
# # Insn generator tool
# INSNGEN=${ASMGENSRCDIR}/opcode-generator.py
# ASMTOOL=${AJITTOOLSBINDIR}/${AJITTOOLSPREFIX}-as
# ASMTOOLARGS=-Av8
# ODTOOL=${AJITTOOLSBINDIR}/${AJITTOOLSPREFIX}-objdump
# ODTOOLARGS="-d -z"

# # Data files
# INSNLST=${ASMGENDATADIR}/the-insns.lst
# INSNDATA=${ASMGENDATADIR}/all-insns.csv
# INSNFMTS=${ASMGENDATADIR}/all-formats.csv

# RUNDATE=$(date +%A-%B-%d-%Y-%H-%M-%S)
# RUNDIR=${ASMGENRUNDIR}/${RUNDATE}
# RUNLOG=${RUNDIR}/run.log

# # Colour variables
# RED="\033[1;31m"
# GREEN="\033[1;32m"
# NOCOLOR="\033[0m"
# GREENONYELLOW="\033[1;32;1;43m"
# YELLOWONRED="\033[1;33;0;41m"
# YELLOWONGREEN="\033[1;33;1;42m"
# REDONGREEN="\033[1;31;1;42m"

# OKCOLOR=${GREENONYELLOW}
# FAILCOLOR=${YELLOWONRED}
# RUNCOLOR=${REDONGREEN}
# OKMESG="${OKCOLOR}[ OK ]${NOCOLOR}"
# FAILMESG="${FAILCOLOR}[FAIL]${NOCOLOR}"
# DONEMESG="${OKCOLOR}[Done]${NOCOLOR}"
# BLDERRMESG="${FAILCOLOR}[Build ERROR]${NOCOLOR}"
# CPERRMESG="${FAILCOLOR}[Copy ERROR]${NOCOLOR}"

# # Misc. variables
# STARTTIME=
# ENDTIME=

function print_sym_val ()
{
    local sym=$1
    local val=${!sym}           # Use one level of indirection in bash.
    local cmt=$2

    local pval=
    local ahome=$(echo $ASMGENTOPDIR | sed -e "s/\//\\\\\//g")
    local bhome=$(echo $AJITTOOLSTOPDIR | sed -e "s/\//\\\\\//g")
    local chome=$(echo $AJITTOOLSBINDIR | sed -e "s/\//\\\\\//g")

    pval=$(echo $val | sed -e "s/${ahome}/\${ASMGENTOPDIR}/g" | sed -e "s/${bhome}/\${AJITTOOLSTOPDIR}/g")
    
    printf "%-25s : %-15s : %s\n" "${cmt}" ${sym} "${pval}"
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

    RUNDATE=$(date +%A-%B-%d-%Y-%H-%M-%S)
    RUNDIR=${ASMGENRUNDIR}/${RUNDATE}
    RUNLOG=${RUNDIR}/run.log

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
    
    # Misc. variables
    STARTTIME=
    ENDTIME=

    # Now do the main setup
    process_options $*
    
    STARTTIME=$(date +%s)
    [ ! -d ${RUNDIR} ] && mkdir -p ${RUNDIR}
}

function process_options ()
{
    local args=$*
    local optstr=":vhliaodc"
    local argvar                # where we collect the argument

    printf "II == %-40s: \"%s\" : " "Processing command line" "$args"
    DOLISTINSTRUCTIONS=1
    DOINSNEXPANSION=1
    DOASMGENERATION=1
    DOOBJGENERATION=1
    DODISASMGENERATION=1
    DOCOMPARISON=1

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
            *) printf "Unknown option: %s\n" $OPTARG; exit;;
        esac
    done
    mesg="Will: "
    [ $DOLISTINSTRUCTIONS == 1 ] && mesg="${mesg} list instructions,"
    [ $DOINSNEXPANSION    == 1 ] && mesg="${mesg} expand instructions,"
    [ $DOASMGENERATION    == 1 ] && mesg="${mesg} generate ASM code,"
    [ $DOOBJGENERATION    == 1 ] && mesg="${mesg} assemble to object code,"
    [ $DODISASMGENERATION == 1 ] && mesg="${mesg} disassemble the object code,"
    [ $DOCOMPARISON       == 1 ] && mesg="${mesg} compare all,"
    
    printf "Done.\n${mesg}\b.\n"
}

function script_help ()
{
    printf "Command line options\n"
    printf "   -h   This brief help.\n"
    printf "   -l   Do instructions listing.\n"
    printf "   -i   Do instructions expansion.\n"
    printf "   -a   Do ASM generation.\n"
    printf "   -o   Do assembling of files to OBJ files.\n"
    printf "   -d   Do disassembling of OBJ files.\n"
    printf "   -c   Do comparisons.\n"
    printf "\nThe default - no arguments - is to do all of the above.\n"

    return;
}

function ui_header ()
{
    local thecolor=$1
    local mesg=$2
    
    printf "${!thecolor} ${mesg} $NOCOLOR\n"
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

# function print_and_record ()
# {
#     local m=$1
    
#     printf "Generating instruction #%03d: %-15s ... " ${count} ${insn}
#     printf "Generating instruction #%03d: %-15s ... " ${count} ${insn}                        >> ${RUNLOG}
#     printf "   Status is: ERROR.\n" | tee -a ${RUNLOG}
#     printf "   Status is: Done. \n" | tee -a ${RUNLOG}
#     printf "   Command used was: " ${count} ${insn}                                           >> ${RUNLOG}
#     printf "${INSNGEN} -i ${INSNDATA} -f ${INSNFMTS} -e ${insn} > ${outfile} 2> ${errfile}\n" >> ${RUNLOG}
#     printf "=== Instruction details generated: %03d ok and %03d failed.\n" ${ok} ${failed}
#     printf "=== Instruction details generated: %03d ok and %03d failed.\n" ${ok} ${failed}  >> ${RUNLOG}
# }

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
        
        printf "Generating instruction #%03d: %-15s to %-20s ... " ${count} ${insn} ${outname}
        printf "Generating instruction #%03d: %-15s to %-20s ... " ${count} ${insn} ${outname}  >> ${RUNLOG}

        ${INSNGEN} -i ${INSNDATA} -f ${INSNFMTS} -e ${insn} > ${outfile} 2> ${errfile}
        
        if [ -s ${errfile} ];
        then
            # printf "   Status is: ERROR.\n" | tee -a ${RUNLOG}
            printf "   ERROR.\n" | tee -a ${RUNLOG}
            failed=$(expr ${failed} + 1)
        else
            # printf "   Status is: Done. \n" | tee -a ${RUNLOG}
            printf "   Done. \n" | tee -a ${RUNLOG}
            ok=$(expr ${ok} + 1)
        fi
        printf "   Command used was: " ${count} ${insn}                                           >> ${RUNLOG}
        printf "${INSNGEN} -i ${INSNDATA} -f ${INSNFMTS} -e ${insn} > ${outfile} 2> ${errfile}\n" >> ${RUNLOG}
    done

    printf "\r"
    printf "=== Instruction details generated: %03d ok and %03d failed.\n" ${ok} ${failed}
    printf "=== Instruction details generated: %03d ok and %03d failed.\n" ${ok} ${failed}  >> ${RUNLOG}
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
	opcfile=${asmdir}/${insn}.opc # OPcode and bit pattern that have been generated.
        outfile=${asmdir}/${insn}.s
        errfile=${asmdir}/${insn}.err
	outname=$(basename ${outfile})
	inname=$(basename ${infile})
        count=$(expr $count + 1)
        # printf "Generating    ASM file |%-16s| from insn List file |%-20s| ... " ${outname} ${inname} | \
	#     tee -a ${RUNLOG}
        printf "%-20s to %-20s ... " ${inname} ${outname} | tee -a ${RUNLOG}
        genoutheader                                                    > ${outfile}
        cat $infile | grep "^0x"                                        >> ${opcfile} 2>  ${errfile}
        cat $opcfile                                                    | \
	    awk -F\| '{printf ("\t%s\n", gensub (" #;", "", "g", $3))}' >> ${outfile} 2>> ${errfile}
        genouttail                                                      >> ${outfile}

        if [ -s ${errfile} ];
        then
            printf "   ERROR.\n" | tee -a ${RUNLOG}
            failed=$(expr ${failed} + 1)
        else
            printf "   Done. \n" | tee -a ${RUNLOG}
            ok=$(expr ${ok} + 1)
        fi
    done
    
    printf "\r"
    printf "=== ASM code for Instructions generated: %03d ok and %03d failed.\n" ${ok} ${failed}
    printf "=== ASM code for Instructions generated: %03d ok and %03d failed.\n" ${ok} ${failed} >> ${RUNLOG}
}

# function process_asms ()
# {
#     count=0
#     objok=0
#     objfailed=0
#     disok=0
#     disfailed=0
#     resok=0
#     resfailed=0
#     retval=0

#     asmdir=${RUNDIR}/asms
#     objdir=${RUNDIR}/objs
#     disdir=${RUNDIR}/disasm
#     resdir=${RUNDIR}/results
    
#     [ ! -d ${objdir} ] && mkdir -p ${objdir}
#     [ ! -d ${disdir} ] && mkdir -p ${disdir}
#     [ ! -d ${resdir} ] && mkdir -p ${resdir}
    
#     for insn in $(cat ${INSNLST})
#     do
#         asmfile=${asmdir}/${insn}.s
#         objfile=${objdir}/${insn}.o
#         errfile=${objdir}/${insn}.err
#         lstfile=${objdir}/${insn}.lst
#         disfile=${disdir}/${insn}.dis.s
#         resfile=${resdir}/${insn}.res
# 	objname=$(basename ${objfile})
# 	asmname=$(basename ${asmfile})
        
#         count=$(expr $count + 1)
# 	# printf "Generating    OBJ file |%-16s| from insn    ASM file |%-20s| ... " ${objname} ${asmname} | \
# 	# 	    tee -a ${RUNLOG}
# 	printf "%-20s to %-20s ... " ${asmname} ${objname} | tee -a ${RUNLOG}
#         ${ASMTOOL} ${ASMTOOLARGS} -ahls=${lstfile} ${asmfile} -o ${objfile} 2> ${errfile}
#         retval=$?
#         [ -s ${errfile} ]  && printf "ERROR.\n" || printf "Done.\n"
#         ([ -s ${errfile} ] && printf "ERROR.\n" || printf "Done.\n") >> ${RUNLOG}
#         [ -s ${errfile} ]  && objfailed=$(expr ${objfailed} + 1) || objok=$(expr ${objok} + 1)
#         printf "   Command is: ${ASMTOOL} ${ASMTOOLARGS} -ahls=${lstfile} ${asmfile} -o ${objfile} 2> ${errfile}\n" >> ${RUNLOG}
#     done
#     printf "\r                                                                                \r"
#     printf "=== OBJ code for Instructions generated: %03d ok and %03d failed.\n" ${objok} ${objfailed}
#     printf "=== OBJ code for Instructions generated: %03d ok and %03d failed.\n" ${objok} ${objfailed} >> ${RUNLOG}

#     if [ $retval == 0 ];
#        then
#            count=0
#            for insn in $(cat ${INSNLST})
#            do
#                # asmfile=${asmdir}/${insn}.s
#                # objfile=${objdir}/${insn}.o
#                # errfile=${objdir}/${insn}.err
#                # lstfile=${objdir}/${insn}.lst
#                # disfile=${disdir}/${insn}.dis.s
#                # resfile=${resdir}/${insn}.res
               
#                count=$(expr $count + 1)
#                # printf "Disassembling OBJ file |%-16s| to        DISASM file |%-20s| ... " ${objname} ${asmname} | \
# 	       # 	   tee -a ${RUNLOG}
#                printf "%-20s to %-20s ... " ${objname} ${asmname} | tee -a ${RUNLOG}
#                ${ODTOOL} ${ODTOOLARGS} ${objfile} > ${disfile} 2> ${disfile}.err
#                [ -s ${disfile}.err ] && printf "ERROR.\r" || printf "Done.\r"
#                ([ -s ${disfile}.err ] && printf "ERROR.\n" || printf "Done.\n") >> ${RUNLOG}
#                [ -s ${disfile}.err ] && disfailed=$(expr ${disfailed} + 1) || disok=$(expr ${disok} + 1)
#                printf "   Command is: ${ODTOOL} ${ODTOOLARGS} ${objfile} > ${disfile} 2> ${disfile}.err\n" >> ${RUNLOG}
#            done
#            printf "\r                                                                                \r"
#            printf "=== DISASSEMBLY for Instructions generated: %03d ok and %03d failed.\n" ${disok} ${disfailed}
#            printf "=== DISASSEMBLY for Instructions generated: %03d ok and %03d failed.\n" ${disok} ${disfailed} >> ${RUNLOG}
           
#            count=0
#            for insn in $(cat ${INSNLST})
#            do
#                # asmfile=${asmdir}/${insn}.s
#                # objfile=${objdir}/${insn}.o
#                # errfile=${objdir}/${insn}.err
#                # lstfile=${objdir}/${insn}.lst
#                # disfile=${disdir}/${insn}.dis.s
#                # resfile=${resdir}/${insn}.res
# 	       lstname=$(basename ${lstfile})
# 	       disname=$(basename ${disfile})
               
#                count=$(expr $count + 1)
#                # printf "Comparing ASM-OBJ machine code with OBJ-ASM machine code for insn: %s ...\n" ${insn} | tee -a ${RUNLOG}
#                # printf "          ASM Listing file: %s\n" ${lstfile}                                         | tee -a ${RUNLOG}
#                # printf "          DISASM file     : %s\n" ${disfile}                                         | tee -a ${RUNLOG}
#                # printf "\rComparing ASM-OBJ machine code with OBJ-ASM machine code for insn: %s ..." ${insn}

#                printf "%-20s: List file opcodes %-20s == DisAsm file opcodes %-20s : "   \
# 		      ${insn} ${lstname} ${disname}                                    | tee -a ${RUNLOG}
	       
#                grep "^  *" ${lstfile}                                                            | \
#                    sed -e "s/              */      /"                                            | \
#                    awk -F"	" '{n=patsplit ($1, f, "[0-9a-fA-F]+");                            \
#                            if (n >= 3)                                                             \
#                               printf ("%s|%s\n",                                                   \
#                                       f[3],                                                        \
#                                       gensub("^[       ][      ]*", "", "g", $2))}'              | \
#                    sort                                                                            > /tmp/yy.tmp
#                grep "^  *" ${disfile}                                                            | \
#                    awk -F"	" '{printf ("%s|%s\n", toupper(gensub (" ", "", "g", $2)), $3)}' | \
#                    sort                                                                            > /tmp/zz.tmp
#                join -t\| -a 1 -a 2 -j 1 -o 1.1,2.1,1.2,2.2 /tmp/yy.tmp /tmp/zz.tmp               | \
#                    awk -F\| '{if ($1 == $2) r="PASS"; else r="FAIL"; printf ("%s|%s|%s|%s|%s\n", $1, $2, $3, $4, r)}' > ${resfile}

# 	       grep FAIL ${resfile}
# 	       ([ $? == 0 ] && printf "FAIL.\n" || printf "PASS.\n") | tee -a ${RUNLOG}
#                printf "=== STATIC CHECK for instruction \"%s\" generated.\n" ${insn} | tee -a ${RUNLOG}
#            done
#            printf "=== Result files for each instruction are in: %s.\n" ${resdir} | tee -a ${RUNLOG}
#     fi
# }

function do_process_asms ()
{
    count=0
    objok=0
    objfailed=0
    disok=0
    disfailed=0
    resok=0
    resfailed=0
    retval=0

    asmdir=${RUNDIR}/asms
    objdir=${RUNDIR}/objs
    disdir=${RUNDIR}/disasm
    resdir=${RUNDIR}/results
    
    [ ! -d ${objdir} ] && mkdir -p ${objdir}
    [ ! -d ${disdir} ] && mkdir -p ${disdir}
    [ ! -d ${resdir} ] && mkdir -p ${resdir}
    
    for insn in $(cat ${INSNLST})
    do
        asmfile=${asmdir}/${insn}.s
        objfile=${objdir}/${insn}.o
        errfile=${objdir}/${insn}.err
        lstfile=${objdir}/${insn}.lst
        disfile=${disdir}/${insn}.dis.s
        resfile=${resdir}/${insn}.res
	objname=$(basename ${objfile})
	asmname=$(basename ${asmfile})
        
        count=$(expr $count + 1)
	# printf "Generating    OBJ file |%-16s| from insn    ASM file |%-20s| ... " ${objname} ${asmname} | \
	# 	    tee -a ${RUNLOG}
	printf "%-20s to %-20s ... " ${asmname} ${objname} | tee -a ${RUNLOG}
        ${ASMTOOL} ${ASMTOOLARGS} -ahls=${lstfile} ${asmfile} -o ${objfile} 2> ${errfile}
        retval=$?
        [ -s ${errfile} ] && printf "ERROR.\n" || printf "Done.\n" | tee -a ${RUNLOG}
        [ -s ${errfile} ] && objfailed=$(expr ${objfailed} + 1) || objok=$(expr ${objok} + 1)
        if [ $retval == 0 ];
        then
            # printf "Disassembling OBJ file |%-16s| to        DISASM file |%-20s| ... " ${objname} ${asmname} | \
	    # 	tee -a ${RUNLOG}
            printf "%-20s to %-20s ... " ${objname} ${asmname} | tee -a ${RUNLOG}
            ${ODTOOL} ${ODTOOLARGS} ${objfile} > ${disfile} 2> ${disfile}.err
            retval=$?
            [ -s ${disfile}.err ] && printf "ERROR.\n" || printf "Done.\n" | tee -a ${RUNLOG}
            [ -s ${disfile}.err ] && disfailed=$(expr ${disfailed} + 1) || disok=$(expr ${disok} + 1)

            if [ $retval == 0 ];
            then
                # printf "Comparing ASM-OBJ machine code with OBJ-ASM machine code for insn: %s ...\n" ${insn} >> ${RUNLOG}
                # printf "          ASM Listing file: %s\n" ${lstfile}                                         >> ${RUNLOG}
                # printf "          DISASM file     : %s\n" ${disfile}                                         >> ${RUNLOG}
                # printf "Comparing ASM-OBJ machine code with OBJ-ASM machine code for insn: %s ...\n" ${insn}
                printf "Insn: %-20s: Comparing %-20s to %-20s\n" ${insn} ${lstfile} ${disfile} >> ${RUNLOG}

                grep "${insn}" ${lstfile}                                                         | \
                    sed -e "s/              */      /"                                            | \
                    awk -F"	" '{n=patsplit ($1, f, "[0-9a-fA-F]+");                              \
                           if (n >= 3)                                                              \
                              printf ("%s|%s\n",                                                    \
                                      f[3],                                                         \
                                      gensub("^[       ][      ]*", "", "g", $2))}'               | \
                    sort                                                                            > /tmp/yy.tmp
                # grep "^  *" ${lstfile}                                                            | \
                #     sed -e "s/              */      /"                                            | \
                #     awk -F"	" '{n=patsplit ($1, f, "[0-9a-fA-F]+");                              \
                #            if (n >= 3)                                                              \
                #               printf ("%s|%s\n",                                                    \
                #                       f[3],                                                         \
                #                       gensub("^[       ][      ]*", "", "g", $2))}'               | \
                #     sort                                                                            > /tmp/yy.tmp
                grep "${insn}" ${disfile}                                                         | \
                    awk -F"	" '{printf ("%s|%s\n", toupper(gensub (" ", "", "g", $2)), $3)}'  | \
                    sort                                                                            > /tmp/zz.tmp
                # grep "^  *" ${disfile}                                                            | \
                #     awk -F"	" '{printf ("%s|%s\n", toupper(gensub (" ", "", "g", $2)), $3)}'  | \
                #     sort                                                                            > /tmp/zz.tmp
                join -t\| -a 1 -a 2 -j 1 -o 1.1,2.1,1.2,2.2 /tmp/yy.tmp /tmp/zz.tmp               | \
                    awk -F\| '{if ($1 == $2) r="PASS"; else r="FAIL"; printf ("%s|%s|%s|%s|%s\n", $1, $2, $3, $4, r)}' > ${resfile}
		print_status ${insn} ${resfile}
            else
                # printf "xxx Could not disassemble instruction: %s (Object file: %s).\n" ${insn} ${objfile} | tee -a ${RUNLOG}
                printf "xxx Could not disassemble instruction: %s (Object file: %s).\n" ${insn} ${objfile} >> ${RUNLOG}
            fi
        else
            # printf "xxx Could not assemble instruction: %s (ASM file: %s).\n" ${insn} ${asmfile} | tee -a ${RUNLOG}
            printf "xxx Could not assemble instruction: %s (ASM file: %s).\n" ${insn} ${asmfile} >> ${RUNLOG}
	fi
    done
}

function print_status ()
{
    local insntolook=$1
    local filetocheck=$2
    local status=0

    grep ${insn} ${resfile} | grep FAIL
    [ $? == 0 ] && status="FAIL" || status="PASS"
    
    printf "\r                                                                                \r"
    printf "=== STATIC CHECK for instruction \"%-15s\": %s\n" ${insn} ${status} | tee -a ${RUNLOG}
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
    print_setup
    print_setup  >> ${RUNLOG}

    if [ ${DOLISTINSTRUCTIONS} == 1 ];
    then
	printf "\n"
	ui_header RUNCOLOR "Listing the instructions."
	insn_list
    fi

    if [ ${DOINSNEXPANSION} == 1 ];
    then
	printf "\n"
	ui_header RUNCOLOR "Generating all instruction patterns."
	insn_gen
    fi

    if [ ${DOASMGENERATION} == 1 ];
    then
	printf "\n"
	ui_header RUNCOLOR "Generating ASM test files."
	make_asm
    fi

    if [ ${DOOBJGENERATION} == 1 ]    || \
       [ ${DODISASMGENERATION} == 1 ] || \
       [ ${DOCOMPARISON} == 1 ];
    then
	printf "\n"
	ui_header RUNCOLOR "Processing ASM test files."
	do_process_asms
    fi

    cleanup
}

main $*
exit
