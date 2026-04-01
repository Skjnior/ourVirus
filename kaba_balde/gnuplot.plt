set xlabel 'x'
set ylabel 'f(x) = ln(x+1)'
set title 'Graphique de f(x) = ln(x+1)'
set grid
set style data lines
plot 'gnuplot.dat' using 1:2 lw 2 linecolor rgb 'blue'
pause mouse close
