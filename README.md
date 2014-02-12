little-simulation-SDK
=====================

SDK to simulate physical, mathematical and other things.

This SoftwareDevelopmentKit gives you some code to build your own simulations in a fast way. The only thing you have to do is to edit the "sim0_2.cpp"-file with your calculations. The "sim*.cpp"-Files has two parts. The first part is for your simulation and the second for the data management and simulation control.


WHY IT IS SO FAST?

The program is very short and hardware based. It is probably as fast as C++ itself, because the simulations are written and compiled with C++. The data management and simulation control writes the data efficient in the datafile by using a large buffer and good algorithms.


ARCHITEKTURE OF THE SIMULATION-SDK

To use it you have to edit the simulation-function and specialize if for your issues. If you wrote the simulation programm with all calculations you need, you can decide what variable you want to see in a diagram at the end of the simulation process. The simulation SDK runs the simulation-function while the condition (return of the simulation-function) is true. The data (x and y in the diagram) would be print in a file you can choose. With these file, its an easy way to display the diagram by using gnuplot.


HOW TO RUN THE SIMUALTIONS?

If you want to run some simulation, you have two possibilities. The best way under Linux (and Mac) is to use the run-script. You only have to say what you simulation is and what your datafile should be. The script runs also gnuplot after the compiling and the simulation process. e.g.:

./run examples/sim_paper_plane.cpp datafile

The second way (e.g. under Windows) is to compile the simulation and run it. e.g:

g++ -o sim examples/sim_paper_plane.cpp
./sim datafile
gnuplot

=====================

Please contact me if you find some bugs or language mistakes.
