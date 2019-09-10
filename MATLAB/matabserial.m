%if Com port open use fclose(instrfind()) in command window

s = serial('COM7','BaudRate',9600,'Terminator','CR') %initiate connection
i=1
b=zeros(1,6); %initiate matrix

fopen(s) %open serial port
while 1
out=fgetl(s)%read line X-RAW, Y-RAW, Z-RAW, x_accel, y_accel, z_accel
pause(2);
a=str2num(out);
b=[b;a];%cat serial output to matrix
i=i+1;
end
fclose(s)

