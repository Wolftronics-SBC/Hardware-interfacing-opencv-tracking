hold on;
shiftdata1 = data1 - data1(1);
shiftdata2 = data2 - data2(1);
shiftdata3 = data3 - data3(1);
shiftdata4 = data4 - data4(1);
shiftdata5 = data5 - data5(1);
shiftdata6 = data6 - data6(1);
shiftdata7 = data7 - data7(1);
 plot(data1)
 plot(data2)
plot(data3)
 plot(data4)
 plot(data5)
plot(data6)
plot(data7)
legend('18-lpm 30-psi','20-lpm 30-psi','22-lpm 30-psi','25-lpm 30-psi',...
    '27-lpm 40-psi','30-lpm 40-psi','34-lpm 50-psi');

datamaxsize = max([length(shiftdata1),length(data2),length(data3),...
    length(data4),length(data5),length(data6),length(data7)]);

h = [1/2 1/2];
binomialCoeff = conv(h,h);
for n = 1:4
    binomialCoeff = conv(binomialCoeff,h);
end

fDelay = (length(binomialCoeff)-1)/2;


binomialMA1 = filter(binomialCoeff, 1, shiftdata1);
binomialMA2 = filter(binomialCoeff, 1, shiftdata2);
binomialMA3 = filter(binomialCoeff, 1, shiftdata3);
binomialMA4 = filter(binomialCoeff, 1, shiftdata4);
binomialMA5	 = filter(binomialCoeff, 1, shiftdata5);
binomialMA6 = filter(binomialCoeff, 1, shiftdata6);
binomialMA7	 = filter(binomialCoeff, 1, shiftdata7);

binomialMA1 = binomialMA1 + data1(1)
binomialMA2 = binomialMA2 + data2(1)
binomialMA3 = binomialMA3 + data3(1)
binomialMA4 = binomialMA4 + data4(1)
binomialMA5 = binomialMA5 + data5(1)
binomialMA6 = binomialMA6 + data6(1)
binomialMA7 = binomialMA7 + data7(1)


plot(binomialMA1)
plot(binomialMA2)
plot(binomialMA3)
plot(binomialMA4)
plot(binomialMA5)
plot(binomialMA6)
plot(binomialMA7)
hold off;
shg
