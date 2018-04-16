function datadispaly( l,n )
theta = 90; % to rotate 90 counterclockwise
R = [cosd(theta) -sind(theta); sind(theta) cosd(theta)];

F = [1 0;0 -1];
%l = transpose(R*F*transpose(l));
n = transpose(R*transpose(n));

l(:,1) = l(:,1) -1061;
l(:,2) = l(:,2) -382;



n(:,1) = n(:,1) +416;
n(:,2) = n(:,2) -776;


subplot(1,2,1);
plot(l(:,1),l(:,2)); title('Lycra covered silicone module response'); xlabel('X'); ylabel('Y');
subplot(1,2,2);
plot(n(:,1),n(:,2)); title('Silicone module response'); xlabel('X'); ylabel('Y');

end

