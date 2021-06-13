SRC=~/AjitProject/Git/AjitRepoV2
rsync -avz $SRC/tools  ./ --exclude "*Backup_Ajit_buildroot_July2015.tar.gz" --exclude "*cross-compiler" --exclude "*glibc"  --exclude "*device_tree" --exclude "*qemu*" --exclude "*.o"  --exclude "*.a"
rsync -avz $SRC/processor/64bit/C_multi_core_multi_thread processor/64bit/   --exclude "*.o" --exclude ".a" 
rsync -avz $SRC/processor/64bit/verification/ processor/64bit/multi_core_verification/  --exclude "*.o" --exclude ".a" 
rsync -avz $SRC/processor/TestEnvironments processor/   --exclude "*.o" --exclude ".a" 
rsync -avz $SRC/processor/verification processor/   --exclude "*.o" --exclude ".a" 
rsync -avz $SRC/processor/validation  processor/   --exclude "*.o" --exclude ".a" 
rsync -avz $SRC/processor/C_reference_model processor/  --exclude "*.o" --exclude ".a" 
rsync -avz $SRC/os/kernels/pico os/kernels/  --exclude "*.o" --exclude ".a" 
