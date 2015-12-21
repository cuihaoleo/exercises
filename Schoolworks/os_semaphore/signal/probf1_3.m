clear;
fn = @(n) cos(0.5*pi*n)+i*sin(0.5*pi*n)*(uuuuu(n)-uuuuu(n-51));

w = -pi:0.01:pi;
n = 0:1:100;
x = arrayfun(fn, n);
X = dtft(x, n, w);

subplot(2,1,1); plot(w, angle(X)); title('angle');
subplot(2,1,2); plot(w, abs(X)); title('magnitude');
