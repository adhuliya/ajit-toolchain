#!/bin/sh

# The script over write the filesfi they exist in "test"

a=10

write ()
{ 
    for i in `seq $a`
    do
        echo 'test' > "./test/test${i}.txt";
    done
}

write
