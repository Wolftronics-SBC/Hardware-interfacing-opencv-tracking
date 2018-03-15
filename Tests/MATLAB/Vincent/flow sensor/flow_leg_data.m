figure;

minsize = min([length(leg50psi0g),length(leg50psi300g),length(leg50psi600g)]);

relashonAnalyser( leg50psi0g , minsize , 'b' , false )
relashonAnalyser( leg50psi300g , minsize , 'r' , false )
relashonAnalyser( leg50psi600g , minsize , 'g' , false )
xlabel('Sample Time (seconds)');
ylabel('speed (degrees per second)');
h = findobj(gca,'Type','line');
legend([h(1),h(3),h(5)] , {'leg50psi0g','leg50psi300g','leg50psi600g'});