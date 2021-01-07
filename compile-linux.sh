#!/bin/bash

source paths.sh;

cd "`pwd`/from_ajit_repo/os/Ajit_linux/";
./GeneratememMapForAjit.sh && ./vmLinuzToMemmapAtf0004000.sh;
cd -;
