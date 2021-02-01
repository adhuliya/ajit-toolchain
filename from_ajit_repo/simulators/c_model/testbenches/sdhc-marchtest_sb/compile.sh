#source the ahir_bashrc before running this
source path.sh
gcc -o marchtest_sdhc src/marchtest.c src/sdhc.c src/Sdhc_helper.c src/Device_utils.c src/Ancillary.c \
-I include/ -I $AHIR_RELEASE/include -L $AHIR_RELEASE/lib -lPipeHandler -lBitVectors -lpthread -lm
