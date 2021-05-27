#!/bin/sh

# a=1

# until [ $a -gt $1 ]
# do
# 	echo 'test' > "./test/test${a}.txt"
# 	a=`expr $a + 1`
# done

# rm test/*

write ()
{ 
    for i in `seq $1`
    do
        echo 'test' > "./test/test${i}.txt";
    done
}

write