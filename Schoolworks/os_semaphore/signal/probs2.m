clear;
N = 40;
xa = @(t) sin(1000*pi*t);
sps = @(T) 0:T:N*T;

t1 = sps(0.0001);
x1_seq = arrayfun(xa, t1);
subplot(3,1,1);
stem(0:N, x1_seq);

t2 = sps(0.001);
x2_seq = arrayfun(xa, t2);
subplot(3,1,2);
stem(0:N, x2_seq);

t3 = sps(0.01);
x3_seq = arrayfun(xa, t3);
subplot(3,1,3);
stem(0:N, x3_seq);
