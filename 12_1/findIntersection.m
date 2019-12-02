function [x_cord,y_cord] = findIntersection(r1, r2, r3)
%Uses least squares principle to find best intersection of 3 radii


%Setting sensor locations: THIS PART TO BE CHANGED TO ACTUAL CONFIGURATION
x1 = 7;
y1 = 1;
x2 = 7;
y2 = 3;
x3 = 3;
y3 = 2;

% x = xy(1)          y = xy(2)
E = @(xy) ((xy(1) - x1)^2 + (xy(2) - y1)^2 - r1^2).^2 + ((xy(1) - x2)^2 + (xy(2) - y2).^2 - r2^2)^2 + ((xy(1) - x3)^2 + (xy(2) - y3)^2 - r3^2)^2;

[xy, fval] = fminsearch(E,[1,1]);

x_cord = xy(1);
y_cord = xy(2);
end

