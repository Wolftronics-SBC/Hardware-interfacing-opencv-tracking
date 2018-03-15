function flowFinder( lpm18psi30 , lpm20psi30 , lpm22psi30 , lpm25psi30 , lpm27psi40 , lpm30psi40 , lpm34psi50 , newData )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
figure;
minsize = min([length(lpm18psi30),length(lpm20psi30),length(lpm22psi30),length(lpm25psi30),length(lpm27psi40),length(lpm30psi40),length(lpm34psi50)]);
subplot(1,3,1)
flow = [18,20,22,25,27,30,34];
peaks(1) = relashonAnalyser( lpm18psi30 , minsize , 'b' , true );
peaks(2) = relashonAnalyser( lpm20psi30 , minsize , 'r' , true );
peaks(3) = relashonAnalyser( lpm22psi30 , minsize , 'g' , true );
peaks(4) = relashonAnalyser( lpm25psi30 , minsize , 'm' , true );
peaks(5) = relashonAnalyser( lpm27psi40 , minsize , 'c' , true );
peaks(6) = relashonAnalyser( lpm30psi40 , minsize , 'y' , true );
peaks(7) = relashonAnalyser( lpm34psi50 , minsize , 'k' , true );
xlabel('Sample Time (seconds)');
ylabel('speed (degrees per second)');
h = findobj(gca,'Type','line');
legend([h(13),h(11),h(9),h(7),h(5),h(3),h(1)] , {'lpm18psi30','lpm20psi30','lpm22psi30','lpm25psi30','lpm27psi40','lpm30psi40','lpm34psi50'});
title({'rotation speed (dashed) in DPS and';'acleleration (solid) in DPSPS at diffrent flow rates in LPM'});
limitsy = ylim;
limitsx = xlim;

subplot(1,3,2)
grid on
hold on
plot(peaks,flow,'*')
coefficients = polyfit(peaks, flow, 2);
plot(peaks,polyval(coefficients,peaks));
xlabel('max acceleration (degrees per second per second)');
ylabel('flow rate (LPM)');
title('flow rate vs maximum acceleration')
legend({'real world data points' 'polyfit line equation'})
subplot(1,3,3)
%minsize = min([length(leg50psi0g),length(leg50psi300g),length(leg50psi600g)]);
%relashonAnalyser( leg50psi0g , minsize , 'b' , false )
newDataPeak = relashonAnalyser( newData , length(newData) , 'b' , false );
ylim(limitsy)
%xlim(limitsx)
xlabel('Sample Time (seconds)');
ylabel('speed (degrees per second)');
title({'speed (dashed)in DPS and acceleration (solid) in DPSPS';'of data being tested';['flow of new data at max is ' num2str(polyval(coefficients,newDataPeak)) 'LPM']});
disp(['flow of new data at max is ' num2str(polyval(coefficients,newDataPeak)) 'LPM']);


end

