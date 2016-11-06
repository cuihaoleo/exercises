n = 0:50;
dtftn = 2000;

A = 1; T = 1;
xa = @(a, w0, n) A * exp(-a*T*n) .* sin(w0*T*n) .* unitstep(T*n);
ha = zeros(1, 10) + 1;

a = 0.1; w0 = 2.0734;
y = conv(xa(a, w0, n), ha);
ft = fft(y);
ftm = fft(y, dtftn);
subplot(2, 2, 1);
stem(0:length(y)-1, y);
title(sprintf('a=%f, w0=%f', a, w0))
subplot(2, 2, 2);
hold on;
plot(linspace(0, 2*pi, length(y)+1)(1:end-1), abs(ft), '.');
plot(linspace(0, 2*pi, dtftn), abs(ftm));
title('conv and ft')
hold off;

ya = xa(a, w0, n);
ftm = fft(ya, dtftn) .* fft(ha, dtftn);
subplot(2, 2, 4);
plot(linspace(0, 2*pi, dtftn), abs(ftm));
title('directly multiply dtft')
