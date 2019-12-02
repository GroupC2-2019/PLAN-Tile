%Constants
prev_frames = 50; % Number of frames before to save before trigger
total_frames = 300; % Total number of frames to save per event

%if Com port open use fclose(instrfind()) in command window
clc
fclose(instrfind());
close all

arduino1 = serial('COM4','BaudRate',250000,'Terminator','CR');

% arduino1.InputBufferSize = 20;
% arduino2.InputBufferSize = 20;
%arduino3.InputBufferSize = 20;
hzmax1 = [];
hzmax2 = [];
hzmax3 = [];

tile1 = [];
tile2 = [];
tile3 = [];

locationGuess = [];

fopen(arduino1);

for new_i = 1:10
    mat1=[];
    mat2=[];
    mat3=[]; 
    
    max_z = 1000;

    disp("GO")

    % Wait for trigger
    i = 1;
    while(max_z > 850 & max_z < 1150)
        line=fgetl(arduino1);
        str=str2num(line);
        if length(str) == 3 & ~isempty(str)
            mat1=[mat1;str(1)];
            mat2=[mat2;str(2)];
            mat3=[mat3;str(3)];
        end
        
        if length(str) == 3 & ~isempty(str)
            max_z = max(str);    
        end
        i=i+1;
    end
    disp("Trigger")

    % Keep a few frames before the trigger
    if(length(mat1) > prev_frames)
        mat1 = mat1(length(mat1)-prev_frames+1: length(mat1));
    end

    if(length(mat2) > prev_frames)
        mat2 = mat2(length(mat2)-prev_frames+1: length(mat2));
    end

    if(length(mat3) > prev_frames)
        mat3 = mat3(length(mat3)-prev_frames+1: length(mat3));
    end

    % Take data after the trigger event
    tic    
    for i = prev_frames+1:total_frames
        line=fgetl(arduino1);
        str=str2num(line);
        if length(str) == 3 & ~isempty(str)
            mat1=[mat1;str(1)];
            mat2=[mat2;str(2)];
            mat3=[mat3;str(3)];
        end
    end
    time = toc;

    samples1 = mat1 - mean(mat1);
    samples2 = mat2 - mean(mat2);
    samples3 = mat3 - mean(mat3);

    % Plot amplitude-time graphs
