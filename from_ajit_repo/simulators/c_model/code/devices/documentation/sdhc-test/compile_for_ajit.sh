MAIN=main
compileToSparcUclibc.py -g \
                        -U \
                        -N ${MAIN} \
                        -s init.s \
                        -s trap_handlers.s \
                        -c main.c \
                        -D AJIT \
                        -V vmap.txt \
                        -L LinkerScript.lnk \
                        -C sdhc_access/src \
                        -I sdhc_access/include \
                        -C $AJIT_HOME/tools/ajit_access_routines/src \
                        -I $AJIT_HOME/tools/ajit_access_routines/include \
                        -C $AJIT_HOME/tools/minimal_printf_timer/src \
                        -I $AJIT_HOME/tools/minimal_printf_timer/include \
                        -I $AJIT_UCLIBC_HEADERS \
                        -I $AJIT_LIBGCC_INSTALL_DIR/include
# -W bin \
# arguments:  
#                (-h)? 
#                 -N application-name (required.. name of application, used to generate name.elf etc.. 
#                (-W work-area)? (work-area to put compilation results) 
#                (-L linker-script)? (Linker script to be used) 
#                (-I include-dir)* (add include-dir to header search path) 
#                (-C src_dir)* (add src-dir to list of directories from which C source is to be compiled)
#                (-c src_file)* (add src_file to list of C files to be compiled) 
#                (-S assembly_dir)* (add assembly-dir to list of directories where assembly code is to assembled)
#                (-s assembly_file)* (add assembly_file to list of assembly files to be assembled to object code) 
#                (-D define-string)* (add define-string as a define when compiling C files)
#                (-g )? (compile with debug -g flag) 
#                (-U )? (compile with uclibc (in the buildroot) 
#                (-V <vmap-file>) (generate page-table setup assembly code
#                (-F <compiler-option>)* 
#                (-o <0/1/2/3>)* (compile with -O0/1/2/3)
