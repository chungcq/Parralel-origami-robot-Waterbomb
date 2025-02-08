function u= controller_tracking_3dof(ins)
% ins=[1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1]';
global Kp Kd 
qd=ins(1:2); vd=ins(3:4); ad=ins(5:6);
q=ins(7:8); qdot=ins(9:10);
M=matrixM(q); C=matrixC(q,qdot);
G=matrixG(q);
et=qd-q; edot=vd-qdot;
y=ad+Kd*edot+Kp*et; b=C*qdot+G;
u=M*y+b;