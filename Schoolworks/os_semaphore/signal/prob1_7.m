clear;
x7 = @(n) exp(-0.05*n)*sin(0.1*pi*n+pi/3);
n_seq = 0:100;
x7_seq = arrayfun(x7, n_seq);
stem(n_seq, x7_seq)