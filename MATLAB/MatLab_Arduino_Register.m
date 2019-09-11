%Connected to Arduino using Arduino() Function in MatLab
mega = arduino('COM3','Mega2560', 'Libraries', 'I2C');
accel = device(mega, 'I2CAddress', '0x18');

%Register '0x20' Control Register 1
%Settings as following: 01010111 - High Resolution 100HZ Z Y and X Enable
writeRegister(accel, '0x20', 71);

%Register '0x23' Control Register 4
%Settings as following: 00111001 - Continuous 16G scale High Resolution
writeRegister(accel, '0x23', 25);

%Note in High Resolution, Data is in 12 bit mode with High bit shift then
%low
pause (1);

%initialization of X Y and Z High Low Vectors
OUT_X_L = [0 0];
OUT_X_H = [0 0];

OUT_Y_L = [0 0];
OUT_Y_H = [0 0];

OUT_Z_L = [0 0];
OUT_Z_H = [0 0];

sample = [0 0];

%Read Registers for Low an High Registers for X Y Z axis
for count = 1:1:500
    disp(count);
    
    sample(count) = count;
    
    OUT_X_L(count) = readRegister(accel, '0x28', 'int8');
    OUT_X_H(count) = readRegister(accel, '0x29', 'int8');
    
    OUT_Y_L(count) = readRegister(accel, '0x2a', 'int8');
    OUT_Y_H(count) = readRegister(accel, '0x2b', 'int8');
    
    OUT_Z_L(count) = readRegister(accel, '0x2c', 'int8');
    OUT_Z_H(count) = readRegister(accel, '0x2d', 'int8');
    
    pause(1/100)
end

clear accel count mega;

x = OUT_X_H .*2^8 + OUT_X_L;
y = OUT_Y_H .*2^8 + OUT_Y_L;
z = OUT_Z_H .*2^8 + OUT_Z_L;

%Normalize to range plus minus 16g
range = [-16 16];

x_n = normalize(x, 'range', range);
y_n = normalize(y, 'range', range);
z_n = normalize(z, 'range', range);

%Normalizization as per the device Header files
x_d = x ./ 1365;
y_d = y ./ 1365;
z_d = z ./ 1365;

figure('Name', 'XYZ Raw');
subplot(3,1,1);
plot(sample, x);
title('X-axis Raw');
subplot(3,1,2);
plot(sample, y);
title('Y-axis Raw');
subplot(3,1,3);
plot(sample, z);
title('Z-axis Raw');


figure('Name', 'XYZ Divided');
subplot(3,1,1);
plot(sample, x_d);
ylim([-16 16]);
title('X-axis Divided');
subplot(3,1,2);
plot(sample, y_d);
ylim([-16 16]);
title('Y-axis Divided');
subplot(3,1,3);
plot(sample, z_d);
ylim([-16 16]);
title('Z-axis Divided');
