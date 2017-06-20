set datafile separator ","
set termoption dash
set style data points
set style line 1 lt 2 lw 10 pt 1 ps 0.5
set style line 2 lt 2 lw 10 pt 1 ps 0.5
set style line 3 lt 2 lw 10 pt 1 ps 0.5
set style line 4 lt 2 lw 10 pt 1 ps 0.5
set style line 5 lt 2 lw 10 pt 1 ps 0.5
plot 'points.csv' using 1:2 title 'f1' smooth unique with lines,\
	 'points.csv' using 1:3 title 'f2' smooth unique with lines,\
	 'points.csv' using 1:4 title 'f3' smooth unique with lines,\
	 'points.csv' using 1:5 title 'f4' smooth unique with lines,\
	 'points.csv' using 1:6 title 'f5' smooth unique with lines
pause mouse any "Any key or button will terminate"