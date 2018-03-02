function relashonAnalyser( data , maxSize )

coeffientsNum = 2;

shiftdata = data - data(1);

h = [1/2 1/2];
binomialCoeff = conv(h,h);
for n = 1:4
    binomialCoeff = conv(binomialCoeff,h);
end

fDelay = (length(binomialCoeff)-1)/2;

binomiaMA = filter(binomialCoeff, 1, shiftdata);

binomiaMA = binomiaMA + data(1);

y = transpose(1:1:length(binomiaMA));
p = polyfit(y,binomiaMA,coeffientsNum);
ymax = transpose(1:1:maxSize);
fitted = polyval(p,ymax);

hold on
plot (data)
plot (binomiaMA)
plot (fitted)

end

