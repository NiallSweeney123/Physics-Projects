function theta= polygonAngle(n)
if n<3
    n=2;
    disp('input value must be greater than or equal to 3') 
end
if n(n<3)
    n=2;
    disp('input value must be greater than or equal to 3')
end
interiorAngleTotal=(n-2).*180;
theta=interiorAngleTotal./n


