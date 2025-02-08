function Rdot=matrixRdot(q,qdot)
%q=[pi/3; 1.7722];
global m1 m2 m3 m4 m5 m6 mt J1 J2 J3 JB g a b d I1x I1y I1z I2x I2y I2z I2yz I3x I3y I3z
q0=q(1); q1=q(2);
dq0=qdot(1); dq1=qdot(2);
% Rdot = [
%   0;
%  (2*2^(1/2)*tan(q0)*(tan(q0)^2 + 1))/(tan(q1/2)^2 + 1) - (2*2^(1/2)*tan(q1/2)*(tan(q1/2)^2/2 + 1/2)*(tan(q0)^2 + 1))/(tan(q1/2)^2 + 1)^2];
Rdot=[
  0;
 (2*2^(1/2)*dq0*tan(q0)*(tan(q0)^2 + 1))/(tan(q1/2)^2 + 1) - (2*2^(1/2)*dq1*tan(q1/2)*(tan(q1/2)^2/2 + 1/2)*(tan(q0)^2 + 1))/(tan(q1/2)^2 + 1)^2];
 
end