#!/bin/bash
#echo 'kill $(lsof -t -i:' $1 ')'
echo 'Info: recursively removing all .gsi.aa files'
echo 'find ./ -name ".gsi.aa" -type f -delete'
find ./ -name ".gsi.aa" -type f  -delete
