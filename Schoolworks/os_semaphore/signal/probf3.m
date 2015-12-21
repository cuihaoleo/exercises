clear;

R = @(m,n) [0,1]((0<=n & n<m) + 1);
C = @(m,n) 0.5*(1-cos(2*pi*n/(m-1)))*R(m,n);
T = @(m,n) (1-abs(m-1-2*n)/(m-1))*R(m,n);
H = @(m,n) (0.54-0.46*cos(2*pi*n/(m-1)))*R(m,n);

w = -pi:0.01:pi;
n_seq = 0:99;


hold(subplot(2,2,1), 'on');
hold(subplot(2,2,2), 'on');
hold(subplot(2,2,3), 'on');
hold(subplot(2,2,4), 'on');
hold all;

for m=[10,25,50,101]
    r = c = t = h = zeros([1,100]);
    for i=1:length(n_seq)
        r(i) = R(m,i);
        c(i) = C(m,i);
        t(i) = T(m,i);
        h(i) = H(m,i);
    end
    rr = dtft(r, n_seq, w);
    rr = rr / max(abs(rr));
    cc = dtft(c, n_seq, w);
    cc = cc / max(abs(cc));
    tt = dtft(t, n_seq, w);
    tt = tt / max(abs(tt));
    hh = dtft(h, n_seq, w);
    hh = hh / max(abs(hh));
    subplot(2,2,1);
    plot(w, rr, color=sprintf('%d',m), 'DisplayName', [sprintf('R, m=%d', m)]);
    subplot(2,2,2);
    plot(w, cc, color=sprintf('%d',m), 'DisplayName', [sprintf('C, m=%d', m)]);
    subplot(2,2,3);
    plot(w, tt, color=sprintf('%d',m), 'DisplayName', [sprintf('T, m=%d', m)]);
    subplot(2,2,4);
    plot(w, hh, color=sprintf('%d',m), 'DisplayName', [sprintf('H, m=%d', m)]);
end

legend(subplot(2,2,1), 'show');
legend(subplot(2,2,2), 'show');
legend(subplot(2,2,3), 'show');
legend(subplot(2,2,4), 'show');
