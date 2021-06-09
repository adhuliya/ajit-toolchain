compileToSparc.py -o 3 -s init.s \
-s $AJIT_PROJECT_HOME/tools/ajit_access_routines/asm/trap_handlers.s \
-C $AJIT_PROJECT_HOME/tools/ajit_access_routines/src \
-I $AJIT_PROJECT_HOME/tools/ajit_access_routines/include \
-C src/ -I include/ -C env/ -I env/ -D ITERATIONS=2000 \
-E core_mark.elf -V core_mark.vars -H core_mark.hex \
-M core_mark.mmap -O core_mark.objdump \
-D CORE_DEBUG=0 \
-D COMPILER_REQUIRES_SORT_RETURN=1 \
-T .text.startup -D PERFORMANCE_RUN=1 \
-F 'fgcse-sm' -L LinkerScript.lnk

