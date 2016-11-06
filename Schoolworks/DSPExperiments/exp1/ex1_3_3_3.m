xbb = @(n,a,f) exp(-a*n) .* sin(2*pi*f*n);

a = 0.1;
n = 0:15;

f_list = [0.0625 0.4375 0.5625];

count = 1;
for f = f_list;
    y = xbb(n,a,f);
    subplot(length(f_list), 2, count*2 - 1);
    stem(n, y);
    title(sprintf('f = %d', f));
    subplot(length(f_list), 2, count*2);
    plotfft(y);
    title('DFT & DTFT');
    count += 1;
endfor
