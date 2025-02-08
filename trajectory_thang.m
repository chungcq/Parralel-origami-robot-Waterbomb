function rEvE = trajectory_thang(t)
global rA rB T
%% ------------- Chuyen dong thang A-->B theo luat s(t) -------------------
L= norm(rB-rA);
u=(rB-rA)/L;
[s, sdot, sddot] = trajectory_hinhthang(t,L,T);
%% ===================== chuyen dong tren duong thang =====================
% Toa do diem cuoi 
rE = rA + s*u; 
vE = sdot*u; 
rEvE = [rE; vE];
end
