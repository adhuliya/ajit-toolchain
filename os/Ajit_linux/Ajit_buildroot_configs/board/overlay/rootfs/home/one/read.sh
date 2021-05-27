#!/bin/sh

# a=1

# until [ $a -gt $1 ]
# do
# 	cat "./test/test${a}.txt" > /dev/null;
# 	a=`expr $a + 1`
# done

a=10;

read ()
{
    for i in `seq $a`
    do
        cat "./test/test${i}.txt" > /dev/null;
    done
}

read