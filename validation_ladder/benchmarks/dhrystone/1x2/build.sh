CWD=$(pwd)
./compile_for_ajit_uclibc.sh
cd cpu_0
./compile_for_ajit_uclibc.sh
cd $CWD
cd cpu_1
./compile_for_ajit_uclibc.sh
cd $CWD
cat *.mmap cpu_0/*.mmap cpu_1/*.mmap > aggregated.mmap
