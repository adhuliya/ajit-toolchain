#!/bin/bash
../bin/traceGen 127.0.0.1 9998 0 >& 9998.fail.log &
../bin/traceGen 127.0.0.1 9999 1 >& 9999.fail.log &
../bin/traceCompareServer -n 4 -p 9998 -p 9999 -e 1024  > comp.fail.log &
