#!/bin/bash
../bin/traceGen 127.0.0.1 9998 0 >& 9998.pass.log &
../bin/traceGen 127.0.0.1 9999 0 >& 9999.pass.log &
../bin/traceCompareServer -n 4 -p 9998 -p 9999 -e 1024 -c 1024 -l 64 > comp.pass.log &
