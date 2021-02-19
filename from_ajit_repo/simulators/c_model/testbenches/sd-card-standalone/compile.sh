#source the ahir_bashrc before running this
source path.sh
gcc -o marchtest_sdcard src/marchtest-sdcard.c src/sd.c src/Ancillary.c \
-I include/ -I $AHIR_RELEASE/include -L $AHIR_RELEASE/lib -lPipeHandler -lBitVectors -lpthread -lm
