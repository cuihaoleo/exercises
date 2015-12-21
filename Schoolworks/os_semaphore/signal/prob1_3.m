clear;
x3 = @(n) 10*uuuuu(n) - 5*uuuuu(n-5) - 10*uuuuu(n-10) + 5*uuuuu(n-15);
n_seq = -20:20;
x3_seq = arrayfun(x3, n_seq);
stem(n_seq, x3_seq)