//Script to solve dY/dx = F(x, Y), Y(x0) = Y0
function [Z] = F(x, Y)
  Z(1)= -10 * Y(1) + 10 * Y(2);
  Z(2)= 28 * Y(1) - Y(2) - Y(1) * Y(3);
  Z(3)= -2.666667 * Y(3) + Y(1) * Y(2);
endfunction;

//ODE solution
x = [0.0:0.01:20.0];
x0 = 0;
Y0 = [5;5;5];
Y = ode("rk", Y0, x0, x, F); //solve ODE

disp("t     x     y     z")
disp([x' Y']);
y1 = Y(1,:); y2 = Y(2,:); y3 = Y(3,:); //extract y1, y2, y3


scf();
plot(x, y1, 'b-', x, y2, 'r-', x, y3, 'g-');
legend('x', 'y', 'z', 1);
xtitle('signal plots', 't', 'y');

scf();
plot(y1, y2);
xtitle('phase portrait', 'x', 'y');

scf();
plot(y2, y3);
xtitle('phase portrait', 'y', 'z');

scf();
plot(y3, y1);
xtitle('phase portrait', 'z', 'x');
