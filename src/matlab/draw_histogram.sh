#!/bin/bash 
matlab -nodesktop -nosplash -r "figure('visible', 'off');hist = importdata('$1'); bar( hist(:,1) , hist(:,2) ); print('$2' ,'-dpng'); exit;"
