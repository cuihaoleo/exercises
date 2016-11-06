xaa = @(n,p,q) exp(-(n-p).^2/q);

q = 8;
n = 0:15;

p_list = [8 13 14];

count = 1;
for p = p_list;
    y = xaa(n,p,q);
    subplot(length(p_list), 2, count*2 - 1);
    stem(n, y);
    title(sprintf('p = %d', p));
    subplot(length(p_list), 2, count*2);
    plotfft(y);
    title('DFT & DTFT');
    count += 1;
endfor
