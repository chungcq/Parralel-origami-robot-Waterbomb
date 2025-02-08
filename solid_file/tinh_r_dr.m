syms q0 q1
syms dq0 dq1
syms ddq0 ddq1
q=[q0;q1]; dq=[dq0;dq1]; ddq=[ddq0;ddq1];
a=[tan(q0)^2+1     -(1/sqrt(2))*(tan(q1/2)^2+1)];
da=diff(a,q0)+diff(a,q1);
f=a*ddq+da*dq==0;
s=simplify(solve(f, ddq1));
s=(2^(1/2)*(ddq0*(tan(q0)^2 + 1) + 2*dq0*tan(q0)*(tan(q0)^2 + 1) - 2^(1/2)*dq1*tan(q1/2)*(tan(q1/2)^2/2 + 1/2)))/(tan(q1/2)^2 + 1);
R=[1;
   (1/(((tan(q1/2)^2)+1)*(1/sqrt(2))))*(tan(q0)^2+1)];
dr=diff(R,q0)+diff(R,q1);
dr1=diff(R,q0)*dq0+diff(R,q1)*dq1;