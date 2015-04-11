function [II, n, iter, ea] = Romberg(a, b, maxit, es, f)
    //Romberg Integration
    I = zeros(10, 10); //create matrix I with zeros
    n = 1;
    I(1,1) = TrapEq(n, a, b, f);
    iter = 0;
    while(1) do
        iter = iter + 1;
        n = 2^iter;
        I(iter + 1, 1) = TrapEq(n, a, b, f);
        for k = 2:iter+1
            j = 2 + iter - k;
            I(j, k) = (4^(k-1) * I(j+1,k-1) - I(j, k-1)) / (4^(k-1)-1);
        end;
        ea = abs((I(1, iter+1) - I(2,iter))/(I(1,iter+1)))*100;
        if((iter >= maxit) | (ea <= es)) then
            break;
        end;
    end;
    II = I(1, iter + 1);
endfunction;
