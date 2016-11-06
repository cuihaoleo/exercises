L = 50;
n = 0:L;

A = 444.128;
a = 50 * sqrt(2) * pi;
w0 = 50 * sqrt(2) * pi;
xa = @(t) A * exp(-a*t) .* sin(w0*t) .* unitstep(t);

freq_list = [1000 300 400];

count = 1;
for freq = freq_list;
    t = n / freq;
    y = xa(t);
    subplot(length(freq_list), 2, count*2 - 1);
    stem(t, y);
    title(sprintf('F = %d Hz', freq));
    subplot(length(freq_list), 2, count*2);
    plotfft(y);
    title('DFT & DTFT');
    count += 1;
endfor
