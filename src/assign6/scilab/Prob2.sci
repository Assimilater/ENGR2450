function [z] = f(x, y)
  z = .026 * (1 - y / 12000.0) * y;
endfunction;

x0 = 1950.0; y0 = 2555.0; xn = 2000.0; h = 10.0;
x = [x0:h:xn];
y = ode("rk", y0, x0, x, f);

disp("x  y"); // show titles for output table
disp("--------"); // show a line for the table
disp([x' y']);

// fe(x) = exact solution
function z = fe(x)
  z = 12000 / (1 - (1 - (12000 / 2555.0)) * exp(-.026 * (x - 1950.0)));
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
xtitle('Solving dp/dt = k(1-p/pmax)p', 't', 'p');
