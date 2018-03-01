function filterRPM( rpm )

figure();
subplot(2,1,1);
t = [1:1:length(rpm)]';
plot(t,rpm,'DisplayName','Input Data');
hold on
grid on
rpm = medfilt1(rpm);

plot(t,rpm,'DisplayName','Input Data Median');

if(length(t)>108)
    for i = [37]
        windowSize = i; 
        b = (1/windowSize)*ones(1,windowSize);
        a = 1;
        y = filtfilt(b,a,rpm);
        plot(t,y,'DisplayName',['Filtered Data ',num2str(i)]);
    end
else
    for i = [2]
        windowSize = i; 
        b = (1/windowSize)*ones(1,windowSize);
        a = 1;
        y = filter(b,a,rpm);
        plot(t,y,'DisplayName',['Filtered Data ',num2str(i)]);
    end  
end
title('Flow Rate Over Time');
ylabel('Flow Rate');

legend('show')

subplot(2,1,2);
volume = cumtrapz(y);
plot(t,volume,'-o','DisplayName','volume')
title('Volume Over Time');
ylabel('Volume');
xlabel('Time');

grid on
end

