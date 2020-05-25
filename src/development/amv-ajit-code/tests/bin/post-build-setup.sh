#! /bin/bash

#
# Script  to  setup  the  complete development  system  based  on  the
# "buildroot" toolkits  (see: www.buildroot.org).   This is to  be run
# after the buildroot system has been built.
#
# This script is currently under development.
#
# (C) Abhijat Vichare (abhijatv@gmail.com), 2018.
#

#
# Steps:
#
# 1. Choose a top level "HOME".
#    a. Select from command line, or
#       Ask the user with current directory as default.
#    b. Create if non-existent, and change to it.
# 2. Get the processor for which the cross tool chain was built!
#    Either from the command line or ask the user.
# 3. Basic checks:
#    a. Check if the buildroot directory structure exists.
#    b. Check if the buildroot build was successful.
# 4. Final setups:
#    a. Setup executable path for cross tools.
#    b. Setup shared library paths for access to shared C libraries.
# 5. Done!
# 

function init ()
{
    TOPDIR=
    BUILDROOTTARBALLDIR=
    TOPDIRGIVEN="NO"
    BUILDDIRGIVEN="NO"
    BUILDROOTBASEDIR=
    BUILDROOTDIR=
    
    return;
}

function analyse_command_line ()
{
    local args=$*
    local optstr=":vht:b:"
    local argvar		# where we collect the argument

    # Option       Meaning
    # v            Verbose operation (of this script)
    # h            Help
    # t <dirname>  TOP (i.e. home) directory of our build
    # p <name>     Target processor name whose toolchain has been built.
    while getopts $optstr argvar $args
    do
	case $argvar in
	    "v") VERBOSE=1; continue;;
	    "h") script_help; exit;;
	    "t") TOPDIR=${OPTARG}; TOPDIRGIVEN="YES"; continue;;
	    "b") BUILDROOTTARBALLDIR=${OPTARG}; BUILDDIRGIVEN="YES"; continue;;
	    *) printf "Unknown option: %s\n" $OPTARG; exit;;
	esac
    done

    return;
}

function get_buildroot_dir ()
{
    [ "$BUILDDIRGIVEN" == "YES" ]                                                        && \
	BUILDROOTBASEDIR=$(tar ztf ${BUILDROOTTARBALLDIR}                                 | \
				  awk 'BEGIN{FS="/";}{if (NF == 2) printf ("%s\n", $1);}' | \
				  sort                                                    | \
				  uniq)
    
    return;
}

function setup ()
{
    BUILDDIR=${TOPDIR}/build
    get_buildroot_dir
    BUILDROOTDIR=${BUILDDIR}/${BUILDROOTBASE}
    BINDIR=${BUILDROOTDIR}/output/host/usr/bin 
    LIBDIR=${BUILDROOTDIR}/output/host/usr/lib
    SBINDIR=${BUILDROOTDIR}/output/host/usr/sbin
    SHAREDIR=${BUILDROOTDIR}/output/host/usr/share
    SHLIBDIR="${BUILDROOTDIR}/output/host/usr/*buildroot-linux-uclibc/sysroot"
    
    return;
}

function print_setup ()
{
    local strfmt="%-40s: %s\n"
    local intfmt="%-40s: %d\n"
    local numfmt="%-40s: %f\n"

    printf "%s\n" "Your setup is as below:"

    printf "${strfmt}" "TOP directory" "${TOPDIR}"
    printf "${strfmt}" "BUILDROOT tarball location" "${BUILDROOTTARBALLDIR}"
    printf "${strfmt}" "BUILDROOT base directory" "${BUILDROOTDIR}"
    printf "${strfmt}" "BUILDROOT directory" "${BUILDROOTDIR}"
    printf "${strfmt}" "BUILDROOT binaries directory" "${BINDIR}"
    printf "${strfmt}" "BUILDROOT libraries directory" "${LIBDIR}"
    printf "${strfmt}" "BUILDROOT shared libraries directory" "${SHLIBBDIR}"
    
    return;
}

function check_and_change_to_home ()
{
    [ "${TOPDIRGIVEN}" == "NO"  ] && \
	printf "%-70s\n" "Please type the full pathname of the directory" && \
	printf "%-70s\n" "where you would like to setup your development system." && \
	read td && \
	printf "Your Response: %s.\n" "${td}" && \
	TOPDIRGIVEN="YES"
    
    # [ "${TOPDIRGIVEN}" == "YES" ] && [ ! -d ${TOPDIR} ] && mkdir -p ${TOPDIR}

    # cd ${TOPDIR}
    
    return;
}

function check_buildroot_build ()
{
    return;
}

function main ()
{
    init
    analyse_command_line $*
    setup
    check_and_change_to_home
    check_buildroot_build
    
    print_setup

    return;
}

main $*
exit
