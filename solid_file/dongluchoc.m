syms q0 q1
syms dq0 dq1
syms a b d
syms g
syms m1 m2 m3 m4 m5 m6 mt
syms I1x I1y I1z
syms I2x I2y I2z I2yz
syms I3x I3y I3z
syms J1 J2 J3 JB
%global a b d m1 m2 m3 m4 m5 m6 mt I1x I1y I1z I2x I2y I2z I2yz I3x I3y I3z g
q=[q0; q1];
dq=[dq0; dq1];
g0=[0;-g;0];
% TOA DO KHOI TAM KHAU I TRONG HE I (4x1)
uc11=[b; (-sqrt(2)*(a + 2*d))/4; (sqrt(2)*(a + 2*d))/4; 1];
uc22=[-b; -a/3; 2*a/3; 1];
uc33=[b; -a/(3*sqrt(2)); a/sqrt(2); 1];
uc44=[b; (-sqrt(2)*(a + 2*d))/4; (sqrt(2)*(a + 2*d))/4; 1];
uc55=[-b; -a/3; 2*a/3; 1];
uc66=[b; -a/(3*sqrt(2)); a/sqrt(2); 1];
% MOMEN QUAN TINH KHAU I TRONG HE I
IC11=diag([I1x,I1y,I1z]);
IC22=[ I2x 0 0; 0 I2y I2yz; 0 I2yz I2z];
IC33=diag([I3x,I3y,I3z]);
IC44=IC11;
IC55=IC22;
IC66=IC33;
% doan nay la tinh theo anh hai
IC1=[2*JB 0;
     0    0];
IC2=[ J1  0         0;
      0  (J2+J3)/2 (J3-J2)/2;
      0  (J3-J2)/2 (J2+J3)/2];
IC3=[ J1 0  0;
      0  J2 0;
      0  0  J3];
IC5=IC2;
IC6=IC3;
% tinh ma tran thuan nhat
T01T=[ cos(q0-pi/2) -cos(pi/4)*sin(q0-pi/2)  sin(pi/4)*sin(q0-pi/2)  0;
       sin(q0-pi/2)  cos(pi/4)*cos(q0-pi/2) -sin(pi/4)*cos(q0-pi/2)  0;
       0             sin(pi/4)               cos(pi/4)               0;
       0             0                       0                       1];
T01R=[ 1 0 0 -2*b;
       0 1 0 0;
       0 0 1 -(a+d)*sqrt(2);
       0 0 0 1];
T01=simplify(T01T*T01R);
T12=[ cos(2*pi-q1) -sin(2*pi-q1)*(1/sqrt(2)) sin(2*pi-q1)*-1/sqrt(2) 2*b*cos(2*pi-q1);
      sin(2*pi-q1)  cos(2*pi-q1)*(1/sqrt(2)) cos(2*pi-q1)*1/sqrt(2)  2*b*sin(2*pi-q1);
      0            sin(-pi/4)              cos(-pi/4)             d*sqrt(2);
      0            0                       0                      1];
T23=[ cos(2*q0) -sin(2*q0)*(1/sqrt(2)) sin(2*q0)*-1/sqrt(2) -2*b*cos(2*q0);
      sin(2*q0)  cos(2*q0)*(1/sqrt(2)) cos(2*q0)*1/sqrt(2)  -2*b*sin(2*q0);
      0            sin(-pi/4)              cos(-pi/4)             0;
      0            0                       0                      1];
T34=[ cos(pi+q1)  0                       sin(pi+q1)*-1         0;
      sin(pi+q1)  0                       cos(pi+q1)            0;
      0            -1                      0                      -d*sqrt(2);
      0            0                       0                      1];
T45=[ cos(2*pi-q1) -sin(2*pi-q1)*(1/sqrt(2)) sin(2*pi-q1)*-1/sqrt(2) 2*b*cos(2*pi-q1);
      sin(2*pi-q1)  cos(2*pi-q1)*(1/sqrt(2)) cos(2*pi-q1)*1/sqrt(2)  2*b*sin(2*pi-q1);
      0             sin(-pi/4)               cos(-pi/4)              d*sqrt(2);
      0             0                        0                       1];
T56=[ cos(2*q0) -sin(2*q0)*(1/sqrt(2)) sin(2*q0)*-1/sqrt(2) -2*b*cos(2*q0);
      sin(2*q0)  cos(2*q0)*(1/sqrt(2)) cos(2*q0)*1/sqrt(2)  -2*b*sin(2*q0);
      0          sin(-pi/4)            cos(-pi/4)             0;
      0          0                     0                      1];
T61=[ cos(pi+q1)  0                       sin(pi+q1)*-1         0;
      sin(pi+q1)  0                       cos(pi+q1)            0;
      0           -1                      0                     -d*sqrt(2);
      0           0                       0                     1];
