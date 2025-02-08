function u= controller(ins)
% ins=[1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1]';
global kp kd 
global Kp Kd
q0d=ins(1); v0d=ins(2); a0d=ins(3);
q0=ins(4); q0dot=ins(5);
q1x=2*atan((1/sqrt(2))*tan(q0d));
q1xdot=(2*v0d*(tan(q0d^2+1)))/(sqrt(2)*tan(q0d^2+1));
q1xddot=((2*tan(q0d)^2+1)*(a0d+2*v0d^2*tan(q0))-0.5*q1xdot^2*tan(q0d)*(tan(q0d)^2+2))/(sqrt(2)*(tan(q0d)^2+2));
q1=2*atan((1/sqrt(2))*tan(q0));
q1dot=(2*q0dot*(tan(q0^2+1)))/(sqrt(2)*tan(q0^2+1));
q=[q0; q1]; qdot=[q0dot; q1dot];
qd=[q0d; q1x]; vd=[v0d; q1xdot];
ad=[a0d; q1xddot];
M=matrixM(q); C=matrixC(q,qdot);
G=matrixG(q); R=matrixR(q);
B=matrixB;
%C1=[C(1,1)+C(1,2);C(2,1)+C(2,2)];
et=q0d-q0; edot=v0d-q0dot;
y=ad+kd*edot+kp*et; b=C*qdot+G;
u=inv(transpose(R)*B)*transpose(R)*(M*y+b);
