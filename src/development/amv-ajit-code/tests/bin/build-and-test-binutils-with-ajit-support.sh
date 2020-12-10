#!/bin/bash

# --------------------------------------------------------------------
# Script to build and test the 2.22 version of GNU Binutils _with AJIT
# support_ in the buildroot system with the version under development.
#
# THIS IS  NO LONGER  SPARC WITH  AJIT ADDED.
#
# GNU BINUTILS 2.22  now supports AJIT as an independent  CPU.  A full
# BINUTILS toolchain,  i.e. assembler, linker  etc. is built  for AJIT
# only.
#
# Added code  to run the  tests for  the newly built  AJIT cross
# binutils toolchain.
#
# NOTE: A  usual build of  the system using  buildroot has to  be done
# before we start updating.
#
# Standard GNU coreutils, fileutils etc. used in this script.
# --------------------------------------------------------------------

# --------------------------------------------------------------------
# Set the three variables below to the correct directories.  
# See USAGE.txt.
# --------------------------------------------------------------------
AJITTOPHOME=/lindata/My-work/Professional/iitb

###
# Variables common to all the ajit development and testing scripts.
###
AJITTARBALLHOME=${AJITTOPHOME}/tarballs
AJITDEVELOPMENTHOME=${AJITTOPHOME}/development
AJITGITHOME=${AJITDEVELOPMENTHOME}/git-repo
AJITGITREPOHOME=${AJITGITHOME}/ajit-toolchain/src/development/amv-ajit-code
AJITBINUTILSHOME=${AJITGITREPOHOME}/ajit-binutils-2.22
AJITNEWBINUTILSHOME=${AJITGITREPOHOME}/ajit-supported-binutils-2.22/ajit-binutils-2.22
AJITTRIALSINSTALLHOME=${AJITGITREPOHOME}/trial-install
AJITTRIALSINSTALL=${AJITTRIALSINSTALLHOME}/ajit-install
AJITTRIALSINSTALLBIN=${AJITTRIALSINSTALL}/bin

AJITTESTHOME=${AJITGITREPOHOME}/tests
AJITTESTSRC=${AJITTESTHOME}/src
AJITTESTASM=${AJITTESTHOME}/asm
AJITTESTBIN=${AJITTESTHOME}/bin
AJITTESTBLD=${AJITTESTHOME}/build
AJITTESTOBJECT=${AJITTESTHOME}/ajit-supported-obj
AJITTESTDISASM=${AJITTESTHOME}/ajit-supported-disasm
AJITTESTGDBASM=${AJITTESTHOME}/ajit-supported-gdbasm

# Add to PATH
PATH=${AJITTRIALSINSTALLBIN}:${PATH}

TOOLPREFIX=ajit-buildroot-linux-gnu
ASMTOOL=${TOOLPREFIX}-as
DISASMTOOL=${TOOLPREFIX}-objdump
GDBTOOL=${TOOLPREFIX}-gdb
STATTOOL=/usr/bin/stat
GDBCMDFILE="/tmp/commands.gdb"

ASMTOOLARGS="-Aajit"
DISASMTOOLARGS="-d"             # Using "-D" to disassemble __all__ sections can give "unknown"
                                # instructions in non-text sections!
GDBTOOLARGS="-batch -x ${GDBCMDFILE}"
STATTOOLARGS="-c %y"	        # Human readable time of last modification, i.e. latest build time.

