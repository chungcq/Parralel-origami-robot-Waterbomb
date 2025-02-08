function q_dot=tinh_q_dot(input)
% x=[5,6,0];
% q=newton_raphson(x);
   
jx=jacobi(input(1));

x_dot=input(3);

q_dot=jx^-1*x_dot;
 
  