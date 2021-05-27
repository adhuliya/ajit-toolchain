#!/bin/sh

a=10;

read ()
{
    for i in `seq $a`
    do
        cat "./test/test${i}.txt" > /dev/null;
    done
}

read