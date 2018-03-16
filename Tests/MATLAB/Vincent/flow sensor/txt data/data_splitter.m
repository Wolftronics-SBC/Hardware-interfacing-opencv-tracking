ost0G50psivis_dur = [0,0,0,0,0,0,0];
ost0G50psivis_pos = [0,0,0,0,0,0,0];
for i = 1:1:size(ost0G50psivis,1)
    if(ost0G50psivis(i,3) == 0)
        ost0G50psivis_dur = [ost0G50psivis_dur ; ost0G50psivis(i,:)];
    else
        ost0G50psivis_pos = [ost0G50psivis_pos ; ost0G50psivis(i,:)];
    end
end

ost0G50psivis_dur = ost0G50psivis_dur(2:end,1:2);
ost0G50psivis_pos = ost0G50psivis_pos(2:end,:);