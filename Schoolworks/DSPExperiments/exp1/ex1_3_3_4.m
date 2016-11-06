n = 0:7;
ycc = [1:4 4:-1:1];
ydd = [4:-1:1 1:4];

y = ycc;
subplot(4, 2, 1);
stem(n, y);
title('x_{cc}');
subplot(4, 2, 2);
plotfft(y);

y = ydd;
subplot(4, 2, 3);
stem(n, y);
title('x_{dd}');
subplot(4, 2, 4);
plotfft(y);

n = 0:15;

y = [ycc zeros(1,8)];
subplot(4, 2, 5);
stem(n, y);
title('x_{cc} (0-pad)');
subplot(4, 2, 6);
plotfft(y);

y = [ydd zeros(1,8)];
subplot(4, 2, 7);
stem(n, y);
title('x_{dd} (0-pad)');
subplot(4, 2, 8);
plotfft(y);
