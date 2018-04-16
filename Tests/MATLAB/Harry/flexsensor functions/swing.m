close all ;
close all hidden ;
hold on;
range = 2263:length(c1);
range = 1:1050;
sens1 = smooth(c1(range,1),'moving');
sens2 = smooth(c1(range,2),'moving');
ypos = c1(range,3);

a = 0.2;
b = 0.3;
C = [sens1 sens2]*[a;b]
[sens1 sens2]/C;








hold off;