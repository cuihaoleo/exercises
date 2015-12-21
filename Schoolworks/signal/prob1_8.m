clear;
x8 = @(n) exp(0.01*n)*sin(0.1*pi*n);
n_seq = 0:100;
x8_seq = arrayfun(x8, n_seq);
stem(n_seq, x8_seq)