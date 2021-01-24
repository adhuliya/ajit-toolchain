# Script for producing Linux image for AJIT processor

echo "================================================="
echo "Executing Step 1 of AJIT Linux build, log can be found in build-logs/ directory"
./GeneratememMapForAjit.sh |& tee ./build-logs/GenMemMapScript.log
echo "Finished Step 1 of AJIT Linux build"

echo "================================================="
echo "Executing Step 2 of AJIT Linux build, log can be found in build-logs/ directory"
./vmLinuzToMemmapAtf0004000.sh |& tee ./build-logs/vmLinuzF0004000.log
echo "Finished Step 2 of AJIT Linux build"

cp Generated_memory_map.f0004000/Output.f0004000/boot_loader_plus_kernel.mmap ./linux_boot/boot_loader_plus_kernel_mmap/
echo "boot_loader_plus_kernel.mmap file copied"

echo "================================================="
echo "Executing Step 3 of AJIT Linux build, log can be found in ./linux_boot/ directory"
cd linux_boot
./compile.sh |& tee finalImagebuild.log
echo "Finished Step 3 of AJIT Linux build"

