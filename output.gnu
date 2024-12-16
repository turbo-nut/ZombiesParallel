#creating gnuplot

plot "data/daySZRD.dat" u 1:2 w lines title "S", "data/daySZRD.dat" u 1:3 w lines title "Z", "data/daySZRD.dat" u 1:4 w lines title "R", "data/daySZRD.dat" u 1:5 w lines title "D", "data/daySZRD.dat" u 1:6 w lines title "I"
pause -1 "hit enter to continue"
