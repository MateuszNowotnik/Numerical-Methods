syms x

a = 0;
b = 4;

f = @(x)sin(2.5.*x)+2.*x.*cos((0.1.*x)+1);
F = @(x)20.*x.*sin((x+10)/10)+200.*cos((x+10)/10)-((2.*cos((5.*x)/2))/(5));

subplot(2,1,1)
fplot(f, [a b])
xlabel('x')
ylabel('y')
title('Plot of the function f(x)')

subplot(2,1,2)
fplot(F, [a b])
xlabel('x')
ylabel('y')
title('Plot of the primitive function F(x)')

PreciseIntegral = feval(F, b) - feval(F, a)