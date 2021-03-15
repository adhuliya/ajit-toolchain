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

# Misc. variables
STARTTIME=
ENDTIME=

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
    STARTTIME=$(date +%s)
    [ ! -d ${RUNDIR} ] && mkdir -p ${RUNDIR}
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

function insn_gen ()
{
    count=0
    ok=0
    failed=0
    usedir=${RUNDIR}/insns
    [ ! -d ${usedir} ] && mkdir -p ${usedir}
    
    for insn in $(cat ${INSNLST})
    do
        outfile=${usedir}/${insn}.out
        errfile=${usedir}/${insn}.err
        count=$(expr $count + 1)
        
        printf "Generating instruction #%03d: %-15s ... " ${count} ${insn}
        printf "Generating instruction #%03d: %-15s ... " ${count} ${insn}                        >> ${RUNLOG}
        printf "   Command is: " ${count} ${insn}                                                 >> ${RUNLOG}
        printf "${INSNGEN} -i ${INSNDATA} -f ${INSNFMTS} -e ${insn} > ${outfile} 2> ${errfile}\n" >> ${RUNLOG}

        ${INSNGEN} -i ${INSNDATA} -f ${INSNFMTS} -e ${insn} > ${outfile} 2> ${errfile}
        
        if [ -s ${errfile} ];
        then
            printf "   Status is: ERROR.\n" | tee -a ${RUNLOG}
            failed=$(expr ${failed} + 1)
        else
            printf "   Status is: Done. \n" | tee -a ${RUNLOG}
            ok=$(expr ${ok} + 1)
        fi
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
        outfile=${asmdir}/${insn}.s
        errfile=${asmdir}/${insn}.err
        count=$(expr $count + 1)
        printf "Generating    ASM file |%-15s| from insn List file |%-15s| ... " $(basename ${outfile}) $(basename ${infile}) | \
	    tee -a ${RUNLOG}
        genoutheader                                                               > ${outfile}
        cat $infile | awk -F\| '{printf ("\t%s\n", gensub (" #;", "", "g", $3))}' >> ${outfile} 2> ${errfile}
        genouttail                                                                >> ${outfile}

        if [ -s ${errfile} ];
        then
            printf "   Status is: ERROR.\n" | tee -a ${RUNLOG}
            failed=$(expr ${failed} + 1)
        else
            printf "   Status is: Done. \n" | tee -a ${RUNLOG}
            ok=$(expr ${ok} + 1)
        fi
    done
    
    printf "\r"
    printf "=== ASM code for Instructions generated: %03d ok and %03d failed.\n" ${ok} ${failed}
    printf "=== ASM code for Instructions generated: %03d ok and %03d failed.\n" ${ok} ${failed} >> ${RUNLOG}
}

