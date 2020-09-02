#!/bin/sh
export PATH=${PATH}:/home/nehak/AJITproject/AjitRepoV2/tools/cross-compiler/buildroot_cross_compiler/usr/bin

echo "Generating init executable"
sparc-linux-gcc -static init_executable.c -o init
mkdir initramfs_contents
cd initramfs_contents
mv ../init ./
sudo chown root:root init

echo "Generating dev/ nodes"
mkdir dev
cd dev
sudo mknod null c 1 3
sudo mknod zero c 1 5
sudo mknod tty c 5 0
sudo mknod console c 5 1
sudo mknod ttyprintk c 5 3
sudo mknod tty0 c 4 0 
cd ../
sudo find . | cpio -H newc -o > ../initramfs.cpio
cd ../
echo " Created initramfs archive " $PWD"/initramfs.cpio"


