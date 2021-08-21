#!/bin/bash

### SPARC_PREFIX=sparc-linux
SPARC_PREFIX=sparc-buildroot-linux-uclibc

# List of tools
AJIT_ASSEMBLER=${SPARC_PREFIX}-as
AJIT_LINKER=${SPARC_PREFIX}-ld
AJIT_ELFREADER=${SPARC_PREFIX}-readelf
AJIT_OBJDUMP=${SPARC_PREFIX}-objdump

# Files etc.
ASM_FILES="init.s /usr/local/ajit_release/tools/ajit_access_routines/asm/trap_handlers.s addd.s"
LINKER_SCRIPT=LinkerScript.lnk
OBJDIR=./sparc-obj

# Options required for some tools
ASM_OPTS="-Av8"
AJIT_DISASM="${AJIT_OBJDUMP} -d"
AJIT_LD_OPTS="-e main -T ${LINKER_SCRIPT}"

# Master log file
MASTERLOG=/tmp/master.log

# Functions
function setup () {
    /bin/rm -f ${MASTERLOG}
    touch ${MASTERLOG}
    
    return
}

function search_command ()
{
    local stat=
    local cmd=$1
    local retval=

    # printf "Executing \"which %s\" ...\n" $cmd
    which ${cmd} > /tmp/which-cmd.output
    stat=$?

    [ ${stat} == "0" ] && retval=$(cat /tmp/which-cmd.output) || retval="NOT FOUND."
    /bin/rm -f /tmp/which-cmd.output

    printf "%s" $retval
    
    return $stat
}

function check_commands ()
{
    for tool in ${AJIT_ASSEMBLER} ${AJIT_LINKER} ${AJIT_ELFREADER} ${AJIT_OBJDUMP}
    do
	printf "   Searching %-35s ... %s\n" ${tool} $(search_command ${tool}) >> ${MASTERLOG}
	printf "   Searching %-35s ... %s\n" ${tool} $(search_command ${tool})
	# printf "Searching %s ... "
	# search_command ${tool}
	# printf "\n"
    done
}

function do_assemble ()
{
    local stat=
    
    for asmprog in ${ASM_FILES}
    do
	OBJNAME=$(basename $asmprog .s).o
	ONAME=${OBJDIR}/${OBJNAME}
	/bin/rm -f ${ONAME}
	
	printf "   Executing: ${AJIT_ASSEMBLER} ${ASM_OPTS} ${asmprog} -o ${ONAME} ... " >> ${MASTERLOG}
	printf "   Executing: ${AJIT_ASSEMBLER} ${ASM_OPTS} ${asmprog} -o ${ONAME} ... "
	${AJIT_ASSEMBLER} ${ASM_OPTS} ${asmprog} -o ${ONAME} >> ${MASTERLOG} 2>&1
	[ -s ${ONAME} ] && stat=0 || stat=1
	[ -s ${ONAME} ] && printf "Looks OK.\n" || printf "ERROR.\n"
	([ -s ${ONAME} ] && printf "Looks OK.\n" || printf "ERROR.\n") >> ${MASTERLOG}
    done
}

function do_link ()
{
    local objfiles=

    for asmprog in ${ASM_FILES}
    do
	ofile=$(basename $asmprog .s).o
	objfiles="${objfiles} ${OBJDIR}/${ofile}"
    done

    /bin/rm -f ./addd.elf
    printf "   Executing: ${AJIT_LINKER} ${AJIT_LD_OPTS} ${objfiles} -o addd.elf ... " >> ${MASTERLOG}
    printf "   Executing: ${AJIT_LINKER} ${AJIT_LD_OPTS} ${objfiles} -o addd.elf ... "
    ${AJIT_LINKER} ${AJIT_LD_OPTS} ${objfiles} -o addd.elf >> ${MASTERLOG} 2>&1
    [ -s ./addd.elf ] && printf "Looks OK.\n" || printf "ERROR.\n"
    ([ -s ./addd.elf} ] && printf "Looks OK.\n" || printf "ERROR.\n") >> ${MASTERLOG}
    
    return 0
}

