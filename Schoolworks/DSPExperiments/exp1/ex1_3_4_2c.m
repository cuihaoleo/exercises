n = 0:50;

A = 1; T = 1;
xa = @(a,w0,n) A * exp(-a*T*n) .* sin(w0*T*n) .* unitstep(T*n);
ha = zeros(1, 10) + 1;

a = 0.4; w0 = 2.0734;
y = conv(xa(a, w0, n), ha);
subplot(3, 2, 1);
stem(0:length(y)-1, y);
title(sprintf('a=%f, w0=%f', a, w0))
subplot(3, 2, 2); plotfft(y);

a = 0.1; w0 = 2.0734;
y = conv(xa(a, w0, n), ha);
subplot(3, 2, 3);
stem(0:length(y)-1, y);
title(sprintf('a=%f, w0=%f', a, w0))
subplot(3, 2, 4);
plotfft(y);

a = 0.4; w0 = 1.2516;
y = conv(xa(a, w0, n), ha);
subplot(3, 2, 5);
stem(0:length(y)-1, y);
title(sprintf('a=%f, w0=%f', a, w0))
subplot(3, 2, 6);
plotfft(y);
