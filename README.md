Little-Simulation-Software-Development-Kit
=====================

This is a very fast and small Software-Development-Kit for numerical simulations. You can simulate an infinite number of things in physics, math, economy...

This Software-Development-Kit give you some code to build your own simulations in a fast way. The only thing you have to do is to edit the "sim0_2.cpp"-file with your own calculations. Please notice, that the "sim*.cpp"-Files has two parts: The first part is for your simulation-program and the second is for the data management and simulation control (Don't change this part). In the examples-directory are a lot of programs you can look for.


WHY IT IS SO FAST?

The program is very small and hardware based. It's probably as fast as C++ itself, because the simulations are written and compiled with C++. The data management and simulation control writes the data efficient in the data file by using a large buffer and fast algorithms. In version 0.3 and higher you can also use the LIVE-mode, that prints the data (and only the data) to the screen and not in a file. That can use to pipe the data in a other program or script.

In version 0.3 and higher there are also ways to use parallel programming by using openmp. If you are familiar with openmp you can parallelize your own calculations. In each case the data management uses two threads. One to calculate the simulation and one to write it to a file or screen.


ARCHITEKTURE OF THE SIMULATION-SDK

The SDK is split in different files and scripts. In the following schema you can see the files and its meaning.

sim_0_3.cpp
The heart of the SDK. You have to edit this file with your calculations for the simulation process. Please follow the comments in the file.


The following files are only for an user friendly integration of C++ and gnuplot. That files are not necessary for all users, but they are recommended.


init_sim <*.cpp file> <data file>  (only Linux and Mac)
Initialization and configuration script. It is needed by the “run_sim” script and the “plot_sim” script.

run_sim <*.conf file>  (only Linux and Mac)
.. runs and compiles the simulation program. This is an user friendly way to run the simulation from the “sim_0_3.cpp” (other file names possible). You have to run the “init_sim” script first.

plot_sim <*.conf file>  (only Linux and Mac)
.. runs a gnuplot-script to plot the data. Please run “init_sim” and “run_sim” first. Otherwise it wouldn't run. “run_sim” starts “plot_sim” currently if its enabled.


HOW TO RUN THE SIMUALTIONS?

First you have to clone and rename the “sim_0_3.cpp”. Than you have to write your calculations in it. After that you have two possibilities:

1. (only Linux and Mac) The user friendly start scripts

First the simulation must be configured with the “init_sim”-script. This script saves the configuration in an *.conf file. Now you can run the simulation by running the “run_sim”-script. The parameter is the configuration file. This script compiles the *.cpp program and runs it. The output can be print with the “plot_sim”-scipt by using gnuplot. If you enabled gnuplot in the configuration it runs currently.

e.g.:

cd examples/paper_plane
./init_sim sim_paper_plane.cpp /tmp/datafile
./run_sim paper_plane.conf

# to show the graph again
./plot_sim paper_plane.conf

2. (all OS) Manual compilation way

Compile the *.cpp script and run the application. The first parameter is the data file. Plot the data by using gnuplot or others. This way is more difficult, because you need more knowledge about C++ and gnuplot.

e.g.:

g++ -fopenmp -o sim examples/paper_plane/sim_paper_plane.cpp

./sim datafile

# declare your own gnuplot-script
gnuplot
> plot “datafile”


=====================

Please contact me, if you find some bugs or language mistakes.
