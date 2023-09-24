% sampling rate
fs =  360.0                            % external sampling rate.

% Filter-1 cutoffs
a1 = 4.0;
a2 = 20.0;

% band-pass filter.
b = fir1(127,[a1*2/fs, a2*2/fs]);       % 128 band pass filter.
B = 16;                                 % Number of bits
L = floor(log2((2^(B-1)-1)/max(b)));    % Round towards zero to avoid overflow
bsc = b*2^L;                            % scale 
lpf = round(bsc);                       % round: 

d = 1

freqz(lpf,d,128,40000000)
fp=fopen('bpf.h','a')
fprintf(fp, '\nint16_t BPF_COEFFICIENTS[128] = {')
fprintf(fp, '%d, ', lpf(1:127))
fprintf(fp, '%d}; ', lpf(128))
fclose(fp)
