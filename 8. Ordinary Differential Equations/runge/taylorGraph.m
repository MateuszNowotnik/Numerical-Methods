y = @(x) -10+(27.*x)-(34.*(x.^2))+((82./3).*(x.^3));

%plot
fplot(y, [0 5])
grid on
xlabel('x'), ylabel('y')
title('Graph of the solution using Taylor series method')