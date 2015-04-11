function [T]=TrapEq(n, a, b, f)
    //trapezoidal rule
    h = (b - a) / n;
    x = a;
    suma = f(x);
    for i = 1:n-1
        x = x+h;
        suma = suma + 2*f(x);
    end;
    suma = suma + f(b);
    T = (b - a) * suma / (2*n);
endfunction;
