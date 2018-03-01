function [outputs] = dataman(data)
middle = 54;
coff = 3;
for n = 1:size(data,1)
    if data{n,3} > middle
       data{n,4} = coff;
    else
        data{n,4} = -coff;
    end
end

% plot(data{:,4})
% hold on;
% plot(data{:,1})% for above middle
% plot(data{:,2}) % for below middle
% plot(data{:,3})

hold off;
for n = 1:size(data,1)
    if data{n,3} > middle
        data{n,5} = data{n,1};
    else
        data{n,5} = data{n,2};
    end
    
end


hold on;
plot(data{(1:1046),3})
plot(data{(1:1046),5})
hold off;
figure();
hold on;
plot(data{(1046:2226),3})
plot(data{(1046:2226),5})
hold off;
shg;
end