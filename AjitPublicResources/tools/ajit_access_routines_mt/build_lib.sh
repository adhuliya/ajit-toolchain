if [ "$#" -ne 1 ]; then
    echo "specify device config as one of:  alt default"
    exit
fi

if [[ "$1" ==  "alt" ]]; then
echo "ALT selected " $1
DEFS="  -H -v -nostdlib -D USE_VMAP -D USE_ALTERNATE_DEVICE_ADDRESSES -D HAS_FLOAT "
rm -f lib/libajit_alt.a 
else
echo "DEFAULT selected " $1
DEFS="  -H -v -nostdlib -D USE_VMAP -D HAS_FLOAT "
rm -f lib/libajit_default.a 
fi

echo $DEFS

rm -rf obj_temp
rm -rf obj_assembly
mkdir  obj_temp
mkdir  obj_assembly

#
#
#
sparc-linux-as -Av8  asm/clear_stack_pointers.s -o obj_temp/clear_stack_pointers.o 
sparc-linux-as -Av8  asm/generic_isr_mt.s -o obj_temp/generic_isr_mt.o
sparc-linux-as -Av8  asm/generic_sw_trap_mt.s -o obj_temp/generic_sw_trap_mt.o 
sparc-linux-as -Av8  asm/generic_sys_calls.s -o obj_temp/generic_sys_calls.o 
sparc-linux-as -Av8  asm/mutexes.s -o obj_temp/mutexes.o 
sparc-linux-as -Av8  asm/trap_handlers_for_rtos.s -o obj_temp/trap_handlers_for_rtos.o
sparc-linux-gcc $DEFS -c  -S -m32 -mcpu=v8 -nostdlib -ffreestanding  -O2  -I $AJIT_PROJECT_HOME/tools/ajit_access_routines_mt/include  src/ajit_access_routines.c -o obj_assembly/ajit_access_routines.s 
sparc-linux-as -Av8 obj_assembly/ajit_access_routines.s -o obj_temp/ajit_access_routines.o 
sparc-linux-gcc $DEFS -c  -S -m32 -mcpu=v8 -nostdlib -ffreestanding    -O2  -I $AJIT_PROJECT_HOME/tools/ajit_access_routines_mt/include  src/ajit_generic_sys_calls.c -o obj_assembly/ajit_generic_sys_calls.s 
sparc-linux-as -Av8 obj_assembly/ajit_generic_sys_calls.s -o obj_temp/ajit_generic_sys_calls.o
sparc-linux-gcc $DEFS  -c  -S -m32 -mcpu=v8 -nostdlib -ffreestanding    -O2  -I $AJIT_PROJECT_HOME/tools/ajit_access_routines_mt/include  src/ajit_ipi.c -o obj_assembly/ajit_ipi.s 
sparc-linux-as -Av8 obj_assembly/ajit_ipi.s -o obj_temp/ajit_ipi.o
sparc-linux-gcc $DEFS -c  -S -m32 -mcpu=v8 -nostdlib -ffreestanding    -O2  -I $AJIT_PROJECT_HOME/tools/ajit_access_routines_mt/include  src/ajit_mmap.c -o obj_assembly/ajit_mmap.s 
sparc-linux-as -Av8 obj_assembly/ajit_mmap.s -o obj_temp/ajit_mmap.o
sparc-linux-gcc $DEFS -c  -S -m32 -mcpu=v8 -nostdlib -ffreestanding    -O2  -I $AJIT_PROJECT_HOME/tools/ajit_access_routines_mt/include  src/ajit_mt_irc.c -o obj_assembly/ajit_mt_irc.s 
sparc-linux-as -Av8 obj_assembly/ajit_mt_irc.s -o obj_temp/ajit_mt_irc.o
sparc-linux-gcc $DEFS -c  -S -m32 -mcpu=v8 -nostdlib -ffreestanding    -O2  -I $AJIT_PROJECT_HOME/tools/ajit_access_routines_mt/include  src/ajit_mt_sw_traps.c -o obj_assembly/ajit_mt_sw_traps.s 
sparc-linux-as -Av8 obj_assembly/ajit_mt_sw_traps.s -o obj_temp/ajit_mt_sw_traps.o
sparc-linux-gcc $DEFS -c  -S -m32 -mcpu=v8 -nostdlib -ffreestanding    -O2  -I $AJIT_PROJECT_HOME/tools/ajit_access_routines_mt/include  src/ajit_spi_flash.c -o obj_assembly/ajit_spi_flash.s 
sparc-linux-as -Av8 obj_assembly/ajit_spi_flash.s -o obj_temp/ajit_spi_flash.o
sparc-linux-gcc $DEFS -c  -S -m32 -mcpu=v8 -nostdlib -ffreestanding    -O2  -I $AJIT_PROJECT_HOME/tools/ajit_access_routines_mt/include  src/additional_serial.c -o obj_assembly/additional_serial.s 
sparc-linux-as -Av8 obj_assembly/additional_serial.s -o obj_temp/additional_serial.o
#
# prints are delivered by cortos2
#
#sparc-linux-gcc $DEFS -c  -S -m32 -mcpu=v8 -nostdlib -ffreestanding    -O2  -I $AJIT_PROJECT_HOME/tools/minimal_printf_timer/include  -I $AJIT_PROJECT_HOME/tools/ajit_access_routines_mt/include $AJIT_PROJECT_HOME/tools/minimal_printf_timer/src/core_portme.c -o obj_assembly/core_portme.s 
#sparc-linux-as -Av8 obj_assembly/core_portme.s -o obj_temp/core_portme.o
#sparc-linux-gcc $DEFS -c  -S -m32 -mcpu=v8 -nostdlib -ffreestanding    -O2  -I $AJIT_PROJECT_HOME/tools/minimal_printf_timer/include -I $AJIT_PROJECT_HOME/tools/ajit_access_routines_mt/include $AJIT_PROJECT_HOME/tools/minimal_printf_timer/src/cvt.c -o obj_assembly/cvt.s 
#sparc-linux-as -Av8 obj_assembly/cvt.s -o obj_temp/cvt.o
#sparc-linux-gcc $DEFS -c  -S -m32 -mcpu=v8 -nostdlib -ffreestanding    -O2  -I $AJIT_PROJECT_HOME/tools/minimal_printf_timer/include  -I $AJIT_PROJECT_HOME/tools/ajit_access_routines_mt/include $AJIT_PROJECT_HOME/tools/minimal_printf_timer/src/ee_printf.c -o obj_assembly/ee_printf.s 
#sparc-linux-as -Av8 obj_assembly/ee_printf.s -o obj_temp/ee_printf.o
#sparc-linux-gcc $DEFS -c  -S -m32 -mcpu=v8 -nostdlib -ffreestanding    -O2  -I $AJIT_PROJECT_HOME/tools/alternate_printf/include  -I $AJIT_PROJECT_HOME/tools/ajit_access_routines_mt/include $AJIT_PROJECT_HOME/tools/alternate_printf/src/printf.c -o obj_assembly/printf.s 
#sparc-linux-as -Av8 obj_assembly/printf.s -o obj_temp/printf.o
#
# build the archive
#
sparc-linux-ar -cr lib/libajit_$1.a obj_temp/*.o
echo "created library lib/libajit_$1.a"
# remove the temporaries.
#rm -rf obj_temp
#rm -rf obj_assembly
#mkdir  obj_temp
#mkdir  obj_assembly