T02=simplify(T01*T12);
T03=simplify(T02*T23);
T04=simplify(T03*T34);
T05=simplify(T04*T45);
T06=simplify(T05*T56);
% T61=simplify(T06*T61);
R01=T01(1:3, 1:3);
R02=T02(1:3, 1:3);
R03=T03(1:3, 1:3);
R04=T04(1:3, 1:3);
R05=T05(1:3, 1:3);
R06=T06(1:3, 1:3);
% R61=T61(1:3, 1:3);
rc10=simplify(T01*uc11); % toa do khoi tam khau 1 trong he co so( toa do thuan) 4x1
rc20=simplify(T02*uc22);
rc30=simplify(T03*uc33);
rc40=simplify(T04*uc44);
rc50=simplify(T05*uc55);
rc60=simplify(T06*uc66);
JT1= simplify(jacobian(rc10(1:3), q));  % MA TRAN JACOBI TINH TIEN
JT2= simplify(jacobian(rc20(1:3), q));
JT3= simplify(jacobian(rc30(1:3), q));
JT4= simplify(jacobian(rc40(1:3), q));
JT5= simplify(jacobian(rc50(1:3), q));
JT6= simplify(jacobian(rc60(1:3), q));
% ma tran w song 3x3
W1s=simplify(expand((diff(R01,q0)*dq0+diff(R01,q1)*dq1)*R01.'));
W2s=simplify(expand((diff(R02,q0)*dq0+diff(R02,q1)*dq1)*R02.'));
W3s=simplify(expand((diff(R03,q0)*dq0+diff(R03,q1)*dq1)*R03.'));
W4s=simplify(expand((diff(R04,q0)*dq0+diff(R04,q1)*dq1)*R04.'));
W5s=simplify(expand((diff(R05,q0)*dq0+diff(R05,q1)*dq1)*R05.'));
W6s=simplify(expand((diff(R06,q0)*dq0+diff(R06,q1)*dq1)*R06.'));
W1=[W1s(3,2); W1s(1,3); W1s(2,1)]; % ma tran w 3x1
W2=[W2s(3,2); W2s(1,3); W2s(2,1)];
W3=[W3s(3,2); W3s(1,3); W3s(2,1)];
W4=[W4s(3,2); W4s(1,3); W4s(2,1)];
W5=[W5s(3,2); W5s(1,3); W5s(2,1)];
W6=[W6s(3,2); W6s(1,3); W6s(2,1)];
JR1=simplify(jacobian(W1, dq)); %3x2
JR2=simplify(jacobian(W2, dq));
JR3=simplify(jacobian(W3, dq));
JR4=simplify(jacobian(W4, dq));
JR5=simplify(jacobian(W5, dq));
JR6=simplify(jacobian(W6, dq));
% CACH 1 TINH M G
Ms=m1*transpose(JT1)*JT1+transpose(JR1)*R01*IC11*transpose(R01)*JR1+ m2*transpose(JT2)*JT2+transpose(JR2)*R02*IC22*transpose(R02)*JR2+m3*transpose(JT3)*JT3+transpose(JR3)*R03*IC33*transpose(R03)*JR3+m4*transpose(JT4)*JT4+transpose(JR4)*R04*IC44*transpose(R04)*JR4+m5*transpose(JT5)*JT5+transpose(JR5)*R05*IC55*transpose(R05)*JR5+m6*transpose(JT6)*JT6+transpose(JR6)*R06*IC66*transpose(R06)*JR6;
Gs=m1*transpose(JT1)*g0+m2*transpose(JT2)*g0+m3*transpose(JT3)*g0+m4*transpose(JT4)*g0+m5*transpose(JT5)*g0+m6*transpose(JT6)*g0;   
% CACH 2 TINH M G GIONG ANH Hai
%Ms=m1*transpose(JT1)*JT1+m2*transpose(JT2)*JT2+m3*transpose(JT3)*JT3+m4*transpose(JT4)*JT4+m5*transpose(JT5)*JT5+m6*transpose(JT6)*JT6+IC1+transpose(JR2)*IC2*JR2+transpose(JR3)*IC3*JR3+transpose(JR5)*IC5*JR5+transpose(JR6)*IC6*JR6;
Mt=mt*[(2*a*cos(q0)-4*b*sin(q0))^2 0;
        0                          0];
Gt=mt*g*[2*a*cos(q0)-4*b*sin(q0);
         0];
M=4*Ms+Mt;
M=simplify(M);
%G=-4*Gs+Gt;
%simplify(G);
%========================tinh toan ma tran C=============================%
Cijk = sym(zeros(2, 2, 2)); % tinh cac phan tu cijk
for i = 1:2
    for j = 1:2
        for k = 1:2
            Cijk(i, j, k) = 0.5 * (diff(M(i, j), q(k)) + diff(M(i, k), q(j)) - diff(M(j, k), q(i)));
        end
    end
end
C = sym(zeros(2, 2));
for i = 1:2
    for j = 1:2
        for k = 1:2
            C(i, j) = C(i, j) + Cijk(i, j, k) * dq(k);
        end
    end
end
C1=simplify(C);


% for i = 1:2
%     for j = 1 : 2
%         for k =1:2
%             c{i}(j,k)=1/2*(jacobian(M(i,j),q(k))+jacobian(M(i,k),q(j))-jacobian(M(j,k),q(i)));
%         end
%     end
% end
% C = sym(zeros(2, 2));
% for i = 1:2
%     for j = 1 : 2
%         C(i,j)=0;
%         for k =1:2
%             C(i,j)=C(i,j)+c{i}(j,k)*q_dot(k);
%         end
%     end
% end






    