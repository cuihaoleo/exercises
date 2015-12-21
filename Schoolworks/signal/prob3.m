clear;
n = 0:100;
x = arrayfun(@(n) delta(n), n);
a = [1, -0.5, 0.25];
b = [1, 2, 0, 1];
h = filter(b, a, x);

figure
subplot(2,1,1)
stem(n, h)

n2 = 0:200;
x2 = arrayfun(@(n) (5+3*cos(0.2*pi*n)+4*sin(0.6*pi*n))*uuuuu(n), n2);
y2 = filter(b, a, x2);

subplot(2,1,2)
stem(n2, y2)