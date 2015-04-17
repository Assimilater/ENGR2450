//Script to solve dY/dx=F(x,Y), Y(x0)=Y0
function [Z] = F(x, Y)
  Z(1) = Y(2);
  Z(2) = (2.5 * sin(.5 * x) - 5 * abs(Y(2)) * Y(2) - 6 * Y(1)) / 2;
endfunction;

x = [0.0:0.25:15];
x0 = 0;
Y0 = [1;0];
Y = ode("rk", Y0, x0, x, F); //solve ODE

disp("t   Displacement   Velocity")
disp([x' Y']);
y1 = Y(1,:); y2 = Y(2,:); //extract y1, y2C

scf();
plot(x, y1, 'b-', x, y2, 'r-');
legend('Disp.', 'Velo.', 1);
xtitle('signal plots', 't', 'y');

scf();
plot(y1, y2);
xtitle('phase portrait', 'x', 'dx/dt');
