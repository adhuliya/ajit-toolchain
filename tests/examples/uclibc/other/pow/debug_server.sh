
#!/usr/bin/env bash

MAIN=main

ajit_C_system_model -m ${MAIN}.mmap -w ${MAIN}.wtrace -d -r ${MAIN}.results -l ${MAIN}.log -g -p 9998 > debug_server.log 2>&1 &
