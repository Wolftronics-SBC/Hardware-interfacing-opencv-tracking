function filterDuration( data1, data2, data3, data4 )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here


figure;
hold on
plot(data1)
plot(data2)
plot(data3)
plot(data4)

dataSize = max([length(data1), length(data2), length(data3), length(data4)]);
data1 = padarray(data1,dataSize,'circular');

end

