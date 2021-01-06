
#!/usr/bin/env bash

NAME=test_pow

ajit_C_system_model -m ${NAME}.mmap -w ${NAME}.wtrace -d -r ${NAME}.results -l ${NAME}.log -g -p 9998 > debug_server.log 2>&1 &
