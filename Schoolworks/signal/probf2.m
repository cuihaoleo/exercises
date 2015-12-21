clear;
fn = @(n) 0.6^abs(n)*(uuuuu(n+10)-uuuuu(n-11));

x1 = [1,2,2,1];
n1 = 0:length(x1)-1;

x2 = [1,2,2,1,1,2,2,1];
n2 = 0:length(x2)-1;

w = -pi:0.01:pi;
X1 = dtft(x1, n1, w);
X2 = dtft(x2, n2, w);

subplot(4,1,1); plot(w, angle(X1)); title('angle1');
subplot(4,1,2); plot(w, abs(X1)); title('magnitude1');

subplot(4,1,3); plot(w, angle(X2)); title('angle2');
subplot(4,1,4); plot(w, abs(X2)); title('magnitude2');
