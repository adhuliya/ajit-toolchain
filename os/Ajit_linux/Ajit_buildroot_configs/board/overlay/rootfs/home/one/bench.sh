#!/bin/sh

a=10;

rm ./test/*

write ()
{ 
    for i in `seq $a`
    do
        echo 'test' > "./test/test${i}.txt";
    done
}

read ()
{
    for i in `seq $a`
    do
        cat "./test/test${i}.txt" > /dev/null;
    done
}

write && read
