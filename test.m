syms q1 q0;
syms dq0 dq1
syms a b d
syms g
syms m1 m2 m3 m4 m5 m6 mt
syms I1x I1y I1z
syms I2x I2y I2z I2yz
syms I3x I3y I3z
syms J1 J2 J3 JB
R01 = [q1^2     2*q1+q0  q0; 
     3*q1     q1^3     q0^3+1; 
     q0^2+q1  q1^2-q1  q0^2];

% Tính ??o hàm riêng t?ng ph?n t? c?a ma tr?n theo bi?n q
z = diff(R01,q0)*dq0+diff(R01,q1)*dq1;
% *transpose(A);
t=simplify([z(3,2); z(1,3); z(2,1)]);
T34=rotz(pi-q1)*tran(0,0,-d*2^(0.5))*[1,0,0,0;0,0,1,0;0,-1,0,0;0,0,0,1];
T34X=tranrot((pi-q1),-d*sqrt(2), 0, -pi/2); 
T34Z=rotz(pi-q1)*tran(0,0,-d*2^(0.5))*rotx(-pi/2);
T34Z-T34





