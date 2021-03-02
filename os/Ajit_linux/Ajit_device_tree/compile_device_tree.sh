#!/bin/bash
DEVICE_TREE='Ajit_device_tree'
dtc -O asm -o $DEVICE_TREE.S  -V 17 $DEVICE_TREE.dts
echo generated device tree blob $DEVICE_TREE.S 
echo applying patch to device tree blob
patch $DEVICE_TREE.S patch_device_tree
echo patched $DEVICE_TREE.S
echo Preprocessing $DEVICE_TREE.S file to generate assembly $DEVICE_TREE.s file 
sparc-linux-gcc  -O0 -S -g -Wall -Werror -m32 -mcpu=v8 -ffreestanding -nostdlib $DEVICE_TREE.S > $DEVICE_TREE.s
