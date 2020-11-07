#!/bin/bash
#echo 'kill $(lsof -t -i:' $1 ')'
kill $(lsof -t -i:$1)
