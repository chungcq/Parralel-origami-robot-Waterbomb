clc
clear all
global d a b g
a=75*10^-3; b=2.5*10^-3; d=25*10^-3; g=9.81;
global m1 m2 m3 m4 m5 m6 mt
m1=90.75e-3;m2=17.58e-3;m3=17.58e-3;
m4=90.75e-3;m5=17.58e-3;m6=17.58e-3;mt=199.61e-3;
global I1x I1y I1z I2x I2y I2z I2yz I3x I3y I3z
I2x=11187e-9; I2y=8891.06e-9; I2z=2389.6e-9; 
I1x=162217.57e-9; I1y=81783.92e-9; I1z=81783.92e-9; I2yz=0; 
I3x=I2x; I3y=I2y; I3z=I2z;
global Kp Kd
Kp=diag([900,900]); Kd=diag([60,60]);
global kd kp
kp=1200; kd=110;
% kp=1600; kd=130;
global J1 J2 J3 JB
J1=11187.27e-9; J2=8794.80e-9; J3=2409.86e-9;
JB=42262.76e-9;
global rA rB T
rA=0.09; rB=0.03; T=10;