%     plot(samples1)
%     hold on
%     plot(samples2)
%     hold on
%     plot(samples3)
%     ylim([-2048 2048])
%     legend("Arduino1", "Arduino2", "Arduino3");

    % Get FFTs
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
    
    
    power1 = mean((mat1 - 998.7).^2);
    power2 = mean((mat2 - 991.19).^2);
    power3 = mean((mat3 - 972.87).^2);

    ratio1 = power3 / power2;
    ratio2 = power3 / power1;
    ratio3 = power2 / power1;
    
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
        elseif f2(i) <= 75
            temp3 = [temp3; FFT2(i)];
        elseif f2(i) <= 100
            temp4 = [temp4; FFT2(i)];
        elseif f2(i) <= 150
            temp5 = [temp5; FFT2(i)];
        elseif f2(i) <= 200
            temp6 = [temp6; FFT2(i)];
        else         
            break         
        end
    end
    
    hzmax2 = [max(temp) max(temp2) max(temp3) max(temp4) max(temp5) max(temp6)];
    
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
        elseif f1(i) <= 75
            temp3 = [temp3; FFT1(i)];
        elseif f1(i) <= 100
            temp4 = [temp4; FFT1(i)];
        elseif f1(i) <= 150
            temp5 = [temp5; FFT1(i)];
        elseif f1(i) <= 200
            temp6 = [temp6; FFT1(i)];
        else         
            break         
        end
    end
    
    hzmax1 = [max(temp) max(temp2) max(temp3) max(temp4) max(temp5) max(temp6)];
 
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
        elseif f3(i) <= 75
            temp3 = [temp3; FFT3(i)];
        elseif f3(i) <= 100
            temp4 = [temp4; FFT3(i)];
        elseif f3(i) <= 150
            temp5 = [temp5; FFT3(i)];
        elseif f3(i) <= 200
            temp6 = [temp6; FFT3(i)];
        else         
            break         
        end
    end
    
    hzmax3 = [max(temp) max(temp2) max(temp3) max(temp4) max(temp5) max(temp6)];
    
    r1 = [];
    r2 = [];
    r3 = [];
    
    eq1 = abs(log(hzmax1(:,1)/33.357)/-0.216);
    eq2 = abs(log(hzmax1(:,2)/37.725)/-0.207);
    eq3 = abs(log(hzmax1(:,3)/26.275)/-0.211);
    eq4 = abs(log(hzmax1(:,4)/19.709)/-0.169);
    eq5 = abs(log(hzmax1(:,5)/21.142)/-0.157);
    eq6 = abs(log(hzmax1(:,6)/17.504)/-0.129);
    
    r1 = [eq1 eq2 eq3 eq4 eq5 eq6];
    
    eq1 = abs(log(hzmax2(:,1)/33.357)/-0.216);
    eq2 = abs(log(hzmax2(:,2)/37.725)/-0.207);
    eq3 = abs(log(hzmax2(:,3)/26.275)/-0.211);
    eq4 = abs(log(hzmax2(:,4)/19.709)/-0.169);
    eq5 = abs(log(hzmax2(:,5)/21.142)/-0.157);
    eq6 = abs(log(hzmax2(:,6)/17.504)/-0.129);
    
    r2 = [eq1 eq2 eq3 eq4 eq5 eq6];
    
    eq1 = abs(log(hzmax3(:,1)/33.357)/-0.216);
    eq2 = abs(log(hzmax3(:,2)/37.725)/-0.207);
    eq3 = abs(log(hzmax3(:,3)/26.275)/-0.211);
    eq4 = abs(log(hzmax3(:,4)/19.709)/-0.169);
    eq5 = abs(log(hzmax3(:,5)/21.142)/-0.157);
    eq6 = abs(log(hzmax3(:,6)/17.504)/-0.129);
    
    r3 = [eq1 eq2 eq3 eq4 eq5 eq6];
    
    cord = [];
    
    [x , y] = findIntersection(r1(1), r2(1), r3(1));
    cord = [cord; x y];
    [x , y] = findIntersection(r1(2), r2(2), r3(2));
    cord = [cord; x y];
    [x , y] = findIntersection(r1(3), r2(3), r3(3));
    cord = [cord; x y];
    [x , y] = findIntersection(r1(4), r2(4), r3(4));
    cord = [cord; x y];
    [x , y] = findIntersection(r1(5), r2(5), r3(5));
    cord = [cord; x y];
    [x , y] = findIntersection(r1(6), r2(6), r3(6));
    cord = [cord; x y];

    meanx = mean(cord(:,1));
    meany = mean(cord(:,2));
    
    
    s = 0;
    meancord = [];
    
    for s=1:6
        if ratio1 > 1 & ratio2 > 1 & ratio3 > 0.9 & ratio3 < 1.1
            if cord(s,1) < 2.5
                meancord = [meancord; cord(s,1) cord(s,2)];
            else
                meancord = [meancord; meanx meany];
            end
        elseif ratio1 > 1 & ratio2 > 1 & ratio3 <1
            if cord(s,1) >= 2.5 & cord(s,1) < 4.5 & cord(s,2) < 2
                meancord = [meancord; cord(s,1) cord(s,2)];
            else
                meancord = [meancord; meanx meany];
            end
        elseif ratio1 > 1 & ratio2 > 1 & ratio3 > 1
            if cord(s,1) >= 2.5 & cord(s,1) < 4.5 & cord(s,2) >= 2
                meancord = [meancord; cord(s,1) cord(s,2)];
            else
                meancord = [meancord; meanx meany];
            end
        elseif ratio1 > 1 & ratio2 > 0.75 & ratio2 < 1.25 & ratio3 < 1
            if cord(s,1) >= 4.5 & cord(s,1) < 8 & cord(s,2) < 1.25 & cord(s,2) > 0
                meancord = [meancord; cord(s,1) cord(s,2)];
            else
                meancord = [meancord; meanx meany];
            end
        elseif ratio1 > 0.75 & ratio1 < 1.25 & ratio2 > 0.75 & ratio2 < 1.25 & ratio3 > 0.75 & ratio3 < 1.25
            if cord(s,1) >= 4.5 & cord(s,1) < 7.25 & cord(s,2) >= 1.25 & cord(s,2) < 2.75
                meancord = [meancord; cord(s,1) cord(s,2)];
            else
                meancord = [meancord; meanx meany];
            end
        elseif ratio1 > 0.75 & ratio1 < 1.25 & ratio2 > 1 & ratio3 > 1
            if cord(s,1) >= 4.5 & cord(s,1) < 8 & cord(s,2) >= 2.75 & cord(s,2) > 4
                meancord = [meancord; cord(s,1) cord(s,2)];
            else
                meancord = [meancord; meanx meany];
            end
        elseif ratio1 < 1 & ratio2 < 1 & ratio3 > 0.9 & ratio3 < 1.1
            if cord(s,1) >= 7.5 & cord(s,1) < 8 & cord(s,2) >= 0.5 & cord(s,2) > 3.5
                meancord = [meancord; cord(s,1) cord(s,2)];
            else
                meancord = [meancord; meanx meany];
            end
        else
            meancord = [meancord; meanx meany];
        end
    end
    
                
            
    
    
%     for s=1:6
%         if (cord(s,1) < 1.5+meanx & cord(s,1) > meanx-1.5) & (cord(s,2) < 1.5+meany & cord(s,2) > meany-1.5)
%             meancord = [meancord; cord(s,1) cord(s,2)];
%         else
%             meancord = [meancord; meanx meany];
%         end
%     end
%     
%     ratio1
%     ratio2
%     ratio3
    
    arrowCord = [mean(meancord(:,1)) mean(meancord(:,2))];
    
    locationGuess = [locationGuess; mean(meancord(:,1)) mean(meancord(:,2))];
    
    scatter(locationGuess(:,1),locationGuess(:,2));
    ylim([0 4]);
    xlim([0 8]);
    
    for i=1:length(locationGuess)
        [t1, t2, t3] = ArrowOperation(arrowCord)
        %fprintf(arduino1, t1);
        %fprintf(arduino1, t2);
        %fprintf(arduino1, t3);        
    end 
    
    
end



fclose(arduino1);
