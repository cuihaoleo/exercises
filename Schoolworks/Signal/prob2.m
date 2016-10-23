clear;
x = @(n) 0.9^n;
y = @(n) 0.8^(-n);
nx_seq = 0:20;
ny_seq = -20:0;
x_seq = arrayfun(x, nx_seq);
y_seq = arrayfun(y, ny_seq);
[gxx, gxx_n] = conv_m(x_seq, nx_seq, x_seq, nx_seq);
[gxy, gxy_n] = conv_m(x_seq, nx_seq, y_seq, ny_seq);

figure
subplot(2,1,1)
stem(gxx_n, gxx)
subplot(2,1,2)
stem(gxy_n, gxy)