set xlabel 'x'
set ylabel 'f(x) = sqrt(x)'
set title 'Graphique de f(x) = sqrt(x)'
set grid
set style data lines
plot 'gnuplot.dat' using 1:2 lw 2 linecolor rgb 'blue'
pause mouse close
