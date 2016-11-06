function y = unitstep(n)
y = -0 * n;
y(find(n >= 0)) = 1;
