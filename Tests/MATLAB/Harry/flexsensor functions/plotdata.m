function plotdata (ypos,sens1,sens2)

sens1 = smooth(sens1,'moving');
sens2 = smooth(sens2,'moving');
ypos = smooth(ypos,'moving');

figure;
plot3(sens1,sens2,ypos); xlabel('Sensor 1'); ylabel('Sensor 2'); zlabel('Y Pos'); grid on;

figure;
scatter3(sens1,sens2,ypos); xlabel('Sensor 1'); ylabel('Sensor 2'); zlabel('Y Pos'); grid on; 
figure;


x1 = sens1(2108:4499);
x2 = sens2(2108:4499);
y = ypos(2108:4499);

hold off;
plot(y);
hold on;
plot(x1);
plot(x2);
legend('Y Pos','Sensor 1','Sensor 2');
title('Filtered and banded');

hold off;


end

