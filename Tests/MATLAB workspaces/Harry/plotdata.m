function plotdata (sens1,sens2,ypos)

sens1 = smooth(sens1,'moving');
sens2 = smooth(sens2,'moving');
ypos = smooth(ypos,'moving');

figure;
plot3(sens1,sens2,ypos); xlabel('Sensor 1'); ylabel('Sensor 2'); zlabel('Y Pos'); grid on;

figure;
scatter3(sens1,sens2,ypos); xlabel('Sensor 1'); ylabel('Sensor 2'); zlabel('Y Pos'); grid on; 
figure;
surface(sens1,sens2,ypos); xlabel('Sensor 1'); ylabel('Sensor 2'); zlabel('Y Pos');
shg;







end

