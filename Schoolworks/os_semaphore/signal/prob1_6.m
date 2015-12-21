clear;
x6 = @(n) 2*sin(0.01*pi*n)*cos(0.5*pi*n);
n_seq = -200:200;
x6_seq = arrayfun(x6, n_seq);
stem(n_seq, x6_seq)