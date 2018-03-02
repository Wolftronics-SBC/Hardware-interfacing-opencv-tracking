close all
close all hidden
subplot(2,2,1)
hold on;
plot(c1(:,1))
plot(c1(:,2))
plot(c1(:,3)); title('Cycle 1'); legend('Sensor 1','Sensor 2','Y pos');
hold off;
subplot(2,2,2);
hold on;
plot(c2(:,1))
plot(c2(:,2))
plot(c2(:,3)); title('Cycle 2'); legend('Sensor 1','Sensor 2','Y pos');
hold off;
subplot(2,2,3);
hold on;
plot(c3(:,1))
plot(c3(:,2))
plot(c3(:,3)); title('Cycle 3'); legend('Sensor 1','Sensor 2','Y pos');
hold off;
subplot(2,2,4);
hold on;
plot(c4(:,1))
plot(c4(:,2))
plot(c4(:,3)); title('Cycle 4'); legend('Sensor 1','Sensor 2','Y pos');
hold off;