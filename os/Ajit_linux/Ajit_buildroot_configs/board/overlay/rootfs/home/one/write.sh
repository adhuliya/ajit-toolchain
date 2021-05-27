#!/bin/sh

# a=1

# until [ $a -gt $1 ]
# do
# 	echo 'test' > "./test/test${a}.txt"
# 	a=`expr $a + 1`
# done

# rm test/*

a=10;

write ()
{ 
    for i in `seq $a`
    do
        echo 'test' > "./test/test${i}.txt";
    done
}

write