#stdbuf -o 0  ajit_cpu_uarch_HW_env_v1 -m Output/mem_map_for_initial_PC_f0004000.txt  -r Results.txt -l Log.txt 2>&1 |tee ./Ajit_FPGA_linux_boot_LOG.txt
stdbuf -o 0  ajit_cpu_uarch_FPGA_C_compare_env_v1 -m Output/mem_map_for_initial_PC_f0004000.txt  -r Results.txt -l Log.txt -s 2>&1 |tee ./Ajit_twin_cpu_linux_boot_LOG.txt

