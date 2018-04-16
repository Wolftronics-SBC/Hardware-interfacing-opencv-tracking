function work = motionPlotter( data , mass )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
% Width of 640 and Height of 480
% y0,x0,y1,x1,y2,x2,time



convs = 219.6474/23.5;

figure;
hold on
grid on
plot(data(:,2)/convs,((data(:,1)-480)*-1)/convs,'Marker','o','Color','r')
text(data(1,2)/convs,((data(1,1)-480)*-1)/convs,'\leftarrow start')
text(data(end,2)/convs,((data(end,1)-480)*-1)/convs,'\leftarrow end')

plot(data(:,4)/convs,((data(:,3)-480)*-1)/convs,'Marker','o','Color','b')
text(data(1,4)/convs,((data(1,3)-480)*-1)/convs,'\leftarrow start')
text(data(end,4)/convs,((data(end,3)-480)*-1)/convs,'\leftarrow end')

plot(data(:,6)/convs,((data(:,5)-480)*-1)/convs,'Marker','o','Color','g')
text(data(1,6)/convs,((data(1,5)-480)*-1)/convs,'\leftarrow start')
text(data(end,6)/convs,((data(end,5)-480)*-1)/convs,'\leftarrow end')

hold off

xlabel('x Position (cm)');
ylabel('y Position (cm)');

ylim([0,600/convs])
xlim([0,600/convs])

%find work done
dist = (((data(end,1)-480)*-1)/convs)-(((data(1,1)-480)*-1)/convs);
work = 9.81*mass*10^-3*dist*10^-2;
disp('work done to move vertically is:')
disp([num2str(work),' Joules'])

legend({'Hip' 'Knee' 'Ankle'})

title({'Movment of Joints of Leg from Camera View';['Total Vertical Energy Expended to Move Weight of ' num2str(mass) ' g is ' num2str(work) ' Joules']});

end

