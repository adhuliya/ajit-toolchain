#!/bin/bash

#
# Script to update the build  version of GNU Binutils in the buildroot
# system with the version  under development.  This updated version is
# then  rebuilt using  "make &&  make  install" in  the same  binutils
# directory.
#
# Added code  to run the  tests for  the newly built  SPArc-AJIT cross
# binutils toolchain.
#
# NOTE: A  usual build of  the system using  buildroot has to  be done
# before we start updating.
#
# Standard GNU coreutils, fileutils etc. used in this script.
#

# --------------------------------------------------------------------
# Set the two variables below to the correct directories.  
# See USAGE.txt.
# --------------------------------------------------------------------
### AJITTOPHOME=/lindata/My-work/Professional/iitb
#AJITTOPHOME=/home/gaurip
#AJITTOPHOME=/home/codeman/.itsoflife/mydata/local/packages-live/OPEN_ME_TO_README
# IMPORTANT: AJITTOPHOME is now taken from then environment.
AJITBUILDROOTHOME=${AJITTOPHOME}/buildroot-2014.08

# Nothing below  should need to  be changed.  See USAGE.TXT  to report
# any problems.
AJITTARBALLHOME=${AJITTOPHOME}/tarballs
AJITDEVELOPMENTHOME=${AJITTOPHOME}/development
AJITGITHOME=${AJITDEVELOPMENTHOME}/amv-ajit-code
AJITBINUTILSHOME=${AJITGITHOME}/ajit-binutils-2.22
AJITGDBHOME=${AJITGITHOME}/ajit-gdb-7.6.2

AJITBUILDROOTBUILDDIR=${AJITBUILDROOTHOME}/output/build
AJITBUILDROOTBINUTILSDIR=${AJITBUILDROOTBUILDDIR}/host-binutils-2.22
AJITBUILDROOTGDBDIR=${AJITBUILDROOTBUILDDIR}/host-gdb-7.6.2
AJITBUILDROOTBIN=${AJITBUILDROOTHOME}/output/host/usr/bin
AJITBUILDROOTSBIN=${AJITBUILDROOTHOME}/output/host/usr/sbin

AJITTESTHOME=${AJITGITHOME}/tests
AJITTESTSRC=${AJITTESTHOME}/src
AJITTESTASM=${AJITTESTHOME}/asm
AJITTESTOBJ=${AJITTESTHOME}/obj
AJITTESTBIN=${AJITTESTHOME}/bin
AJITTESTBLD=${AJITTESTHOME}/build
AJITTESTDISASM=${AJITTESTHOME}/disasm
AJITTESTGDBASM=${AJITTESTHOME}/gdbasm

# Add to PATH
PATH=${AJITBUILDROOTBIN}:${AJITBUILDROOTSBIN}:${PATH}

# Files to copy; use relative paths
### FILESTOUPDATE="include/opcode/sparc.h opcodes/sparc-opc.c opcodes/sparc-dis.c binutils/objdump.c binutils/objdump.h"
FILESTOUPDATE="include/opcode/sparc.h opcodes/sparc-opc.c opcodes/sparc-dis.c"

TOOLPREFIX=sparc-buildroot-linux-uclibc
# TOOLPREFIX=sparc-linux
ASMTOOL="${TOOLPREFIX}-as"
DISASMTOOL=${TOOLPREFIX}-objdump
GDBTOOL=${TOOLPREFIX}-gdb
STATTOOL=/usr/bin/stat
GDBCMDFILE="/tmp/commands.gdb"

### ASMTOOLARGS="-a -ag"   # No "-Av8" gives "Hardware capability XXX not enabled for insn YYY" error.
### ASMTOOLARGS="-Av8 -bump -a -ag"
ASMTOOLARGS="-Av8"
DISASMTOOLARGS="-d"             # Using "-D" to disassemble __all__ sections can give "unknown"
                                # instructions in non-text sections!
GDBTOOLARGS="-batch -x ${GDBCMDFILE}"
### STATTOOLARGS="--format=%y"	# Human readable time of last modification, i.e. latest build time.
STATTOOLARGS="-c %y"	        # Human readable time of last modification, i.e. latest build time.

OLDASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITBUILDROOTBIN}/${ASMTOOL}")
OLDDISASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITBUILDROOTBIN}/${DISASMTOOL}")
ASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITBUILDROOTBIN}/${ASMTOOL}")
DISASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITBUILDROOTBIN}/${DISASMTOOL}")

