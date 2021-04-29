#!/bin/sh

if [ $1 = -c ]
then
	echo "!!! Are you sure (y/n), please check your pwd..."
	read input
		if [ $input = y ]
		then
			find . ! -iname '*.do' -delete
			echo "cleaned ..."
		elif [ $input = n ]
		then 
			echo "NOT cleaned ..."
			exit 0
		fi
	exit 0

elif [ $# -lt 1 ]
then 
	echo ""
	echo "Error : Please provide input argument "
	echo "Usage : run_modelsim.sh <file.do> OR"
	echo "To view the waveforms: "
	echo "Usage : run_modelsim.sh -w <file.do> OR"
	echo "To clean the directory except dofile:"
	echo "Usage : run_modelsim.sh -c"
	echo ""
	exit 0

elif [ $1 = -w ]
then
	if [ $# -lt 2 ]
	then
		echo ""
		echo "Error : Please provide input argument "
		echo "Usage : run_modelsim.sh -w <file.do> OR"
		echo ""
		exit 0
	fi

	cp $AJIT_PROJECT_HOME/processor/Aa/modelsim/modelsim.ini ./
	vsim -do $2	
	exit 0
fi

cp $AJIT_PROJECT_HOME/processor/Aa/modelsim/modelsim.ini ./
vsim -c -do $1
