function peak = relashonAnalyser( data , minSize , color , useMedi)

shiftdata = data - data(1);

h = [1/2 1/2];
binomialCoeff = conv(h,h);
for n = 1:4
    binomialCoeff = conv(binomialCoeff,h);
end

binomialMA = filter(binomialCoeff, 1, shiftdata);
binomialMA = binomialMA + data(1);

for i = 1:1:length(data)
    datatime(i) = sum(data(1:i)*10^-6);
end

for i = 1:1:length(binomialMA)
    binomialtime(i) = sum(binomialMA(1:i)*10^-6);
end

for i = 1:1:length(binomialMA)
    DPS(i) = 90/(binomialMA(i)*10^-6);
end

DPSmedi = medfilt1(DPS,100);

DPSdifferential = diff(DPS(:))./diff(binomialtime(:));

hold on
grid on
%plot (datatime, data,'--','color',color)
%plot (binomialtime,binomialMA,'color',color)
plot (binomialtime,DPS,'--','color',color)
%plot (binomialtime,DPSmedi,'color',color)

 if useMedi
     DPSdifferential = medfilt1(DPSdifferential,100);
     plot (binomialtime(2:end),DPSdifferential,'color',color)
 else
     plot (binomialtime(2:end),DPSdifferential,'color',color)
 end
 peak = max(DPSdifferential);

end

