syms x y

z = (-((x-1)^3)*(5*cos(y)*sin(y)^2+6*cos(y)^3)/(12*sin(y)^4));

fsurf(z, [0.5 1.5 0.5 2])

xlabel('x')
ylabel('y')
zlabel('z')
title('Task 1')