clear;
x1 = @(n) 3*delta(n+2) + 2*delta(n) - delta(n-3) + 5*delta(n-7);
n_seq = -5:15;
x1_seq = arrayfun(x1, n_seq);
stem(n_seq, x1_seq)