# Build a list of ASM source files.
TESTASMS=$(ls ${AJITTESTASM}/*.s)

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

    # Create the GDB commands file
    cat <<-EOF  > ${GDBCMDFILE}
    disassemble 0
    quit
EOF

    printf "\n"
    printf "Directory structure:\n"
    print_sym_val AJITTOPHOME "(Top level)"
    print_sym_val AJITTARBALLHOME ""
    print_sym_val AJITDEVELOPMENTHOME ""
    print_sym_val AJITGITHOME ""
    print_sym_val AJITBINUTILSHOME ""
    print_sym_val AJITGDBHOME ""
    print_sym_val AJITBUILDROOTHOME ""
    print_sym_val AJITBUILDROOTBUILDDIR ""
    print_sym_val AJITBUILDROOTBINUTILSDIR ""
    print_sym_val AJITBUILDROOTBIN ""
    print_sym_val AJITBUILDROOTSBIN ""

    print_sym_val AJITTESTHOME ""
    print_sym_val AJITTESTSRC ""
    print_sym_val AJITTESTASM ""
    print_sym_val AJITTESTOBJ ""
    print_sym_val AJITTESTBIN ""
    print_sym_val AJITTESTBLD ""
    print_sym_val AJITTESTDISASM ""
    print_sym_val AJITTESTGDBASM ""

    print_sym_val GDBCMDFILE ""

    printf "\n"
    printf "Tools used and their command line flags:\n"
    print_sym_val STATTOOL ""
    print_sym_val STATTOOLARGS ""
    # print_sym_val PATH ""
    print_sym_val TOOLPREFIX ""
    cmt=$([ -x ${AJITBUILDROOTBIN}/${ASMTOOL} ] && echo " (available in PATH)" || echo " (NOT available in PATH)")
    print_sym_val ASMTOOL "${cmt}"
    cmt=$([ -x ${AJITBUILDROOTBIN}/${DISASMTOOL} ] && echo " (available in PATH)" || echo " (NOT available in PATH)")
    print_sym_val DISASMTOOL "${cmt}"

    printf "\n"
    printf "Time stamp of tools before build (if any):\n"
    print_sym_val OLDASMTOOLBUILDDATE "(PRE-UPDATE Assembler build date and time)"
    print_sym_val OLDDISASMTOOLBUILDDATE "(PRE-UPDATE Disassembler build date and time)"

    return 0
}

function do_update ()
{
    local status=

    printf "Updating the AJIT code for GNU Binutils.\n"
    for f in ${FILESTOUPDATE}
    do
	printf "%-30s : %-30s " "Updating" "${f} ..."
	    cp ${AJITBINUTILSHOME}/${f} ${AJITBUILDROOTBINUTILSDIR}/${f} && \
	    status=$?                                                    && \
	    printf "Done.\n"                                             || \
	    (status=$? && printf "COPYing ERROR.\n")
    done

    printf "Updating the AJIT code for GDB.\n"
    for f in ${FILESTOUPDATE}
    do
	printf "%-30s : %-30s " "Updating" "${f} ..."
	    cp ${AJITGDBHOME}/${f} ${AJITBUILDROOTGDBDIR}/${f} && \
	    status=$?                                          && \
	    printf "Done.\n"                                   || \
	    (status=$? && printf "COPYing ERROR.\n")
    done
	
    return $status
}

function do_build ()
{
    local status=

    printf "%-30s : %-30s " "Building" "updated BINUTILS ..."
    cd ${AJITBUILDROOTBINUTILSDIR}
    make install > ajit-binutils.log 2> ajit-binutils.err && \
	status=$?                                         && \
	printf "Done.\n"                                  || \
	printf "BUILD Error.\n"
    cd - > /dev/null 2>&1

    printf "%-30s : %-30s " "Building" "updated GDB ..."
    cd ${AJITBUILDROOTGDBDIR}
    make install > ajit-gdb.log 2> ajit-gdb.err && \
	status=$?                               && \
	printf "Done.\n"                        || \
	printf "BUILD Error.\n"
    cd - > /dev/null 2>&1

    return $status
}

function print_build_status ()
{
    local s=1;
    local t=0;

    NEWASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITBUILDROOTBIN}/${ASMTOOL}")           && \
	NEWDISASMTOOLBUILDDATE=$(eval "${STATTOOL} ${STATTOOLARGS} ${AJITBUILDROOTBIN}/${DISASMTOOL}") && \
	printf "Time stamp of tools after build (if any):\n"                                           && \
	print_sym_val NEWASMTOOLBUILDDATE "(POST-UPDATE Assembler build date and time)"                && \
	print_sym_val NEWDISASMTOOLBUILDDATE "(POST-UPDATE Disassembler build date and time)"

    # The new  tools must  at least have  a different time  stamp than
    # their old version.  This will be  the case if the new tools have
    # been successfully  built.  Otherwise we  will be looking  at the
    # same old tools in the NEW variables above.
    [[ "${NEWASMTOOLBUILDDATE}" != "${OLDASMTOOLBUILDDATE}" ]] # Success if these are different!
    s=$?

    AJITBUILDSTATUS=$( if test $s -eq 0; then printf "OK."; else printf "NOT OK."; fi ) && \
	printf "\n"                                                                     && \
	print_sym_val AJITBUILDSTATUS "(File modification time based overall status of UPDATED code)"

    # printf "=== Build status: s = %d (AJITBUILDSTATUS = %s)\n" $s "${AJITBUILDSTATUS}"

    return $s
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
	${ASMTOOL} ${ASMTOOLARGS} $inasm -o $outobj > ${AJITTESTOBJ}/$lst
	
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

function do_gdb_disassemble ()
{
    local inobj=$1
    local outgdb=$2

    [ ! -f $inobj ] && \
	printf "%-40s %s NOT FOUND.\n" "${GDBTOOL}" $inobj
    [ -f $inasm ] && \
	printf "%-40s %-20s %-20s to %s ...\n" "${GDBTOOL}" "${GDBTOOLARGS}" $(basename $inobj) $(basename $outgdb) && \
	${GDBTOOL} ${GDBTOOLARGS} $inobj > $outgdb
	
    return $?
}

function cleanup ()
{
    /bin/rm -f ${GDBCMDFILE}

    return
}

print_setup
printf "\n"                          && \
    do_update                        && \
    printf "\n"                      && \
    do_build                         && \
    printf "\n"                      && \
    print_build_status               && \
    printf "\n"                      && \
    printf "Running basic tests:\n"  && \
    for a in ${TESTASMS}
    do
	objname=${AJITTESTOBJ}/$(basename $a .s).o   
	disasmname=${AJITTESTDISASM}/$(basename $a .s).dis.s
	gdbasmname=${AJITTESTGDBASM}/$(basename $a .s).gdbdis.s
	
	do_assemble ${a}       ${objname}               && \
	    do_disassemble     ${objname} ${disasmname} && \
	    do_gdb_disassemble ${objname} ${gdbasmname}
    done
cleanup

exit $?


