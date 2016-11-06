n = 0:20;

yb = [1];
hb = [1 2.5 2.5 1];

y = yb;
y(end+1:length(n)) = 0;
subplot(3, 2, 1); stem(n, y); title('y_b');
subplot(3, 2, 2); plotfft(y);

y = hb;
y(end+1:length(n)) = 0;
subplot(3, 2, 3); stem(n, y); title('h_b');
subplot(3, 2, 4); plotfft(y);

y = conv(yb, hb);
y(end+1:length(n)) = 0;
subplot(3, 2, 5); stem(n, y); title('conv(y_b, h_b)');
subplot(3, 2, 6); plotfft(y);
