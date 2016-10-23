n = -50:50;
x = sin(0.125*pi*n);
subplot(2,2,1); stem(n,x); title('sin(0.125*pi*n)');
[y,m] = dnsample(x,n,4);
subplot(2,2,3); stem(m,y); title('dnsample 4');
axis([m(1),m(end),-1,1]);

x = sin(0.5*pi*n);
subplot(2,2,2); stem(n,x); title('sin(0.5*pi*n)');
[y,m] = dnsample(x,n,4);
subplot(2,2,4); stem(m,y); title('dnsample 4');
axis([m(1),m(end),-1,1]);
