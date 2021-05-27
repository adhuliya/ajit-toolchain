#!/bin/sh

# # writing
# for i in {0..1000}; 
# do 
# 	echo 'test' > "./test/test${i}.txt";
# done
# # reading
# for i in {0..1000};
# do 
# 	cat "./test/test${i}.txt" > /dev/null;
# done

rm ./test/*
a=1

until [ $a -gt 10 ]
do
	echo 'test' > "./test/test${a}.txt"
	a=`expr $a + 1`
done

until [ $a -gt 10 ]
do
	cat "./test/test${a}.txt" > /dev/null;
	a=`expr $a + 1`
done

# time -v `sh write.sh $1`

# time sh read.sh

# rm ./test/*

# write ()
# { 
#     for i in `seq 10`
#     do
#         echo 'test' > "./test/test${i}.txt";
#     done
# }

# read ()
# {
#     for i in `seq 10`
#     do
#         cat "./test/test${i}.txt" > /dev/null;
#     done
# }

# write && read
# write
# read