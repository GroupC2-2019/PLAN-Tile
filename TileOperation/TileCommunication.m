%Constants
prev_frames = 50; % Number of frames before to save before trigger
total_frames = 300; % Total number of frames to save per event

%if Com port open use fclose(instrfind()) in command window
clc
fclose(instrfind());
close all

arduino1 = serial('COM3','BaudRate',230400,'Terminator','CR');
arduino2 = serial('COM6','BaudRate',230400,'Terminator','CR');
arduino3 = serial('COM7','BaudRate',230400,'Terminator','CR');

% arduino1.InputBufferSize = 20;
% arduino2.InputBufferSize = 20;
%arduino3.InputBufferSize = 20;
hzmax1 = [];
hzmax2 = [];
hzmax3 = [];

fopen(arduino1);
fopen(arduino2);
fopen(arduino3);

for new_i = 1:10
    mat1=[];
    mat2=[];
    mat3=[]; 



    max_z = 1000;

    disp("GO")
    i = 1;
    while(max_z > 850 & max_z < 1150)
        line=fgetl(arduino1);
        str1=str2num(line);
        if length(str1) == 1 & ~isempty(str1)
            if(str1 > -2048 & str1 < 2048)
                mat1=[mat1;str1];
            end
        end

        line=fgetl(arduino2);
        str2=str2num(line); 
        if length(str1) == 1 & ~isempty(str2)
            if(str1 > -2048 & str1 < 2048)
                mat2=[mat2;str2];
            end
        end

        line=fgetl(arduino3);
        str3=str2num(line); 
        if length(str3) == 1 & ~isempty(str3)
            if(str3 > -2048 & str3 < 2048)
                mat3=[mat3;str3];
            end
        end
        
        if length(str1) == 1 & ~isempty(str1) & length(str2) == 1 & ~isempty(str2) & length(str3) == 1 & ~isempty(str3)
            max_z = max([str1, str2, str3]);    
        end
        i=i+1;
    end
    disp("Trigger")

    if(length(mat1) > prev_frames)
        mat1 = mat1(length(mat1)-prev_frames+1: length(mat1));
    end

    if(length(mat2) > prev_frames)
        mat2 = mat2(length(mat2)-prev_frames+1: length(mat2));
    end

    if(length(mat3) > prev_frames)
        mat3 = mat3(length(mat3)-prev_frames+1: length(mat3));
    end

    tic
    for i = prev_frames+1:total_frames
        line=fgetl(arduino1);
        str1=str2num(line);
        if length(str1) == 1 & ~isempty(str1)
            mat1=[mat1;str1];
        end

        line=fgetl(arduino2);
        str2=str2num(line);   
        if length(str2) == 1 & ~isempty(str2)
            mat2=[mat2;str2];
        end

        line=fgetl(arduino3);
        str3=str2num(line); 
        if length(str3) == 1 & ~isempty(str3)
            if(str3 > -2048 & str3 < 2048)
                mat3=[mat3;str3];
            end
        end
    end
    time = toc;

    samples1 = mat1 - mean(mat1);
    samples2 = mat2 - mean(mat2);
    samples3 = mat3 - mean(mat3);

% 
%     plot(samples1)
%     hold on
%     plot(samples2)
%     hold on
%     plot(samples3)
%     ylim([-2048 2048])
%     legend("Arduino1", "Arduino2", "Arduino3");

    Fs = total_frames / (time * total_frames/(total_frames-prev_frames));
    T = 1/Fs;


%     figure

    L = length(samples1);
    L2 = floor(L/2);
    t = (0:L-1)*T;
    Y = fft(samples1);
    P2 = abs(Y/L);
    FFT1 = P2(1:L2+1);
    FFT1(2:end-1) = 2*FFT1(2:end-1);
    f1 = Fs*(0:(L2))/L;
%     plot(f1,FFT1) 
%     hold on

    L = length(samples2);
    L2 = floor(L/2);
    t = (0:L-1)*T;
    Y = fft(samples2);
    P2 = abs(Y/L);
    FFT2 = P2(1:L2+1);
    FFT2(2:end-1) = 2*FFT2(2:end-1);
    f2 = Fs*(0:(L2))/L;
