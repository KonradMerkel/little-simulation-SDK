reset

set term postscript eps
set ylabel 'y-axis'
set xlabel 'x-axis'
unset key
set autoscale
set title 'your title'
set output 'graph_default.eps'

f(x) = m*x + n
fit f(x) 'data' via m,n

plot [:] [:] 'your_datafile' lw 3 lc rgb 'black' with line, f(x) lc rgb 'red'
