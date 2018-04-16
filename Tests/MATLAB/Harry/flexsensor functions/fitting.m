p00 = 59.85;
p10 = -21.01;
p01 = -1.164;
p20 = -4.185;
p11 = 11.4;
p02 = -4.87;
p30 = 12.06;
p21 = -2.269;
p12 = 6.356;
p03 = 2.86;
p40 = 4.591;
p31 = -7.367;
p22 = -0.07003;
p13 = -2.827;
p04 = 1.264;

fittedoutput = p00 + p10.*f1 + p01.*f2 + p20.*f1.^2 + p11.*f1.*f2 + p02.*f2.^2 + p30.*f1.^3 + p21.*f1.^2.*f2 ...
    + p12.*f1.*f2.^2 + p03.*f2.^3 + p40.*f1.^4 + p31.*f1.^3.*f2 + p22.*f1.^2.*f2.^2 ...
    + p13.*f1.*f2.^3 + p04.*f2.^4;

plot(output);
hold on;
plot(fittedoutput)
grid on;
legend('Real Output','Fitting Output');
ylabel('Y Pos');
xlabel('Sample Count');
title('Polynomial 22 Up Stroke fitting');