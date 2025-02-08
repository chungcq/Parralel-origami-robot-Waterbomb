function q2dot=tinhq2dot(ins)
qdot=ins(1:2);
q=ins(3:4);
u=ins(5:6);
M=matrixM(q);
C=matrixC(q,qdot);
G=matrixG(q);
B=matrixB1;

q2dot=inv(M)*(B*u-C*qdot-G);
