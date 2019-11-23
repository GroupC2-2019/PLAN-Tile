%if Com port open use fclose(instrfind()) in command window
fclose(instrfind())

close all

arduino1 = serial('COM3','BaudRate',230400,'Terminator','CR') %initiate connection
arduino2 = serial('COM6','BaudRate',230400,'Terminator','CR') 
arduino3 = serial('COM7','BaudRate',230400,'Terminator','CR') 

mat1=0; %initiate matrix
mat2=0; 
mat3=0; 

fopen(arduino1); %open serial port
fopen(arduino3); 
fopen(arduino2); 

max_z = -1000;

disp("GO")

tic

while(max_z > -1150 & max_z < -850)
    %for c=1:3500
    line=fgetl(arduino1);%read line X-RAW, Y-RAW, Z-RAW
    str1=str2num(line); %separates values by comma delimiter
    mat1=[mat1;str1];%cat serial output to matrix

    line=fgetl(arduino2);
    str2=str2num(line); 
    mat2=[mat2;str2];

    line=fgetl(arduino3);
    str3=str2num(line); 
    mat3=[mat3;str3]; 
    
    max_z = max([str1, str2, str3]);
end

disp("Trigger")

%fprintf(arduino1,0);% Write indicator to arduino
length(mat1)

mat1 = mat1(length(mat1)-20:length(mat1))
mat2 = mat2(length(mat2)-20:length(mat2))
mat3 = mat3(length(mat3)-20:length(mat3))

% mat1 = [];
% mat2 = [];
% mat3 = [];

for i=1:230
    line=fgetl(arduino1);%read line X-RAW, Y-RAW, Z-RAW
    str1=str2num(line); %separates values by comma delimiter
    mat1=[mat1;str1];%cat serial output to matrix

    line=fgetl(arduino2);
    str2=str2num(line); 
    mat2=[mat2;str2];

    line=fgetl(arduino3);
    str3=str2num(line); 
    mat3=[mat3;str3]; 
end
     

fclose(arduino1);
fclose(arduino2);
fclose(arduino3);

toc

OUT_X_1=mat1;
OUT_Y_1=mat1;
OUT_Z_1=mat1;


OUT_X_2=mat2;
OUT_Y_2=mat2;
OUT_Z_2=mat2;

OUT_X_3=mat3;
OUT_Y_3=mat3;
OUT_Z_3=mat3;

MAG_1 =(OUT_X_1.^2 + OUT_Y_1.^2 + OUT_Z_1.^2).^(1/2);
MAG_2 =(OUT_X_2.^2 + OUT_Y_2.^2 + OUT_Z_2.^2).^(1/2);
MAG_3 =(OUT_X_3.^2 + OUT_Y_3.^2 + OUT_Z_3.^2).^(1/2);

plotfigures(OUT_X_1,OUT_Y_1,OUT_Z_1, MAG_1, 'Arduino1')
plotfigures(OUT_X_1,OUT_Y_1,OUT_Z_1, MAG_1, 'Arduino2')
plotfigures(OUT_X_1,OUT_Y_1,OUT_Z_1, MAG_1, 'Arduino3')