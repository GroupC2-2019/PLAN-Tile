function plotfigures(in1, in2, in3, in4)
    figure('Name', 'XYZ Raw and MAG');
    subplot(4,1,1);
    plot(in1);
    ylim([-2048 2048]);
    title('X-axis Raw');
    subplot(4,1,2);
    plot(in2);
    ylim([-2048 2048]);
    title('Y-axis Raw');
    subplot(4,1,3);
    plot(in3);
    ylim([-2048 2048]);
    title('Z-axis Raw');
    subplot(4,1,4);
    plot(in4);
    title('MAG');
end