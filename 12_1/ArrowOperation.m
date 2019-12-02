function [tile_1, tile_2, tile_3] = ArrowOperation(arrowcord)
%     north=imread('north.png');
%     northeast=imread('northeast.png');
%     northwest=imread('northwest.png');
%     east=imread('east.png');
%     southeast=imread('southeast.png');
%     south=imread('south.png');
%     southwest=imread('southwest.png');
%     west=imread('west.png');
    
    x_cord=arrowcord(1)
    y_cord=arrowcord(2)
    tile_1=0;
    tile_2=0;
    tile_3=0;
    
    if x_cord < 2.5 %123
        tile_1 = 0;
        tile_2 = 0;
        tile_3 = 0;
    elseif x_cord >= 2.5 & x_cord < 4.5 & y_cord < 2 %4
        tile_1 = 1;
        tile_2 = 0;
        tile_3 = 2;    
             
    elseif x_cord >= 2.5 & x_cord < 4.5 & y_cord >= 2 %5
        tile_1 = 0;
        tile_2 = 7;
        tile_3 = 6; 
 
    elseif x_cord >= 4.5 & x_cord < 8 & y_cord < 1.25 & y_cord > 0 %6
        tile_1 = 1;
        tile_2 = 0;
        tile_3 = 3; 
       
        
    elseif x_cord >= 4.5 & x_cord < 7.25 & y_cord >= 1.25 & y_cord < 2.75 %7
        tile_1 = 1;
        tile_2 = 7;
        tile_3 = 4; 
      
    elseif x_cord >= 4.5 &x_cord < 8 & y_cord >= 2.75 & y_cord > 4 %8
        tile_1 = 1;
        tile_2 = 7;
        tile_3 = 5; 
     
    elseif  x_cord >= 4.5 &  x_cord < 8 &  y_cord < 1.25 &  y_cord > 0 %9
        tile_1 = 2;
        tile_2 = 6;
        tile_3 = 4; 
     
    end
    
%     if tile_1 ==0 | tile_2 ==0 | tile_3 ==0
%          imshow(north)
%      elseif tile_1 ==1 | tile_2 ==1 | tile_3 ==1
%          imshow(northwest)
%      elseif tile_1 ==2 | tile_2 ==2 | tile_3 ==2
%          imshow(west)
%      elseif tile_1 ==3 | tile_2 ==3 | tile_3 ==3
%          imshow(southwest)
%      elseif tile_1 ==4 | tile_2 ==4 | tile_3 ==4
%          imshow(south)
%      elseif tile_1 ==5 | tile_2 ==5 | tile_3 ==5
%          imshow(southeast)
%      elseif tile_1 ==6 | tile_2 ==6 | tile_3 ==6
%          imshow(east)
%     elseif tile_1 ==7 | tile_2 ==7 | tile_3 ==7
%         imshow(northeast)
%     end      
%     

end

    

    %0-n, 1-nw 2-w 3-sw 4-s 5-se 6-e 7-ne
    %for s=1:6 
%         if ratio1 > 1 & ratio2 > 1 & ratio3 > 0.9 & ratio3 < 1.1
%       
%                 meancord = [meancord; cord(s,1) cord(s,2)];
%             else
%                 meancord = [meancord; meanx meany];
%             end
%         elseif ratio1 > 1 & ratio2 > 1 & ratio3 <1
%     
%                 meancord = [meancord; cord(s,1) cord(s,2)];
%             else
%                 meancord = [meancord; meanx meany];
%             end
%         elseif ratio1 > 1 & ratio2 > 1 & ratio3 > 1
%           
%                 meancord = [meancord; cord(s,1) cord(s,2)];
%             else
%                 meancord = [meancord; meanx meany];
%             end
%         elseif ratio1 > 1 & ratio2 > 0.75 & ratio2 < 1.25 & ratio3 < 1
%            
%                 meancord = [meancord; cord(s,1) cord(s,2)];
%             else
%                 meancord = [meancord; meanx meany];
%             end
%         elseif ratio1 > 0.75 & ratio1 < 1.25 & ratio2 > 0.75 & ratio2 < 1.25 & ratio3 > 0.75 & ratio3 < 1.25
%             
%                 meancord = [meancord; cord(s,1) cord(s,2)];
%             else
%                 meancord = [meancord; meanx meany];
%             end
%         elseif ratio1 > 0.75 & ratio1 < 1.25 & ratio2 > 1 & ratio3 > 1
%             
%                 meancord = [meancord; cord(s,1) cord(s,2)];
%             else
%                 meancord = [meancord; meanx meany];
%             end
%         elseif ratio1 < 1 & ratio2 < 1 & ratio3 > 0.9 & ratio3 < 1.1
%             if cord(s,1) >= 7.5 & cord(s,1) < 8 & cord(s,2) >= 0.5 & cord(s,2) > 3.5
%                 meancord = [meancord; cord(s,1) cord(s,2)];
%             else
%                 meancord = [meancord; meanx meany];
%             end
%         else
%             meancord = [meancord; meanx meany];
%         end
%     end
    