function [] = print_z(x,n)
for i=1:length(x)
    if abs(x(i)) > 0
        printf('%+gz^%d ', x(i), -n(i));
    end
end
printf('\n');
