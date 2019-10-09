Fs = length(OUT_Z)/6;            % Sampling frequency                    
T = 1/Fs;            % Sampling period       
L = length(TempZ);   % Length of signal
t = (0:L-1)*T;       % Time vector

Z_FFT = TempZ - Mean_Noise(3);

Y = fft(Z_FFT);

P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
f = Fs*(0:(L/2))/L;


figure('Name', 'FFT');
subplot(2,1,1);
plot(Z_FFT);
title('Time Domain');
subplot(2,1,2);
plot(f, P1);
title('Freq Domain');