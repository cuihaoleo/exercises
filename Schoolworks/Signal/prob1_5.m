clear;
x5 = @(n) 5*(cos(0.49*pi*n)+cos(0.51*pi*n));
n_seq = -200:200;
x5_seq = arrayfun(x5, n_seq);
stem(n_seq, x5_seq)