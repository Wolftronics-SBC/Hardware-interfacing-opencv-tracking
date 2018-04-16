function poly(c1)

f1 = c1(:,1);
f2 = c1(:,2);
output = c1(:,3);

f1 = smooth(f1,'moving');
f2 = smooth(f2,'moving');
output = smooth(output,'moving');

p00 =      -965.9;
p10 =       17.37;
p01 =       13.28;
p20 =    -0.06912;
p11 =     -0.1346;
p02 =    -0.02547;

outputtest = p00 + p10.*f1 + p01.*f2 + p20.*f1.^2 + p11.*f1.*f2 + p02.*f2.^2;

figure;
plot(output);
hold on;
plot(outputtest);
title('Results of polf2fit 2 degrees');
legend('output','polf2 output');


p00 =       -3258;
p10 =       74.86;
p01 =       25.21;
p20 =     -0.4008;
p11 =     -0.3519;
p02 =   -0.001321;

outputtest2 = p00 + p10.*f1 + p01.*f2 + p20.*f1.^2 + p11.*f1.*f2 + p02.*f2.^2


figure;
plot(output);
hold on;
plot(outputtest);
title('Results of polf2fit 2 degrees');
legend('output','polf2 output');



end

