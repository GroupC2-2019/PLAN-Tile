%if Com port open use fclose(instrfind()) in command window

s = serial('COM3','BaudRate',9600,'Terminator','CR') %initiate connection
i=1
b=zeros(1,3); %initiate matrix

fopen(s) %open serial port
%while 1
for c=1:100
out=fgetl(s)%read line X-RAW, Y-RAW, Z-RAW
a=str2num(out); %separates values by comma delimiter
b=[b;a];%cat serial output to matrix
i=i+1;
end
fclose(s)

x=b(:,1); %Assign first column of matrix to x
y=b(:,2);
z=b(:,3);
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