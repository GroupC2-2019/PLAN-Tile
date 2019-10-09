b = Walk1;

OUT_X=b(:,1);
OUT_Y=b(:,2);
OUT_Z=b(:,3);

MAG =(OUT_X.^2 + OUT_Y.^2 + OUT_Z.^2).^(1/2);

figure('Name', 'XYZ Raw');
subplot(4,1,1);
plot(OUT_X);
ylim([-2048 2048]);
title('X-axis Raw');
subplot(4,1,2);
plot(OUT_Y);
ylim([-2048 2048]);
title('Y-axis Raw');
subplot(4,1,3);
plot(OUT_Z);
ylim([-2048 2048]);
title('Z-axis Raw');
subplot(4,1,4);
plot(MAG);
ylim([-2048 2048]);
title('MAG');