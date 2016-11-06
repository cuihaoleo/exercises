n = 0:20;

yc = zeros(1, 10) + 1;
ha = zeros(1, 10) + 1;

y = ha;
y(end+1:length(n)) = 0;
subplot(5, 2, 1); stem(n, y); title('h_a');
subplot(5, 2, 2); plotfft(y);

y = yc;
y(end+1:length(n)) = 0;
subplot(5, 2, 3); stem(n, y); title('y_c');
subplot(5, 2, 4); plotfft(y);

y = conv(yc, ha);
y(end+1:length(n)) = 0;
subplot(5, 2, 5); stem(n, y); title('conv(y_c, h_a)')
subplot(5, 2, 6); plotfft(y);

yc = zeros(1, 5) + 1;
y = yc;
y(end+1:length(n)) = 0;
subplot(5, 2, 7); stem(n, y); title('y_c"');
subplot(5, 2, 8); plotfft(y);

y = conv(yc, ha);
y(end+1:length(n)) = 0;
subplot(5, 2, 9); stem(n, y); title('conv(y_c", h_a)')
subplot(5, 2, 10); plotfft(y);
