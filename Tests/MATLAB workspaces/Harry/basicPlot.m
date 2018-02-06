function [ output_args ] = basicPlot( test1,test2,test3,test4 )

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

figure();

end

