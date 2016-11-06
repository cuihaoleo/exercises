xaa = @(n,p,q) exp(-(n-p).^2/q);

p = 8;
n = 0:15;

q_list = [2 4 9];

count = 1;
for q = q_list;
    y = xaa(n,p,q);
    subplot(length(q_list), 2, count*2 - 1);
    stem(n, y);
    title(sprintf('q = %d', q));
    subplot(length(q_list), 2, count*2);
    plotfft(y);
    title('DFT & DTFT');
    count += 1;
endfor
