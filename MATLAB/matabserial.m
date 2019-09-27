%if Com port open use fclose(instrfind()) in command window

s = serial('COM3','BaudRate',9600,'Terminator','CR') %initiate connection
b=zeros(1,3); %initiate matrix

fopen(s) %open serial port
%while 1
for c=1:1000
out=fgetl(s)%read line X-RAW, Y-RAW, Z-RAW
a=str2num(out); %separates values by comma delimiter
b=[b;a];%cat serial output to matrix
end
fclose(s)

x=b(:,1); %Assign first column of matrix to x
xavg=(mean(reshape(x,10,[]),1)).' 
% reshape vector to matrix, average every 10 values then transpose back to original form

y=b(:,2);
yavg=(mean(reshape(y,10,[]),1)).' 

z=b(:,3);
zavg=(mean(reshape(z,10,[]),1)).' 

figure('Name', 'XYZ Raw');
subplot(3,1,1);
plot(x);
title('X-axis Raw');
subplot(3,1,2);
plot(y);
title('Y-axis Raw');
subplot(3,1,3);
plot(z);
title('Z-axis Raw');

figure('Name', 'XYZ Avg');
subplot(3,1,1);
plot(xavg);
title('X-axis AVG');
subplot(3,1,2);
plot(yavg);
title('Y-axis AVG');
subplot(3,1,3);
plot(zavg);
title('Z-axis AVG');