function do_other_files ()
{
    printf "Generating hex dumps ...\n"
    /bin/rm -f ./addd.hex
    printf "   Executing: ${SPARC_PREFIX}-readelf  --hex-dump=.text --hex-dump=.rodata --hex-dump=.rodata.str1.8 --hex-dump=.data --hex-dump=.rodata.cst8 --hex-dump=.bss  ./addd.elf | tr -cd '\11\12\15\40-\176' | grep 0x > ./addd.hex\n" >> ${MASTERLOG}
    printf "   Executing: ${SPARC_PREFIX}-readelf  --hex-dump=.text --hex-dump=.rodata --hex-dump=.rodata.str1.8 --hex-dump=.data --hex-dump=.rodata.cst8 --hex-dump=.bss  ./addd.elf | tr -cd '\11\12\15\40-\176' | grep 0x > ./addd.hex ... "
    (${SPARC_PREFIX}-readelf  --hex-dump=.text --hex-dump=.rodata --hex-dump=.rodata.str1.8 --hex-dump=.data --hex-dump=.rodata.cst8 --hex-dump=.bss  ./addd.elf | tr -cd '\11\12\15\40-\176' | grep 0x) > ./addd.hex 2>> ${MASTERLOG}
    [ -s ./addd.hex ] && printf "Looks OK.\n" || printf "ERROR.\n"
    ([ -s ./addd.hex} ] && printf "Looks OK.\n" || printf "ERROR.\n") >> ${MASTERLOG}

    printf "Generating vars file ...\n"
    /bin/rm -f ./addd.vars
    printf "   Executing:  ${SPARC_PREFIX}-readelf  --symbols ./addd.elf  > ./addd.vars\n" >> ${MASTERLOG}
    printf "   Executing:  ${SPARC_PREFIX}-readelf  --symbols ./addd.elf  > ./addd.vars ... "
    ${SPARC_PREFIX}-readelf  --symbols ./addd.elf  > ./addd.vars 2>> ${MASTERLOG}
    [ -s ./addd.vars ] && printf "Looks OK.\n" || printf "ERROR.\n"
    ([ -s ./addd.vars} ] && printf "Looks OK.\n" || printf "ERROR.\n") >> ${MASTERLOG}
    
    printf "Generating disasm'd file ...\n"
    /bin/rm -f ./addd.objdump
    printf "   Executing:  ${SPARC_PREFIX}-objdump -d  .//addd.elf > ./addd.objdump\n" >> ${MASTERLOG}
    printf "   Executing:  ${SPARC_PREFIX}-objdump -d  .//addd.elf > ./addd.objdump ... "
    ${SPARC_PREFIX}-objdump -d  .//addd.elf > ./addd.objdump 2>> ${MASTERLOG}
    [ -s ./addd.objdump ] && printf "Looks OK.\n" || printf "ERROR.\n"
    ([ -s ./addd.objdump} ] && printf "Looks OK.\n" || printf "ERROR.\n") >> ${MASTERLOG}

    return 0
}

function final_msg ()
{
cat <<EOF

=====
===== Please send the ${MASTERLOG} file to: abhijatv@acm.org.
=====
EOF
    return
}

setup
check_commands
do_assemble
do_link
do_other_files
final_msg
exit

# ${SPARC_PREFIX}-as   -Av8  init.s -o .//sparc-obj/init.o
# ${SPARC_PREFIX}-as   -Av8  /usr/local/ajit_release/tools/ajit_access_routines/asm/trap_handlers.s.tpl -o .//sparc-obj/trap_handlers.o
# ${SPARC_PREFIX}-as   -Av8  addd.s -o .//sparc-obj/addd.o
# ${SPARC_PREFIX}-ld  -e main -T LinkerScript.lnk .//sparc-obj/init.o  .//sparc-obj/trap_handlers.o  .//sparc-obj/addd.o   -o .//addd.elf
# ${SPARC_PREFIX}-readelf  --hex-dump=.text --hex-dump=.rodata --hex-dump=.rodata.str1.8 --hex-dump=.data --hex-dump=.rodata.cst8 --hex-dump=.bss  .//addd.elf | tr -cd '\11\12\15\40-\176' | grep 0x > .//addd.hex
# ${SPARC_PREFIX}-readelf  --symbols .//addd.elf  > .//addd.vars
# ${SPARC_PREFIX}-objdump -d  .//addd.elf > .//addd.objdump
