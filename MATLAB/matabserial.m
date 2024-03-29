%if Com port open use fclose(instrfind()) in command window

s = serial('COM9','BaudRate',230400,'Terminator','CR') %initiate connection
b=zeros(1,3); %initiate matrix

fopen(s) %open serial port
%while 1

disp("GO")

tic

for c=1:500
    out=fgetl(s);%read line X-RAW, Y-RAW, Z-RAW
    a=str2num(out); %separates values by comma delimiter
    b=[b;a];%cat serial output to matrix
end
fclose(s)

toc

% lx=b(:,1); %Assign first column of matrix to x
% hx=b(:,2); %Assign first column of matrix to x
% 
% 
% ly=b(:,3);
% hy=b(:,4);
% 
% 
% lz=b(:,5); 
% hz=b(:,6);
% 
% OUT_X = (hx .* 2^4 + lx./16);
% OUT_Y = (hy .* 2^4 + ly./16);
% OUT_Z = (hz .* 2^4 + lz./16);

OUT_X=b(:,1);
OUT_Y=b(:,2);
OUT_Z=b(:,3);

MAG =(OUT_X.^2 + OUT_Y.^2 + OUT_Z.^2).^(1/2);

figure('Name', 'XYZ Raw');
subplot(4,1,1);
plot(OUT_X);
ylim([-2048 2048]);
title('X-axis Raw');
subplot(4,1,2);
plot(OUT_Y);
ylim([-2048 2048]);
title('Y-axis Raw');
subplot(4,1,3);
plot(OUT_Z);
ylim([-2048 2048]);
title('Z-axis Raw');
subplot(4,1,4);
plot(MAG);
ylim([-2048 2048]);
title('MAG');




