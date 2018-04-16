h = [1/2 1/2];
binomialCoeff = conv(h,h);
for n = 1:4
    binomialCoeff = conv(binomialCoeff,h);
end

fDelay = (length(binomialCoeff)-1)/2;
lengthofdata = 1028;
f1 = c1([lengthofdata:2092],1);
f2 = c1([lengthofdata:2092],2);
output = c1([lengthofdata:2092],3);

f1 = smooth(f1,'moving');
f2 = smooth(f2,'moving');

bf1 = filter(binomialCoeff, 1, f1);
bf2 = filter(binomialCoeff, 1, f2);
boutput = output;

bf1 = bf1(20:end);
bf2 = bf2(20:end);
boutput = boutput(20:end);


plot(bf1);
hold on;
plot(bf2);
plot(boutput);
