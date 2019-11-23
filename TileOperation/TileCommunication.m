%if Com port open use fclose(instrfind()) in command window
fclose(instrfind())


arduino1 = serial('COM10','BaudRate',230400,'Terminator','CR') %initiate connection
%arduino2 = serial('COM3','BaudRate',230400,'Terminator','CR') 
%arduino3 = serial('COM3','BaudRate',230400,'Terminator','CR') 

mat1=zeros(1,3); %initiate matrix
%mat2=zeros(1,3); 
%mat3=zeros(1,3); 

fopen(arduino1); %open serial port
% fopen(arduino3); 
% fopen(arduino2); 

disp("GO")

tic

for c=1:3500
    line=fgetl(arduino1);%read line X-RAW, Y-RAW, Z-RAW
    str=str2num(line); %separates values by comma delimiter
    mat1=[mat1;str];%cat serial output to matrix
   
%     line=fgetl(arduino2);
%     str=str2num(line); 
%     mat2=[mat2;str];
%     
%     line=fgetl(arduino3);
%     str=str2num(line); 
%     mat3=[mat3;str];
     
end

fprintf(arduino1,0);% Write indicator to arduino

fclose(arduino1);
%fclose(arduino2);
%fclose(arduino3);

toc

OUT_X_1=mat1(:,1);
OUT_Y_1=mat1(:,2);
OUT_Z_1=mat1(:,3);

% OUT_X_2=mat2(:,1);
% OUT_Y_2=mat2(:,2);
% OUT_Z_2=mat2(:,3);
% 
% OUT_X_3=mat3(:,1);
% OUT_Y_3=mat3(:,2);
% OUT_Z_3=mat3(:,3);

MAG_1 =(OUT_X_1.^2 + OUT_Y_1.^2 + OUT_Z_1.^2).^(1/2);
%MAG_2 =(OUT_X_2.^2 + OUT_Y_2.^2 + OUT_Z_2.^2).^(1/2);
%MAG_3 =(OUT_X_3.^2 + OUT_Y_3.^2 + OUT_Z_3.^2).^(1/2);

plotfigures(OUT_X_1,OUT_Y_1,OUT_Z_1, MAG_1, 'Arduino1')
% plotfigures(OUT_X_1,OUT_Y_1,OUT_Z_1, MAG_1, 'Arduino2')
% plotfigures(OUT_X_1,OUT_Y_1,OUT_Z_1, MAG_1, 'Arduino3')





