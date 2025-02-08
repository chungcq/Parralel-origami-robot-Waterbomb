function u=controller_PDg_3dof(ins)
global Kp Kd
qd=ins(1:3);
q=ins(4:6);
qdot=ins(7:9);
e=qd-q;
edot=-qdot;
G=matrixG(q);
u=Kp*e+Kd*edot+G;

