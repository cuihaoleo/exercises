clear;
hd = @(wc, a, n) [sin(wc*(n-a))/(pi*n), 1](1+(n==0));

n = 0:40;
a = 20;
wc = 0.5*pi;
h_seq = zeros([1,41]);

for i=n
    h_seq(i+1) = hd(wc,a,i);
end

subplot(2,1,1); stem(n, h_seq);

w = -pi:0.01:pi;
H = dtft(h_seq, n, w);
subplot(2,1,2); plot(w, abs(H)); title('magnitude');