%     plot(f2,FFT2) 
%     hold on

    L = length(samples3);
    L2 = floor(L/2);
    t = (0:L-1)*T;
    Y = fft(samples3);
    P2 = abs(Y/L);
    FFT3 = P2(1:L2+1);
    FFT3(2:end-1) = 2*FFT3(2:end-1);
    f3 = Fs*(0:(L2))/L;
%     plot(f3,FFT3) 
%     title("FFT")
%     legend("Arduino1", "Arduino2", "Arduino3");

%     figure
%     plot(f1/pi,10*log10(FFT1))
%     hold on
%     plot(f1/pi,10*log10(FFT2))
%     hold on
%     plot(f1/pi,10*log10(FFT3))
%     title("Spctral Power Density")
%     legend("Arduino1", "Arduino2", "Arduino3");
%     ylim([-20 20])
    
    

    temp = [];
    temp2 = [];
    temp3 = [];
    temp4 = [];
    temp5 = [];
    temp6 = [];
    for i=1:length(f1)
        if f1(i) <= 25
            temp = [temp; FFT1(i)];
        elseif f1(i) <= 50
            temp2 = [temp2; FFT1(i)];
        elseif f1(i) <=75
            temp3 = [temp3; FFT1(i)];
        elseif f1(i) <=100
            temp4 = [temp4; FFT1(i)];
        elseif f1(i) <=150
            temp5 = [temp5; FFT1(i)];
        elseif f1(i) <=200
            temp6 = [temp6; FFT1(i)];
        else
            break
        end
    end
    
    hzmax1 =[hzmax1; max(temp) max(temp2) max(temp3) max(temp4) max(temp5) max(temp6)]

    temp = [];
    temp2 = [];
    temp3 = [];
    temp4 = [];
    temp5 = [];
    temp6 = [];

    for i=1:length(f2)
        if f2(i) <= 25
            temp = [temp; FFT2(i)];
        elseif f2(i) <= 50
            temp2 = [temp2; FFT2(i)];
        elseif f2(i) <=75
            temp3 = [temp3; FFT2(i)];
        elseif f2(i) <=100
            temp4 = [temp4; FFT2(i)];
        elseif f2(i) <=150
            temp5 = [temp5; FFT2(i)];
        elseif f2(i) <=200
            temp6 = [temp6; FFT2(i)];
        else
            break
        end
    end
    
    hzmax2 =[hzmax2; max(temp) max(temp2) max(temp3) max(temp4) max(temp5) max(temp6)]


    temp = [];
    temp2 = [];
    temp3 = [];
    temp4 = [];
    temp5 = [];
    temp6 = [];

    for i=1:length(f3)
        if f3(i) <= 25
            temp = [temp; FFT3(i)];
        elseif f3(i) <= 50
            temp2 = [temp2; FFT3(i)];
        elseif f3(i) <=75
            temp3 = [temp3; FFT3(i)];
        elseif f3(i) <=100
            temp4 = [temp4; FFT3(i)];
        elseif f3(i) <=150
            temp5 = [temp5; FFT3(i)];
        elseif f3(i) <=200
            temp6 = [temp6; FFT3(i)];
        else
            break
        end
    end
    
    hzmax3 =[hzmax3; max(temp) max(temp2) max(temp3) max(temp4) max(temp5) max(temp6)]


%     hzmax1 = [hzmax1; mean(abs(samples1)) max(abs(samples1))]
%     hzmax2 = [hzmax2; mean(abs(samples2)) max(abs(samples2))]
%     hzmax3 = [hzmax3; mean(abs(samples3)) max(abs(samples3))]

    % ratio1 = sum(FFT1(15:25))/sum(FFT1(50:75));
    % ratio2 = sum(FFT2(15:25))/sum(FFT2(50:75));
    % ratio3 = sum(FFT3(15:25))/sum(FFT3(50:75));
    % 
    % r1 = -2.058 * log(ratio1) + 0.7911;
    % r2 = -2.058 * log(ratio2) + 0.7911;
    % r3 = -2.058 * log(ratio3) + 0.7911;
    % 
    % r1
    % r2
    % r3
    % [x, y] = findIntersection(r1,r2,r3)
    % x
    % y
    
end

fclose(arduino1);
fclose(arduino2);
fclose(arduino3);

% packet_loss_percent = 100 - [100*length(mat1)/total_frames 100*length(mat2)/total_frames 100*length(mat3)/total_frames]
% 
% sum(abs(samples1))
% sum(abs(samples2))
% sum(abs(samples3))
