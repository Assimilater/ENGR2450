diary("Problems22_22_And_22_3.txt")

//Problem 22.2
a = 1; b = 2; maxiter = 50; ea = .5;

function [y] = f2(x)
    y = (2*x + (3 / x))^2;
endfunction;

[II, n1, iter1, ea1] = Romberg(a,b,maxiter,ea,f2)

//Problem 22.3
a = 0; b = 2; maxiter = 50; ea = .5;

function [z] = f3(t)
    z = (%e^(t) * sin(t)) / (1 + t^2); 
endfunction;

[I2,n2,iter2,ea2] = Romberg(a,b,maxiter,ea,f3)

diary(0)
