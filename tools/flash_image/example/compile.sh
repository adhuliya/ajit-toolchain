# First compile the application..  
#  application starts at virtual address 0x40000000
#  (see the vmap file)
cd code
# generate mmap.remapped file for application.
./compile_for_ajit.sh
# generate assembly code for mmap..
../../bin/mmapToAssy rpn.mmap.remapped rpn_assy.s  0x40000000
# Go to bootstrap area
cd ../bootstrap
# note: bootstrap/compile_for_ajit.sh uses rpn_assy.s
# and ../asm/bootstrap.s
# produces mmap file for bootstrap.
./compile_for_ajit.sh
