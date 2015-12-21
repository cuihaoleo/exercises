disp('X1 =');
x1a = [1,-2,3,-4];
n1a = 0:3;
x1b = [4,3,-2,1];
n1b = 0:3;
[x1,n1] = conv_m(x1a, n1a, x1b, n1b);
print_z(x1,n1);

disp('X2 =');
x2a = [1,-2,3,2,1];
n2a = -2:2;
x2b = [1,0,0,0,0,0,-1];
n2b = -3:3;
[x2,n2] = conv_m(x2a, n2a, x2b, n2b);
print_z(x2,n2);

disp('X3 =');
x3a = [1,1,1];
n3a = 0:2;
x3b = x3a;
n3b = n3a;
[x3,n3] = conv_m(x3a, n3a, x3b, n3b);
print_z(x3,n3);

disp('X4 =');
[x4,n4] = conv_m(x1, n1, x2, n2);
for ind=1:length(n4)
    i=n4(ind);
    for jnd=1:length(n3)
        j=n3(jnd);
        if i==j
            x4(ind)+=x3(jnd);
        end
    end
end
print_z(x4,n4);

disp('X4 =');
x4a = [1,0,-3,0,2,0,5,0,-1];
n4a = 1:9;
x4b = [4,3,2,1];
n4b = -4:-1;
[x4,n4] = conv_m(x4a, n4a, x4b, n4b);
print_z(x4,n4);


