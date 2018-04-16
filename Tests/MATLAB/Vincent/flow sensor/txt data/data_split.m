function [ dur , pos ] = data_split( data )

dur = [0,0,0,0,0,0,0];
pos = [0,0,0,0,0,0,0];
for i = 1:1:size(data,1)
    if(data(i,3) == 0)
        dur = [dur ; data(i,:)];
    else
        pos = [pos ; data(i,:)];
    end
end

dur = dur(2:end,1:2);
pos = pos(2:end,:);

end

