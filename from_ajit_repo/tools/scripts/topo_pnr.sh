#!/bin/bash
# Author: Kalyani Ch.

if [ $# -lt 5 ]
then 
	echo ""
	echo "Error : Please provide correct number of input arguments "
	echo "Usage : topo_pnr.sh  < design name > < library name >  < clock period (ns) >  " 
	echo "< dft y/n> < pnr y/n > < top y/n >"
	echo "Ex: $ ./topo_pnr.sh iunit teu_iunit 15 y n n"
	echo ""
	exit 0
fi

if [ -d "work" ]; then
  rm -r work
fi

#if [ -d syn_topo ]; then
#  rm -r syn_topo
#fi

#if [ ! -d "vhdl_files" ]; then
#  mkdir vhdl_files
#fi

#echo 'Info : Copying VHDL files';
#cd vhdl_files
#source chip_vhdl_files.sh
#cd ../


mkdir -p ${1}_${3}_reports
mkdir -p ${1}_${3}_op_data

if [ $4 = "y" ] 
then
	echo 'Info : Generating DC-topo script files with DFT insertion';
	buildDFT.py -d $1 -l $2 -p $3 -t $6

	echo 'Info : Synthesizing the design with DC-topo';
	source /cad3/synopsys/digitalbashrc
	dc_shell -topo -f dft.tcl | tee dft_terminal.log
else
	echo 'Info : Generating DC-topo script files';
	buildTOPO.py -d $1 -l $2 -p $3 

	echo 'Info : Synthesizing the design with DC-topo';
	source /cad3/synopsys/digitalbashrc
	dc_shell -topo -f topo.tcl | tee topo_terminal.log
fi


# return exit status on fail
if [ "$?" -ne 0 ]
then
    echo "Error : DC-topo failed"
    exit 1
fi


if [ $5 = "y" ] 
then
	mkdir -p ${1}_pnr_reports
        echo 'Info : Generating script file for PNR on the design';
	buildICC.py -d $1 -p $3 -t $6
	cp $AJIT_PROJECT_HOME/tools/scripts/macro_rings.tpl ./
        echo 'Info : Starting PNR on the design';
	icc_shell -f icc.tcl | tee icc_transcript.log
	
	if [ "$?" -ne 0]
	then
	    echo 'Error : ICC-PNR failed'
	    exit 1
	fi
fi


