#!/bin/busybox sh

a=10;

read ()
{
    for i in `seq $a`
    do
        echo ""
        echo "Interration $i"
        cat "/proc/interrupts"
        echo "----------------------------------------"
        date
    done
}

read