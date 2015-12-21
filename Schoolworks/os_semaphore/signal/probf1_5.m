clear;

w = -pi:0.01:pi;
x = [4 3 2 1 -1 -2 -3 -4];
n = 0:1:length(x)-1;
X = dtft(x, n, w);

subplot(2,1,1); plot(w, angle(X)); title('angle');
subplot(2,1,2); plot(w, abs(X)); title('magnitude');
