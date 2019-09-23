%Connected to Arduino using Arduino() Function in MatLab
clear;
uno = arduino('COM3','Uno', 'Libraries', 'I2C');
accel = i2cdev(uno,'0x18');


%1. Write CTRL_REG1
%2. Write CTRL_REG2
%3. Write CTRL_REG3
%4. Write CTRL_REG4
%5. Write CTRL_REG5
%6. Write CTRL_REG6
%7. Write REFERENCE
%8. Write INTx_THS
%9. Write INTx_DUR
%10. Write INTx_CFG
%11. Write CTRL_REG5

pause(1);

%CTRL1
writeRegister(accel, 32, 151);
writeRegister(accel, 32, 151);
%writeRegister(accel, '0x20', 87);
pause(0.5);

%CTRL2
writeRegister(accel, 33, 0);
pause(0.5);

%CTRL3
writeRegister(accel, 34, 0);
pause(0.5);

%CTRL4
writeRegister(accel, 35, 9);
pause(0.5);

%CTRL5
writeRegister(accel, 36, 0);
pause(0.5);

%CTRL6
writeRegister(accel, 37, 0);
pause(0.5);

