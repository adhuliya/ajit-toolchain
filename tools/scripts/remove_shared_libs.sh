#!/bin/bash
#echo 'kill $(lsof -t -i:' $1 ')'
echo 'Info: recursively removing all .so files'
echo 'find ./ -name "*.so" -type f -delete'
find ./ -name "*.so" -type f  -delete
