n = 0:20;

yb = [1];
yc = zeros(1, 10) + 1;
ha = yc;
hb = [1 2.5 2.5 1];

y = yb;
y(end+1:length(n)) = 0;
subplot(3, 2, 1);
stem(n, y);
title('y_b, unit pulse');
subplot(3, 2, 2);
plotfft(y);

y = yc;
y(end+1:length(n)) = 0;
subplot(3, 2, 3);
stem(n, y);
title('y_c = h_b = R_{10}, square wave');
subplot(3, 2, 4);
plotfft(y);

y = hb;
y(end+1:length(n)) = 0;
subplot(3, 2, 5);
stem(n, y);
title('h_b');
subplot(3, 2, 6);
plotfft(y);
