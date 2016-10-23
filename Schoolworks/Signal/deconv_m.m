function[p,np,r,nr]=deconv_m(b,nb,a,na) 
npb=nb(1)-na(1); 
nr=nb; 
[p,r]=deconv(b,a); 
np=[npb:npb+length(p)-1];
