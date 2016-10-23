clear;
x4 = @(n) exp(0.1*n) * (uuuuu(n+20)-uuuuu(n-10));
n_seq = -20:20;
x4_seq = arrayfun(x4, n_seq);
stem(n_seq, x4_seq)