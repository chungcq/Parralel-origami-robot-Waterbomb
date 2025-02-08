function [s,sdot,sddot]= trajectory_hinhthang(t,L,T)
% tao hàm s van toc hinh thang can

% T=10;
% L=10;
a=4*L/T^2;
ta=0.5*T-sqrt(a^2*T^2-4*a*L)/(2*a);
vmax=a*ta;
% vmax=50;
% ta=5;
if (0<=t&&t<=ta)
    s= 0.5*a*t^2;
    sdot= a*t;
    sddot=a;
end
if (ta<t&&t<T-ta)
    s= 0.5*a*ta^2+vmax*(t-ta);
    sdot= vmax;
    sddot=0;
end
if (T-ta<=t&&t<=T)
    s= L-0.5*a*(T-t)^2;
    sdot= vmax-a*(t-T+ta);
    sddot=-a;
end

end
