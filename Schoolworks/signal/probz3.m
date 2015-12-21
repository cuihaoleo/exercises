b = [1,1,1,1,1,1];
nb = -2:3;
a = [1,2,1];
na = -1:1;
[p, np, r, nr] = deconv_m(b,nb,a,na);
disp('Polynomial part:');
print_z(p,np);
disp('Remainder part:');
print_z(r,nr);