# Build a list of ASM source files.
TESTASMS=$(ls ${AJITTESTASM}/*.s)

OLDASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITTRIALSINSTALLBIN}/${ASMTOOL}")
OLDDISASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITTRIALSINSTALLBIN}/${DISASMTOOL}")

# Collect build status
BUILD_STAT=0

# Colour variables
RED="\033[1;31m"
GREEN="\033[1;32m"
NOCOLOR="\033[0m"
GREENONYELLOW="\033[1;32;1;43m"
YELLOWONRED="\033[1;33;0;41m"

OKCOLOR=${GREENONYELLOW}
FAILCOLOR=${YELLOWONRED}
OKMESG="${OKCOLOR}[ OK ]${NOCOLOR}"
FAILMESG="${FAILCOLOR}[FAIL]${NOCOLOR}"
DONEMESG="${OKCOLOR}[Done]${NOCOLOR}"
BLDERRMESG="${FAILCOLOR}[Build ERROR]${NOCOLOR}"
CPERRMESG="${FAILCOLOR}[Copy ERROR]${NOCOLOR}"
DISTERRMESG="${FAILCOLOR}[distclean ERROR]${NOCOLOR}"
CONFERRMESG="${FAILCOLOR}[configure ERROR]${NOCOLOR}"
MAKEERRMESG="${FAILCOLOR}[make      ERROR]${NOCOLOR}"
INSTERRMESG="${FAILCOLOR}[install   ERROR]${NOCOLOR}"

function print_sym_val ()
{
    local sym=$1
    local val=${!sym}           # Use one level of indirection in bash.
    local cmt=$2

    local pval=
    local ahome=$(echo $AJITTOPHOME | sed -e "s/\//\\\\\//g")
    local dhome=$(echo $AJITDEVELOPMENTHOME | sed -e "s/\//\\\\\//g")
    local ghome=$(echo $AJITGITREPOHOME | sed -e "s/\//\\\\\//g")

    if [ x$sym != xAJITGITREPOHOME ];
    then
        pval=$(echo $val | sed -e "s/${ghome}/\${AJITGITREPOHOME}/g")
    else
        pval=$val
    fi

    printf "%-30s : %s %s\n" ${sym} "${pval}" "${cmt}"
}

function print_setup ()
{
    local cmt=

    printf "\n"
    printf "Directory structure:\n"
    print_sym_val AJITTOPHOME "(Top level)"
    print_sym_val AJITTARBALLHOME ""
    print_sym_val AJITDEVELOPMENTHOME ""
    print_sym_val AJITGITHOME ""
    print_sym_val AJITGITREPOHOME ""
    print_sym_val AJITBINUTILSHOME ""

    print_sym_val AJITTESTHOME ""
    print_sym_val AJITTESTSRC ""
    print_sym_val AJITTESTASM ""
    print_sym_val AJITTESTOBJECT ""
    print_sym_val AJITTESTBIN ""
    print_sym_val AJITTESTBLD ""
    print_sym_val AJITTESTDISASM ""
    print_sym_val AJITTESTGDBASM ""

    print_sym_val AJITTRIALSINSTALLHOME ""
    print_sym_val AJITTRIALSINSTALL ""
    print_sym_val AJITTRIALSINSTALLBIN ""

    printf "\n"
    printf "Tools used and their command line flags:\n"
    print_sym_val STATTOOL ""
    print_sym_val STATTOOLARGS ""

    print_sym_val TOOLPREFIX ""
    cmt=$([ -x ${AJITTRIALSINSTALLBIN}/${ASMTOOL} ] && echo " (available in PATH)" || echo " (NOT available in PATH)")
    print_sym_val ASMTOOL "${cmt}"
    cmt=$([ -x ${AJITTRIALSINSTALLBIN}/${DISASMTOOL} ] && echo " (available in PATH)" || echo " (NOT available in PATH)")
    print_sym_val DISASMTOOL "${cmt}"

    printf "\n"
    printf "Time stamp of tools before build (if any):\n"
    print_sym_val OLDASMTOOLBUILDDATE "(PRE-UPDATE Assembler build date and time)"
    print_sym_val OLDDISASMTOOLBUILDDATE "(PRE-UPDATE Disassembler build date and time)"

    return 0
}

function do_build ()
{
    local target=ajit-buildroot-linux-gnu
    local prefix=${AJITTRIALSINSTALL}
    local distcleanfileprefix=0-distclean
    local errdistclean=${distcleanfileprefix}.err
    local logdistclean=${distcleanfileprefix}.log
    local configurefileprefix=0-configure
    local errconfigure=${configurefileprefix}.err
    local logconfigure=${configurefileprefix}.log
    local makefileprefix=0-make
    local errmake=${makefileprefix}.err
    local logmake=${makefileprefix}.log
    local installfileprefix=0-install
    local errinstall=${installfileprefix}.err
    local loginstall=${installfileprefix}.log
    local retval=0
    local CURRENTDIR=

    printf "%-30s : %-30s\n" "Building" "AJIT BINUTILS..."
    cd ${AJITNEWBINUTILSHOME}
    # CURRENTDIR=$(pwd)
    # print_sym_val CURRENTDIR ""

    [ ! ${cwd} == ${AJITNEWBINUTILSHOME} ] && printf "ERROR: Wrong directory.\n" && retval=-1 && return ${retval}

    [ ${retval} == 0 ]                                                                         && \
	[ -f ./Makefile ]                                                                      && \
	printf "%-30s : %-30s " "   make target" "distclean"                                   && \
	make distclean                                2> ${errdistclean} > ${logdistclean}     && \
	printf "${DONEMESG}\n" || \
	([ ! -f ./Makefile ] && printf "${DONEMESG}\n" || (printf "${DISTERRMESG}\n" && less ${errdistclean}))
    retval=$?

    [ ${retval} == 0 ]                                                                         && \
	printf "%-30s : %-30s " "   configure"   "${target}"                                   && \
	./configure --target=${target} --prefix=${prefix} 2> ${errconfigure} > ${logconfigure} && \
	printf "${DONEMESG}\n" || \
	(printf "${CONFERRMESG}\n" && less ${errconfigure})
    retval=$?

    [ ${retval} == 0 ]                                                                         && \
	printf "%-30s : %-30s " "   make target" "default"                                     && \
	make                                          2> ${errmake}      > ${logmake}          && \
	printf "${DONEMESG}\n" || \
	(printf "${MAKEERRMESG}\n" && less ${errmake})
    retval=$?

    [ ${retval} == 0 ]                                                                         && \
	printf "%-30s : %-30s " "   make target" "install"                                     && \
	make install                                  2> ${errinstall}   > ${loginstall}       && \
	printf "${DONEMESG}\n" || \
	(printf "${INSTERRMESG}\n" && less ${errinstall})
    retval=$?

    cd - > /dev/null 2>&1

    BUILD_STAT=$retval
    return $retval
}

function print_build_status ()
{
    local s=1;
    local t=0;			# amv

    NEWASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITTRIALSINSTALLBIN}/${ASMTOOL}")           && \
        NEWDISASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITTRIALSINSTALLBIN}/${DISASMTOOL}") && \
        printf "Time stamp of tools after build (if any):\n"                                           && \
        print_sym_val NEWASMTOOLBUILDDATE "(POST-UPDATE Assembler build date and time)"                && \
        print_sym_val NEWDISASMTOOLBUILDDATE "(POST-UPDATE Disassembler build date and time)"

    # The new  tools must  at least have  a different time  stamp than
    # their old version.  This will be  the case if the new tools have
    # been successfully  built.  Otherwise we  will be looking  at the
    # same old tools in the NEW variables above.
    [[ "${NEWASMTOOLBUILDDATE}"    != "${OLDASMTOOLBUILDDATE}" ]]        && \
        [[ "${NEWDISASMTOOLBUILDDATE}" != "${OLDDISASMTOOLBUILDDATE}" ]] # Success if these are different!
    s=$?

    AJITBUILDSTATUS=$( if test $s -eq 0; then printf "OK."; else printf "NOT OK."; fi ) && \
        printf "\n"                                                                     && \
        print_sym_val AJITBUILDSTATUS "(File modification time based overall status of UPDATED code)"

    return $s
}

function do_assemble ()
{
    local inasm=$1
    local outobj=$2
    local lst=
    local retval=

    [ ! -f $inasm ] && \
        printf "%-40s %s NOT FOUND. " "${ASMTOOL}" $(basename $inasm)
    [ -f $inasm ] && \
        lst=$(basename $inasm .s).lst          && \
        err=$(basename $inasm .s).err          && \
        printf "%-40s %-10s %-20s to %s ... " "${ASMTOOL}" "${ASMTOOLARGS}" $(basename $inasm) $(basename $outobj) && \
        ${ASMTOOL} ${ASMTOOLARGS} $inasm -o $outobj > ${AJITTESTOBJECT}/$lst 2> ${AJITTESTOBJECT}/$err && \
        retval=$?                              && \
        [ $retval == 0 ] && retmsg="${OKMESG}" || retmsg="${FAILMESG}"
        printf "${retmsg}\n"

    return $?
}

function do_disassemble ()
{
    local inobj=$1
    local outdisasm=$2
    local retval=

    [ ! -f $inobj ] && \
        printf "%-40s %s NOT FOUND. " "${DISASMTOOL}" $(basename $inobj)
    [ -f $inobj ]                              && \
        err=$(basename $inobj .s).diserr       && \
        printf "%-40s %-10s %-20s to %s ... " "${DISASMTOOL}" "${DISASMTOOLARGS}" $(basename $inobj) $(basename $outdisasm) && \
        ${DISASMTOOL} ${DISASMTOOLARGS} $inobj > $outdisasm 2> ${AJITTESTDISASM}/$err && \
        retval=$?                              && \
        [ $retval == 0 ] && retmsg="${OKMESG}" || retmsg="${FAILMESG}"
        printf "${retmsg}\n" 
        
    return $?
}

function cleanup ()
{
    /bin/rm -f ${GDBCMDFILE}

    return
}

print_setup
printf "\n"                          && \
    do_build                         && \
    printf "\n"                      && \
    print_build_status               && \
    printf "\n"                      && \
    print_build_status               && \
    printf "\n"                      && \
    [ ${BUILD_STAT} == "0" ]         && \
    printf "Running basic tests:\n"  && \
    for a in ${TESTASMS}
    do
        objname=${AJITTESTOBJECT}/$(basename $a .s).o   
        disasmname=${AJITTESTDISASM}/$(basename $a .s).dis.s
        
        do_assemble ${a}       ${objname}               && \
            do_disassemble     ${objname} ${disasmname}
    done
    :
cleanup

exit $?
