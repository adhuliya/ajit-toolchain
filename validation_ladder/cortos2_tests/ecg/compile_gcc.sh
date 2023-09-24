DEFS=" -D GCC -D NOUSE_CORTOS -D SINGLE_THREAD "
INCL=" -I ./include -I ./fft -I ../../../application_development/thread_channel/include"
CCFLAGS=" -g " 
gcc -c src/backend.c -o obj/backend.o $DEFS $INCL $CCFLAGS
gcc -c src/band_pass_filter.c -o obj/band_pass_filter.o $DEFS $INCL $CCFLAGS
gcc -c src/best_fit.c -o obj/best_fit.o $DEFS $INCL $CCFLAGS
gcc -c src/frontend.c -o obj/frontend.o $DEFS $INCL $CCFLAGS
gcc -c src/hermite.c  -o obj/hermite.o $DEFS $INCL $CCFLAGS
gcc -c src/qrs_peak_detect.c -o obj/qrs_peak_detect.o $DEFS $INCL $CCFLAGS
#gcc -c src/result_buffer.c  -o obj/result_buffer.o $DEFS $INCL $CCFLAGS
gcc -c src/moving_average.c  -o obj/moving_average.o $DEFS $INCL $CCFLAGS
gcc -c src/derivative.c  -o obj/derivative.o $DEFS $INCL $CCFLAGS
gcc -c fft/fft.c  -o obj/fft.o $DEFS $INCL $CCFLAGS
gcc -c fft/utils.c  -o obj/utils.o $DEFS $INCL $CCFLAGS
gcc -o bin/ecg_gcc obj/*.o  -lm  $CCFLAGS
