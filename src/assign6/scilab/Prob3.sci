function [z] = f(x, y)
  z = -0.06 * sqrt(y);
endfunction;

x0 = 0.0; y0 = 3.0; xn = 57; h = 0.5;
x = [x0:h:xn];
y = ode("rk", y0, x0, x, f);

disp("x  y"); // show titles for output table
disp("--------"); // show a line for the table
disp([x' y']);

// fe(x) = exact solution
function z = fe(x)
  z = (0.06)^2 / 4 * (2 / 0.06 * sqrt(3.0) - x)^2;
endfunction;

xe = [x0:h / 10:xn];
n = length(xe);
for i = 1:n
  ye(i) = fe(xe(i));
end;

// NEXT: plot numerical solution as red circles and
// exact solution as a continuous blue line
plot(x, y, 'ro', xe, ye, '-b');
legend('RK4', 'Exact', 3);
xtitle('Solving dy/dt = -k*sqrt(y)', 't', 'y');
