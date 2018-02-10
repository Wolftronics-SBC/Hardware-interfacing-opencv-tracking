function [ output_args ] = basicPlot( test1,test2,test3,test4 )


%% ---General View---
figure(); 
test1{:,1} = smooth(test1{:,1},'moving');
test1{:,2} = smooth(test1{:,2},'moving');
test1{:,3} = smooth(test1{:,3},'moving');

subplot(2,2,1);
plot(test1{:,1});hold on;
plot(test1{:,2});
plot(test1{:,3});
legend('Sensor 1','Sensor 2','Y Pos');
title('Cycle Test 1');
hold off;

subplot(2,2,2);
test2{:,1} = smooth(test2{:,1},'moving');
test2{:,2} = smooth(test2{:,2},'moving');
test2{:,3} = smooth(test2{:,3},'moving');

plot(test2{:,1});hold on;
plot(test2{:,2});
plot(test2{:,3});
legend('Sensor 1','Sensor 2','Y Pos');
title('Cycle Test 2');

subplot(2,2,3);
test3{:,1} = smooth(test3{:,1},'moving');
test3{:,2} = smooth(test3{:,2},'moving');
test3{:,3} = smooth(test3{:,3},'moving');

plot(test3{:,1});hold on;
plot(test3{:,2});
plot(test3{:,3});
legend('Sensor 1','Sensor 2','Y Pos');
title('Cycle Test 3');

subplot(2,2,4);
test4{:,1} = smooth(test4{:,1},'moving');
test4{:,2} = smooth(test4{:,2},'moving');
test4{:,3} = smooth(test4{:,3},'moving');

plot(test4{:,1});hold on;
plot(test4{:,2});
plot(test4{:,3});
legend('Sensor 1','Sensor 2','Y Pos');
title('Cycle Test 4');
hold off;
%% ---General View 3D---
figure();
subplot(2,2,1);
plot3(test1{:,1},test1{:,2},test1{:,3}); 
xlabel('Sensor 1');ylabel('Sensor 2');zlabel('Y Pos');
title('Cycle Test 1');
subplot(2,2,2);
plot3(test2{:,1},test2{:,2},test2{:,3});
xlabel('Sensor 1');ylabel('Sensor 2');zlabel('Y Pos');
title('Cycle Test 2');
subplot(2,2,3);
plot3(test3{:,1},test3{:,2},test3{:,3});
xlabel('Sensor 1');ylabel('Sensor 2');zlabel('Y Pos');
title('Cycle Test 3');
subplot(2,2,4);
plot3(test4{:,1},test4{:,2},test4{:,3});
xlabel('Sensor 1');ylabel('Sensor 2');zlabel('Y Pos');
title('Cycle Test 4');

c1s1='1-1048'
c1s2='1048-2236'
c1s3='2236-3943'

c2s1='1-1092'
c2s2='1092-2021'
c2s3='2021-3761'

c3s1='1-1100'
c3s2='1100-2136'
c3s3='2136-3850'

c4s1='1-1050'
c4s2='1050-2000'
c4s3='2000-3707'


%% ANAYLSING DOWN STROKE STAGE 1

createFit(test1{[1:1048],1},test1{[1:1048],2},test1{[1:1048],3});
createFit(test1{[1:1100],1},test1{[1:1100],2},test1{[1:1100],3});
createFit(test1{[1:1100],1},test1{[1:1100],2},test1{[1:1100],3});

createFit(test1{[1:1050],1},test1{[1:1050],2},test1{[1:1050],3});


%createFit(test1{:,1},test1{:,2},test1{:,3});

end

