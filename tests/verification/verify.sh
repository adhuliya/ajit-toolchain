#!/usr/bin/env bash

# The command.
_CMD="validation_outer_env_v3.py -j 1 -t 20000 -C "
_OUT_FILE="validation-testresults.out";

echo "You can review the output in file: $_OUT_FILE";
sleep 3;

echo -e "Testing STARTED: `date`\n\n" > $_OUT_FILE; 


# Verify the 32 bit ajit
_AJIT32_DIR="./ajit32/";

bash -c "$_CMD $_AJIT32_DIR |& tee $_OUT_FILE";
./clean.sh;

     
echo -e "\n\nYou can review the output in file: $_OUT_FILE";

