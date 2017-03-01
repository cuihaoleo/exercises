N    = 40;       % Order
Beta = 4;        % Window Parameter

win = kaiser(N+1, Beta);
b1  = fir1(N, [0.2 0.4], 'bandpass', win, 'scale');
b2  = fir1(N, [0.6 0.8], 'bandpass', win, 'scale');
b = b1 + b2;
plot(20*log10(abs(fft(b, 2000))));