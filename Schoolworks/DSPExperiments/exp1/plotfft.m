function y = plotfft(y)

dftn = length(y);
dtftn = 2000;

dft = fftshift(fft(y));
dtft = fftshift(fft(y, dtftn));

dft_x = fftshift(wrap2pi(linspace(0, 2*pi, dftn+1)(1:dftn)));
dtft_x = fftshift(wrap2pi(linspace(0, 2*pi, dtftn+1)(1:dtftn)));

set(gca, 'xtick', [-pi, -pi/2, 0, pi/2, pi])
set(gca, 'xticklabel', [' -pi';'-pi/2';' 0';' pi/2';' pi'])

hold on;
plot(dft_x, abs(dft), '.');
plot(dtft_x, abs(dtft));
ylim([0, inf]);
hold off;

function rad = wrap2pi(angle)
    rad = angle - 2*pi*floor((angle+pi)/(2*pi)); 
