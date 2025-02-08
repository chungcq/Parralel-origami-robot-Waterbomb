function q2dot=tinhqddot(ins)
%ins=[1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1]';
q0dot=ins(1);
q0=ins(2);
u=ins(3);
%q0ddot=ins(4);
q1=2*atan((1/sqrt(2))*tan(q0));
q1dot=(2*q0dot*(tan(q0^2+1)))/(sqrt(2)*tan(q0^2+1));
%q1ddot=((2*tan(q0)^2+1)*(q0ddot+2*q0dot^2*tan(q0))-0.5*q1dot^2*tan(q0)*(tan(q0)^2+2))/(sqrt(2)*(tan(q0)^2+2));
q=[q0; q1];
qdot=[q0dot; q1dot];
M=matrixM(q);
C=matrixC(q,qdot);
G=matrixG(q);
B=matrixB;
R=matrixR(q);
DR=matrixRdot(q,qdot);
P=((tan(q0)^2+1)*sqrt(2))/((tan(q1/2)^2+1));
%q2dot=inv(M(1,1)+ P*M(2,1))*(u-(M(1,2)+P*M(2,2))*q1ddot-((C(1,1)+C(1,2))+P*(C(2,1)+C(2,2)))-(G(1,1)+P*G(2,1)));
q2dot=inv(R.'*M*R)*(R.'*B*u-R.'*M*DR*q0dot-R.'*C*R*q0dot-R.'*G);





