%initialization of X Y and Z High Low Vectors
OUT_X_L = [0 0];
OUT_X_H = [0 0];

OUT_Y_L = [0 0];
OUT_Y_H = [0 0];

OUT_Z_L = [0 0];
OUT_Z_H = [0 0];

OUT_X=0;
OUT_Y=0;
OUT_Z=0;


sample = [0 0];
status = 1;
count=1;

%readRegister Registers for Low an High Registers for X Y Z axis
%while count < 100000



 while count < 1000   
    disp(count);
    
    %while status < 143
     %  status=readRegister(accel,27);
    %end
    
    OUT_X_L(count) = readRegister(accel, 40, 'uint8');
    OUT_X_H(count) = readRegister(accel, 41, 'int8');
    
    OUT_Y_L(count) = readRegister(accel, 42, 'uint8');
    OUT_Y_H(count) = readRegister(accel, 43, 'int8');
    
    OUT_Z_L(count) = readRegister(accel, 44, 'uint8');
    OUT_Z_H(count) = readRegister(accel, 45, 'int8');
   
    count=count+1;
    
    
    OUT_X = (OUT_X_H .* 2^8 + OUT_X_L)./16;
    OUT_Y = (OUT_Y_H .* 2^8 + OUT_Y_L)./16;
    OUT_Z = (OUT_Z_H .* 2^8 + OUT_Z_L)./16;

    figure('Name', 'XYZ Raw');
    subplot(3,1,1);
    plot(OUT_X);
    title('X-axis Raw');
    subplot(3,1,2);
    plot(OUT_Y);
    title('Y-axis Raw');
    subplot(3,1,3);
    plot(OUT_Z);
    title('Z-axis Raw');
    drawnow;
end
