clear;
x2 = @(n) sum(arrayfun(@(k) exp(-abs(k)) * delta(n-2*k), -5:5));
n_seq = -10:10;
x2_seq = arrayfun(x2, n_seq);
stem(n_seq, x2_seq)