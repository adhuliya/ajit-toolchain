#!/usr/bin/env python3
import os
import sys
import getopt
import os.path

#Set directory where verification folder exists
CURRDIR='/home/gauri/ajit-toolchain/from_ajit_repo'
CMD = "validation_outer_env_v3.py -j 1 -t 20000 -C {dir}"

#Only 1 argument for the script
arg_list = sys.argv[1]    

if arg_list == '-32' :
    os.system(CMD.format(dir="/verification/ajit32/"))
     
# if arg_list == '-control' :
#     os.system("validation_outer_env_v3.py -j 1 -t 20000 -C " + CURRDIR + "/verification/ajit32/instruction_tests/control_transfer/")    
# 
# if arg_list == '-data' :
#     os.system("validation_outer_env_v3.py -j 1 -t 20000 -C " + CURRDIR + "/verification/ajit32/instruction_tests/data_transfer/")
# 
# if arg_list == '-float' :
#     os.system("validation_outer_env_v3.py -j 1 -t 20000 -C " + CURRDIR + "/verification/ajit32/instruction_tests/floating_point/")
# 
# if arg_list == '-integer' :
#     os.system("validation_outer_env_v3.py -j 1 -t 20000 -C " + CURRDIR + "/verification/ajit32/instruction_tests/integer_alu/")
# 
# if arg_list == '-misc' :
#     os.system("validation_outer_env_v3.py -j 1 -t 20000 -C " + CURRDIR + "/verification/ajit32/instruction_tests/misc/")
# 
# if arg_list == '-pipe' :
#     os.system("validation_outer_env_v3.py -j 1 -t 20000 -C " + CURRDIR + "/verification/ajit32/instruction_tests/pipeline_verification/")
# 
# if arg_list == '-cache'
#         os.system("validation_outer_env_v3.py -j 1 -t 20000 -C " + CURRDIR + "/verification/ajit32/other_tests/cache_basic_validation/")
# 
# if arg_list == '-Ctests'
#         os.system("validation_outer_env_v3.py -j 1 -t 20000 -C " + CURRDIR + "/verification/ajit32/other_tests/C_tests/")
# 
# if arg_list == '-memory'
#         os.system("validation_outer_env_v3.py -j 1 -t 20000 -C " + CURRDIR + "/verification/ajit32other_tests/MemoryTest/")
# 
# if arg_list == '-mmu'
#         os.system("validation_outer_env_v3.py -j 1 -t 20000 -C " + CURRDIR + "/verification/ajit32/other_tests/mmu_validation/")
# 
# if arg_list == '-serial'
#         os.system("validation_outer_env_v3.py -j 1 -t 20000 -C " + CURRDIR + "/verification/ajit32/other_tests/serial_and_IRC_validation/")
# 
# if arg_list == '-template'
#         os.system("validation_outer_env_v3.py -j 1 -t 20000 -C " + CURRDIR + "/verification/ajit32/other_tests/template/")
# 
# if arg_list == '-timer'
#         os.system("validation_outer_env_v3.py -j 1 -t 20000 -C " + CURRDIR + "/verification/ajit32/other_tests/timer_and_IRC_validation/")

