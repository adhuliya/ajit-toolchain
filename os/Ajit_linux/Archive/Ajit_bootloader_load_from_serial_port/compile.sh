COMMONSERIAL=$AJIT_PROJECT_HOME/processor/C/validation/serial_and_IRC_validation/common_serial_routines
SPARCSTDIO=$AJIT_PROJECT_HOME/os/kernels/pico
AJITHWCONFIG=$AJIT_PROJECT_HOME/processor/C/common/include
LINKER=$AJIT_PROJECT_HOME/tools/linker/bootRomLinkerScript.lnk
compileToSparc.py -W ./ -E Ajit_bootloader.elf -H Ajit_bootloader.hexdump -M Ajit_bootloader.mmap -O Ajit_bootloader.objdump -I ./ -I $COMMONSERIAL/include -I $SPARCSTDIO/include -I$AJITHWCONFIG -C ./ -C $COMMONSERIAL/src/ -C $SPARCSTDIO/src -V Ajit_bootloader.vars  
