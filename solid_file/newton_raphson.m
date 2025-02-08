function q0 = newton_raphson(h)
    
 global a 
 q = 0;
 %x = [ 150.34;200.22;pi/4];
 %h=0.09;
    % Set tolerance and maximum iterations
    tolerance = 1e-6;
    max_iterations = 1000;
    num_iterations = 0;
    q0 = zeros(size(q));
    while num_iterations < max_iterations
    % Calculate the value of the functions F at the point q
   
      fx =2*a*sin(q)-h;
      Jx = jacobi(q); 
      delta_q = Jx^-1*(-fx);
      q = q + delta_q;
      if norm(delta_q) < tolerance
            q0 = q;
            break;
      end
      num_iterations = num_iterations + 1;
    end

    % If no solution is found after the maximum iterations
  q0 = q;
%  
%   x1=forward(q0)
%   x-x1
end
