#!/bin/bash

#
# Script to update the build  version of GNU Binutils in the buildroot
# system with the version  under development.  This updated version is
# then  rebuilt using  "make &&  make  install" in  the same  binutils
# directory.
#
# NOTE: A  usual build of  the system using  buildroot has to  be done
# before we start updating.
#
# Standard GNU coreutils, fileutils etc. used in this script.
#

### AJITTOPHOME=/lindata/My-work/Professional/iitb
AJITTOPHOME=/home/amv/projects/iitb

AJITTARBALLHOME=${AJITTOPHOME}/tarballs
AJITDEVELOPMENTHOME=${AJITTOPHOME}/development
AJITGITHOME=${AJITDEVELOPMENTHOME}/amv-ajit-code
AJITBINUTILSHOME=${AJITGITHOME}/ajit-binutils-2.22

AJITBUILDROOTHOME=${AJITTOPHOME}/build/buildroot-2014.08
AJITBUILDROOTBUILDDIR=${AJITBUILDROOTHOME}/output/build
AJITBUILDROOTBINUTILSDIR=${AJITBUILDROOTBUILDDIR}/host-binutils-2.22
AJITBUILDROOTBIN=${AJITBUILDROOTHOME}/output/host/usr/bin
AJITBUILDROOTSBIN=${AJITBUILDROOTHOME}/output/host/usr/sbin

# Add to PATH
PATH=${AJITBUILDROOTBIN}:${AJITBUILDROOTSBIN}:${PATH}

# Files to copy; use relative paths
FILESTOUPDATE="include/opcode/sparc.h opcodes/sparc-opc.c"

TOOLPREFIX=sparc-buildroot-linux-uclibc
# TOOLPREFIX=sparc-linux
ASMTOOL="${TOOLPREFIX}-as"
DISASMTOOL=${TOOLPREFIX}-objdump
STATTOOL=/usr/bin/stat

STATTOOLARGS="--format=%y"	# Human readable time of last modification, i.e. latest build time.

OLDASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITBUILDROOTBIN}/${ASMTOOL}")
OLDDISASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITBUILDROOTBIN}/${DISASMTOOL}")

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

    printf "%-25s : %s %s\n" ${sym} "${pval}" "${cmt}"
}

function print_setup ()
{
    local cmt=

    print_sym_val AJITTOPHOME "(Top level)"
    print_sym_val AJITTARBALLHOME ""
    print_sym_val AJITDEVELOPMENTHOME ""
    print_sym_val AJITGITHOME ""
    print_sym_val AJITBINUTILSHOME ""
    print_sym_val AJITBUILDROOTHOME ""
    print_sym_val AJITBUILDROOTBUILDDIR ""
    print_sym_val AJITBUILDROOTBINUTILSDIR ""
    print_sym_val AJITBUILDROOTBIN ""
    print_sym_val AJITBUILDROOTSBIN ""

    print_sym_val STATTOOL ""
    print_sym_val STATTOOLARGS ""
    # print_sym_val PATH
    print_sym_val TOOLPREFIX ""
    cmt=$([ -x ${AJITBUILDROOTBIN}/${ASMTOOL} ] && echo " (available in PATH)" || echo " (NOT available in PATH)")
    print_sym_val ASMTOOL "${cmt}"
    cmt=$([ -x ${AJITBUILDROOTBIN}/${DISASMTOOL} ] && echo " (available in PATH)" || echo " (NOT available in PATH)")
    print_sym_val DISASMTOOL "${cmt}"

    print_sym_val OLDASMTOOLBUILDDATE "(PRE-UPDATE Assembler build date and time)"
    print_sym_val OLDDISASMTOOLBUILDDATE "(PRE-UPDATE Disassembler build date and time)"

    return 0
}

function do_update ()
{
	# printf "   cp ${AJITBINUTILSHOME}/${f} ${AJITBUILDROOTBINUTILSDIR}/${f}\n"
    for f in ${FILESTOUPDATE}
    do
	printf "%-25s : %-30s " "Updating" "${f} ..."
	    cp ${AJITBINUTILSHOME}/${f} ${AJITBUILDROOTBINUTILSDIR}/${f} && \
	    printf "Done.\n"                                             || \
	    printf "COPYing ERROR.\n"
    done
	
    return $?
}

function do_build ()
{
    printf "%-25s : %-30s " "Building" "updated BINUTILS ..."
    # printf "   cd ${AJITBUILDROOTBINUTILSDIR}\n"
    # printf "      make install > ajit-binutils.log 2> ajit-binutils.err\n"
    # printf "      cd -\n"

    cd ${AJITBUILDROOTBINUTILSDIR}                            && \
    	make install > ajit-binutils.log 2> ajit-binutils.err && \
	printf "Done.\n"                                      || \
	printf "BUILD Error.\n"
    cd - > /dev/null 2>&1
	
    return $?
}

function print_build_status ()
{
    NEWASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITBUILDROOTBIN}/${ASMTOOL}")           && \
	NEWDISASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITBUILDROOTBIN}/${DISASMTOOL}") && \
	print_sym_val NEWASMTOOLBUILDDATE "(POST-UPDATE Assembler build date and time)"                && \
	print_sym_val NEWDISASMTOOLBUILDDATE "(POST-UPDATE Disassembler build date and time)"

    ISOK=$([ "${NEWASMTOOLBUILDDATE}" == "${OLDASMTOOLBUILDDATE}" ] && printf "NOT OK." || printf "OK.") && \
	print_sym_val ISOK "(File modification time based overall status of UPDATED code)"
	
    return $?
}

print_setup
printf "\n"             && \
    do_update           && \
    do_build            && \
    printf "\n"         && \
    print_build_status

exit

