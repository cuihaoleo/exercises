function [X] = dtft(x, n, w)
t = w' * n;
t = -i * t;
e = exp(t);
X = e * x';
end