function process_asms ()
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
	printf "Generating    OBJ file |%-15s| from insn    ASM file |%-15s| ... " ${objname} ${asmname} | \
		    tee -a ${RUNLOG}
        ${ASMTOOL} ${ASMTOOLARGS} -ahls=${lstfile} ${asmfile} -o ${objfile} 2> ${errfile}
        retval=$?
        [ -s ${errfile} ] && printf "ERROR.\r" || printf "Done.\r"
        ([ -s ${errfile} ] && printf "ERROR.\n" || printf "Done.\n") >> ${RUNLOG}
        [ -s ${errfile} ] && objfailed=$(expr ${objfailed} + 1) || objok=$(expr ${objok} + 1)
    done
    printf "\r                                                                                \r"
    printf "=== OBJ code for Instructions generated: %03d ok and %03d failed.\n" ${objok} ${objfailed}
    printf "=== OBJ code for Instructions generated: %03d ok and %03d failed.\n" ${objok} ${objfailed} >> ${RUNLOG}

    if [ $retval == 0 ];
       then
           count=0
           for insn in $(cat ${INSNLST})
           do
               # asmfile=${asmdir}/${insn}.s
               # objfile=${objdir}/${insn}.o
               # errfile=${objdir}/${insn}.err
               # lstfile=${objdir}/${insn}.lst
               # disfile=${disdir}/${insn}.dis.s
               # resfile=${resdir}/${insn}.res
               
               count=$(expr $count + 1)
               printf "Disassembling OBJ file |%-15s| to        DISASM file |%-15s| ... " ${objname} ${asmname} | \
		   tee -a ${RUNLOG}
               ${ODTOOL} ${ODTOOLARGS} ${objfile} > ${disfile} 2> ${disfile}.err
               [ -s ${disfile}.err ] && printf "ERROR.\r" || printf "Done.\r"
               ([ -s ${disfile}.err ] && printf "ERROR.\n" || printf "Done.\n") >> ${RUNLOG}
               [ -s ${disfile}.err ] && disfailed=$(expr ${disfailed} + 1) || disok=$(expr ${disok} + 1)
           done
           printf "\r                                                                                \r"
           printf "=== DISASSEMBLY for Instructions generated: %03d ok and %03d failed.\n" ${disok} ${disfailed}
           printf "=== DISASSEMBLY for Instructions generated: %03d ok and %03d failed.\n" ${disok} ${disfailed} >> ${RUNLOG}
           
           count=0
           for insn in $(cat ${INSNLST})
           do
               # asmfile=${asmdir}/${insn}.s
               # objfile=${objdir}/${insn}.o
               # errfile=${objdir}/${insn}.err
               # lstfile=${objdir}/${insn}.lst
               # disfile=${disdir}/${insn}.dis.s
               # resfile=${resdir}/${insn}.res
               
               count=$(expr $count + 1)
               printf "Comparing ASM-OBJ machine code with OBJ-ASM machine code for insn: %s ...\n" ${insn} | tee -a ${RUNLOG}
               printf "          ASM Listing file: %s\n" ${lstfile}                                         | tee -a ${RUNLOG}
               printf "          DISASM file     : %s\n" ${disfile}                                         | tee -a ${RUNLOG}
               printf "\rComparing ASM-OBJ machine code with OBJ-ASM machine code for insn: %s ..." ${insn}

               grep "^  *" ${lstfile}                                                            | \
                   sed -e "s/              */      /"                                            | \
                   awk -F"	" '{n=patsplit ($1, f, "[0-9a-fA-F]+");                            \
                           if (n >= 3)                                                             \
                              printf ("%s|%s\n",                                                   \
                                      f[3],                                                        \
                                      gensub("^[       ][      ]*", "", "g", $2))}'              | \
                   sort                                                                            > /tmp/yy.tmp
               grep "^  *" ${disfile}                                                            | \
                   awk -F"	" '{printf ("%s|%s\n", toupper(gensub (" ", "", "g", $2)), $3)}' | \
                   sort                                                                            > /tmp/zz.tmp
               join -t\| -a 1 -a 2 -j 1 -o 1.1,2.1,1.2,2.2 /tmp/yy.tmp /tmp/zz.tmp               | \
                   awk -F\| '{if ($1 == $2) r="PASS"; else r="FAIL"; printf ("%s|%s|%s|%s|%s\n", $1, $2, $3, $4, r)}' > ${resfile}
               printf "\r                                                                                \r"
               # printf "=== STATIC CHECK for instruction \"%s\" generated.\n" ${insn}
               printf "=== STATIC CHECK for instruction \"%s\" generated.\n" ${insn} | tee -a ${RUNLOG}
           done
           printf "=== Result files for each instruction are in: %s.\n" ${resdir} | tee -a ${RUNLOG}
    fi
}

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
	printf "Generating    OBJ file |%-15s| from insn    ASM file |%-15s| ... " ${objname} ${asmname} | \
		    tee -a ${RUNLOG}
        ${ASMTOOL} ${ASMTOOLARGS} -ahls=${lstfile} ${asmfile} -o ${objfile} 2> ${errfile}
        retval=$?
        [ -s ${errfile} ] && printf "ERROR.\n" || printf "Done.\n" | tee -a ${RUNLOG}
        [ -s ${errfile} ] && objfailed=$(expr ${objfailed} + 1) || objok=$(expr ${objok} + 1)
        if [ $retval == 0 ];
        then
            printf "Disassembling OBJ file |%-15s| to        DISASM file |%-15s| ... " ${objname} ${asmname} | \
		tee -a ${RUNLOG}
            ${ODTOOL} ${ODTOOLARGS} ${objfile} > ${disfile} 2> ${disfile}.err
            retval=$?
            [ -s ${disfile}.err ] && printf "ERROR.\n" || printf "Done.\n" | tee -a ${RUNLOG}
            [ -s ${disfile}.err ] && disfailed=$(expr ${disfailed} + 1) || disok=$(expr ${disok} + 1)

            if [ $retval == 0 ];
            then
                printf "Comparing ASM-OBJ machine code with OBJ-ASM machine code for insn: %s ...\n" ${insn} >> ${RUNLOG}
                printf "          ASM Listing file: %s\n" ${lstfile}                                         >> ${RUNLOG}
                printf "          DISASM file     : %s\n" ${disfile}                                         >> ${RUNLOG}
                printf "Comparing ASM-OBJ machine code with OBJ-ASM machine code for insn: %s ...\n" ${insn}

                grep "^  *" ${lstfile}                                                            | \
                    sed -e "s/              */      /"                                            | \
                    awk -F"	" '{n=patsplit ($1, f, "[0-9a-fA-F]+");                              \
                           if (n >= 3)                                                              \
                              printf ("%s|%s\n",                                                    \
                                      f[3],                                                         \
                                      gensub("^[       ][      ]*", "", "g", $2))}'               | \
                    sort                                                                            > /tmp/yy.tmp
                grep "^  *" ${disfile}                                                            | \
                    awk -F"	" '{printf ("%s|%s\n", toupper(gensub (" ", "", "g", $2)), $3)}'  | \
                    sort                                                                            > /tmp/zz.tmp
                join -t\| -a 1 -a 2 -j 1 -o 1.1,2.1,1.2,2.2 /tmp/yy.tmp /tmp/zz.tmp               | \
                    awk -F\| '{if ($1 == $2) r="PASS"; else r="FAIL"; printf ("%s|%s|%s|%s|%s\n", $1, $2, $3, $4, r)}' > ${resfile}
		print_status ${insn} ${resfile}
            else
                printf "xxx Could not disassemble instruction: %s (Object file: %s).\n" ${insn} ${objfile} | tee -a ${RUNLOG}
            fi
        else
            printf "xxx Could not assemble instruction: %s (ASM file: %s).\n" ${insn} ${asmfile} | tee -a ${RUNLOG}
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
    setup
    print_setup

    printf "\n"
    ui_header RUNCOLOR "Listing the instructions."
    insn_list

    printf "\n"
    ui_header RUNCOLOR "Generating all instruction patterns."
    insn_gen

    printf "\n"
    ui_header RUNCOLOR "Generating ASM test files."
    make_asm

    printf "\n"
    ui_header RUNCOLOR "Processing ASM test files."
    do_process_asms

    cleanup
}

main $*
exit
