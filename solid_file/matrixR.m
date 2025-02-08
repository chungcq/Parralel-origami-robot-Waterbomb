function R=matrixR(q)
%q=[pi/3; 1.7722];
global m1 m2 m3 m4 m5 m6 mt J1 J2 J3 JB g a b d I1x I1y I1z I2x I2y I2z I2yz I3x I3y I3z
q0=q(1); q1=q(2);
R=[1;
   (1/(((tan(q1/2)^2)+1)*(1/sqrt(2))))*(tan(q0)^2+1)];
end