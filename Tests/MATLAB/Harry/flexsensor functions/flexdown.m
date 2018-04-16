fd_ypos = c1([1:1050],3);
fd_f1 = c1([1:1050],1);
fd_f2 = c1([1:1050],2);

a = 0.02;
b = 0.1;
c = 0;
estimated =  (a*fd_f1+b*fd_f2) + c;
error = fd_ypos - estimated;

R = corrcoef(fd_ypos,fd_f1)
plot(R)                
close all
close all hidden
plot(fd_ypos)
hold on;
plot(fd_f1)
plot(fd_f2)
plot(estimated)
legend('Y pos','Sens 1', 'Sens 2', 'estimated', 'error'); 
hold off;
figure
hold on;
plot(error)
hold off;
shg

