#!/bin/bash

#
# Script to run the newly built SPArc-AJIT cross compiler and binutils
# toolchain.
#
# Standard GNU coreutils, fileutils etc. used.
#

AJITTOPHOME=/lindata/My-work/Professional/iitb

AJITTARBALLHOME=${AJITTOPHOME}/tarballs
AJITDEVELOPMENTHOME=${AJITTOPHOME}/development
AJITGITHOME=${AJITDEVELOPMENTHOME}/amv-ajit-code

AJITBUILDROOTHOME=${AJITTOPHOME}/build/buildroot-2014.08
AJITBUILDROOTBIN=${AJITBUILDROOTHOME}/output/host/usr/bin
AJITBUILDROOTSBIN=${AJITBUILDROOTHOME}/output/host/usr/sbin

AJITAMVTESTHOME=${AJITTOPHOME}/tests
AJITAMVTESTSRC=${AJITAMVTESTHOME}/src
AJITAMVTESTASM=${AJITAMVTESTHOME}/asm
AJITAMVTESTOBJ=${AJITAMVTESTHOME}/obj
AJITAMVTESTBIN=${AJITAMVTESTHOME}/bin
AJITAMVTESTBLD=${AJITAMVTESTHOME}/build
AJITAMVTESTDISASM=${AJITAMVTESTHOME}/disasm

### /lindata/My-work/Professional/iitb/build/buildroot-2014.08/output/host/usr/bin:/lindata/My-work/Professional/iitb/build/buildroot-2014.08/output/host/usr/sbin:/usr/lib/lightdm/lightdm:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games
# Add to PATH
PATH=${AJITBUILDROOTBIN}:${AJITBUILDROOTSBIN}:${PATH}

TOOLPREFIX=sparc-buildroot-linux-uclibc
# TOOLPREFIX=sparc-linux
ASMTOOL="${TOOLPREFIX}-as"
DISASMTOOL=${TOOLPREFIX}-objdump
STATTOOL=/usr/bin/stat

### ASMTOOLARGS="-a -ag"   # No "-Av8" gives "Hardware capability XXX not enabled for insn YYY" error.
ASMTOOLARGS="-Av8 -bump -a -ag"
DISASMTOOLARGS="-d"
STATTOOLARGS="--format=%y"	# Human readable time of last modification, i.e. latest build time.
STATTOOLARGS="-c %y"	# Human readable time of last modification, i.e. latest build time.

ASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITBUILDROOTBIN}/${ASMTOOL}")
DISASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITBUILDROOTBIN}/${DISASMTOOL}")

# Build a list of ASM source files.
TESTASMS=$(ls ${AJITAMVTESTASM}/*.s)

function print_sym_val ()
{
    local sym=$1
    local val=${!sym}		# Use one level of indirection in bash.
    local cmt=$2

    local pval=
    local ahome=$(echo $AJITTOPHOME | sed -e "s/\//\\\\\//g")

    if [ x$sym != xAJITTOPHOME ];
    then
	pval=$(echo $val | sed -e "s/${ahome}/\${AJITTOPHOME}/g")
    else
	pval=$val
    fi

    printf "%-30s : %s %s\n" ${sym} "${pval}" "${cmt}"
}

function print_setup ()
{
    local cmt=

    print_sym_val AJITTOPHOME "(Top level)"
    print_sym_val AJITTARBALLHOME ""
    print_sym_val AJITDEVELOPMENTHOME ""
    print_sym_val AJITGITHOME ""
    print_sym_val AJITBUILDROOTHOME ""
    print_sym_val AJITBUILDROOTBIN ""
    print_sym_val AJITBUILDROOTSBIN ""
    print_sym_val AJITAMVTESTHOME ""
    print_sym_val AJITAMVTESTSRC ""
    print_sym_val AJITAMVTESTASM ""
    print_sym_val AJITAMVTESTOBJ ""
    print_sym_val AJITAMVTESTBIN ""
    print_sym_val AJITAMVTESTBLD ""
    print_sym_val AJITAMVTESTDISASM ""
    print_sym_val STATTOOL ""
    print_sym_val STATTOOLARGS ""
    # print_sym_val PATH
    print_sym_val TOOLPREFIX ""
    cmt=$([ -x ${AJITBUILDROOTBIN}/${ASMTOOL} ] && echo " (available in PATH)" || echo " (NOT available in PATH)")
    print_sym_val ASMTOOL "${cmt}"
    cmt=$([ -x ${AJITBUILDROOTBIN}/${DISASMTOOL} ] && echo " (available in PATH)" || echo " (NOT available in PATH)")
    print_sym_val DISASMTOOL "${cmt}"
    print_sym_val ASMTOOLBUILDDATE "(Assembler built on this date and time)"
    print_sym_val DISASMTOOLBUILDDATE "(Disassembler built on this date and time)"

    return 0
}

function do_assemble ()
{
    local inasm=$1
    local outobj=$2
    local lst=

    [ ! -f $inasm ] && \
	printf "%-40s %s NOT FOUND.\n" "${ASMTOOL}" $inasm
    [ -f $inasm ] && \
	lst=$(basename $inasm .s).lst
	printf "%-40s %-20s %-20s to %s ...\n" "${ASMTOOL}" "${ASMTOOLARGS}" $(basename $inasm) $(basename $outobj) && \
	${ASMTOOL} ${ASMTOOLARGS} $inasm -o $outobj > ${AJITAMVTESTOBJ}/$lst
	
    return $?
}

function do_disassemble ()
{
    local inobj=$1
    local outdisasm=$2

    [ ! -f $inobj ] && \
	printf "%-40s %s NOT FOUND.\n" "${DISASMTOOL}" $inobj
    [ -f $inasm ] && \
	printf "%-40s %-20s %-20s to %s ...\n" "${DISASMTOOL}" "${DISASMTOOLARGS}" $(basename $inobj) $(basename $outdisasm) && \
	${DISASMTOOL} ${DISASMTOOLARGS} $inobj > $outdisasm
	
    return $?
}

print_setup
for a in ${TESTASMS}
do
    objname=${AJITAMVTESTOBJ}/$(basename $a .s).o   
    disasmname=${AJITAMVTESTDISASM}/$(basename $a .s).dis.s

    do_assemble ${a} ${objname} && \
	do_disassemble ${objname} ${disasmname}
done


