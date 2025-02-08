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
T01=simplify(rotz(q0-pi/2)*rotx(pi/4)*tran(2*b,0,-(a+d)*2^(0.5)));
T12=tranrot((pi-q1), d*sqrt(2), 2*b, -pi/4);
T23=tranrot((pi+2*q0), 0, -2*b, -pi/4);
T34=tranrot((pi-q1), -d*sqrt(2), 0, -pi/2);
T45=T12; T56=T23; T61=T34;
T13=simplify(T12*T23);
T14=simplify(T12*T23*T34);
T15=simplify(inv(T61)*inv(T56));
h=2*a*sin(q0);
rc10=T01*uc11;
rc20=simplify(T01*T12*uc22);
rc30=simplify(T01*T13*uc33);
rc40=simplify(T01*T14*uc44);
%rc40=[rc10(1);h-rc10(2);rc10(3);1];
rc50=simplify(T01*T15*uc55);
rc60=simplify(T01*inv(T61)*uc66);
JT1= simplify(jacobian(rc10(1:3), q));  % MA TRAN JACOBI TINH TIEN
JT2= simplify(jacobian(rc20(1:3), q));
JT3= simplify(jacobian(rc30(1:3), q));
JT4= simplify(jacobian(rc40(1:3), q));
JT5= simplify(jacobian(rc50(1:3), q));
JT6= simplify(jacobian(rc60(1:3), q));
R01=T01(1:3,1:3);
RR2=T01*T12; R02=RR2(1:3,1:3);
RR3=T01*T12*T23; R03=RR3(1:3,1:3);
RR4=T01*T14; R04=RR4(1:3,1:3);
RR5=T01*T15; R05=RR5(1:3,1:3);
RR6=T01*inv(T61); R06=RR6(1:3,1:3);
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
%Gs=m1*transpose(JT1)*g0+m2*transpose(JT2)*g0+m3*transpose(JT3)*g0+m4*transpose(JT4)*g0+m5*transpose(JT5)*g0+m6*transpose(JT6)*g0;   
Ms=simplify(Ms);
% CACH 2 TINH M G GIONG ANH Hai
%Ms=m1*transpose(JT1)*JT1+m2*transpose(JT2)*JT2+m3*transpose(JT3)*JT3+m4*transpose(JT4)*JT4+m5*transpose(JT5)*JT5+m6*transpose(JT6)*JT6+IC1+transpose(JR2)*IC2*JR2+transpose(JR3)*IC3*JR3+transpose(JR5)*IC5*JR5+transpose(JR6)*IC6*JR6;





