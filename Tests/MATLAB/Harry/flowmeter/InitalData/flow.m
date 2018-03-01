function [ output_args ] = flow( data, data1, data2, data3)

close all
close all hidden 

datamaxsize = max([length(data),length(data1),length(data2),length(data3)]);
plot(data)
hold on;
plot(data1)
plot(data2)
plot(data3)

y = transpose(1:1:length(data));
p = polyfit(y,data,2);

y1 = transpose(1:1:length(data1));
p1 = polyfit(y1,data1,2);

y2 = transpose(1:1:length(data2));
p2 = polyfit(y2,data2,2);

y3 = transpose(1:1:length(data3));
p3 = polyfit(y3,data3,2);

ymax = transpose(1:1:datamaxsize);

fitted = polyval(p,ymax);
fitted1 = polyval(p1,ymax);
fitted2 = polyval(p2,ymax);
fitted3 = polyval(p3,ymax);


% plot(fitted)
% plot(fitted1)
% plot(fitted2)
% plot(fitted3)

plot((fitted+fitted1+fitted2+fitted3)/4)



hold off;
shg


end

