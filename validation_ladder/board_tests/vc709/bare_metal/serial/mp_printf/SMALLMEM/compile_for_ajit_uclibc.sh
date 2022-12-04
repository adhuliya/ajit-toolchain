AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
PT_ALT=$AJIT_PROJECT_HOME/tools/alternate_printf
TEXTBASE=0x0
DATABASE=0x40000
VMAP=VMAP.TXT
CLKFREQ=80000000
#1 generate linker script
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#2 compile the application
compileToSparcUclibc.py -U -g -V $VMAP -D USE_VMAP -N printf_test\
			-s ../init.s -s $AAR/asm/trap_handlers.s -s $AAR/asm/generic_sw_trap_mt.s \
			-s $AAR/asm/generic_sys_calls.s \
			-L customLinkerScript.lnk -D HAS_FLOAT\
			-I $AAR/include -I $PT/include -I $PT_ALT/include \
			-c ../main.c -C $AAR/src -C $PT/src -C $PT_ALT/src  -D VA_DATA_SECTION_START=$DATABASE -D CLK_FREQUENCY=$CLKFREQ
