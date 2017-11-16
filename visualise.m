function visualise
%%GRAB DATA FOR LOG FILE
fid = fopen('log.txt');
formatspec = '%d %d';
sizea=[2 inf];
loggeddata = fscanf(fid, formatspec, sizea);
fclose(fid);


%%WORK ON DATA
time = 0:1:(size(loggeddata,2)-1);
plot(time,transpose(loggeddata));
legend('Position','Set Point');
title ('Data Log');
end

