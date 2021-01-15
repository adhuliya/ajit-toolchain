#!/usr/bin/env bash

MAIN=main
_PORT=9998

ajit_C_system_model -m ${MAIN}.mmap -w ${MAIN}.wtrace -d -r ${MAIN}.results -l ${MAIN}.log -g -p $_PORT > debug_server.log 2>&1 &
