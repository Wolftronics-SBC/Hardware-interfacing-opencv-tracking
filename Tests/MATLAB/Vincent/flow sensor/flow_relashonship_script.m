
figure;

minsize = min([length(lpm18psi30),length(lpm20psi30),length(lpm22psi30),length(lpm25psi30),length(lpm27psi40),length(lpm30psi40),length(lpm34psi50)]);

flow = [18,20,22,25,27,30,34];
peaks(1) = relashonAnalyser( lpm18psi30 , minsize , 'b' , true );
peaks(2) = relashonAnalyser( lpm20psi30 , minsize , 'r' , true );
peaks(3) = relashonAnalyser( lpm22psi30 , minsize , 'g' , true );
peaks(4) = relashonAnalyser( lpm25psi30 , minsize , 'm' , true );
peaks(5) = relashonAnalyser( lpm27psi40 , minsize , 'c' , true );
peaks(6) = relashonAnalyser( lpm30psi40 , minsize , 'y' , true );
peaks(7) = relashonAnalyser( lpm34psi50 , minsize , 'k' , true );
xlabel('Sample Time (seconds)');
ylabel('duration (seconds)');
h = findobj(gca,'Type','line');
legend([h(13),h(11),h(9),h(7),h(5),h(3),h(1)] , {'lpm18psi30','lpm20psi30','lpm22psi30','lpm25psi30','lpm27psi40','lpm30psi40','lpm34psi50'});
limitsy = ylim;
limitsx = xlim;

