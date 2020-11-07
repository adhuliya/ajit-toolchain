#!/bin/bash

if [ $# -lt 3 ]
then 
	echo ""
	echo "Error : Please provide correct number of input arguments "
	echo "Usage : formality.sh  < design name > < library name >  < clock period >  " 
	echo ""
	exit 0
fi

echo 'Info : Generating formality script files';
buildFormality.py -d $1 -l $2 -p $3 

echo 'Info : Running formal verification on the design with Formality';
source /cad3/synopsys/digitalbashrc
fm_shell -f formality.tcl 

# return exit status on fail
if [ "$?" -ne 0 ]
then
    echo "Error : Formal verification by formality failed"
    exit 1
fi

