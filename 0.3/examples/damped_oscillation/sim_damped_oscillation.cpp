/*
** Simulator
***************************************************************
** (c) Konrad Merkel
** SDK-Version: 0.3
** 23. Mai 2014
**************************************************************/
unsigned long int const buf = 50000 ;
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
using namespace std;

/* simulation */

// if you want to print the date in the standard output uncomment following line
//#define LIVE

// const
double const D=5; // N/m
double const m=0.05; // kg
double const dt=0.001; // s

// Variables
double F; // N
double Fr; // N
double v; // m/s
double t; // s
double y_s=0.01; // m

void begin()
{
  // Something that have to do first and only once.
}

bool simulation(double &x, double &y)
{
  Fr =0.777 * v*v;

  if (v>0)
    F=-D*y_s - Fr;
  else 
    F=-D*y_s + Fr;

  v=v+(F/m)*dt;
  y_s=y_s+v*dt;
  t=t+dt;
  
  x = t;
  y = y_s;
  
  // While
  if (t<=10) {return true;}
  else {return false;}
}



/*################ Only 4 developer's eyes! ################*/

/* system */

struct koordinatesBuffer{
  double *x;
  double *y;
};

void welcome()
{
  cout << "\n\nWelcome to Km-ware simulations\n";
  cout << "\nDeveloper: Konrad Merkel\nSDK-Version: 0.3.0\n\n\n";
}


void writeData(ofstream &myfile, struct koordinatesBuffer &buffer, unsigned long int buf_size = buf)
{
  for (int j=0 ; j<buf_size; j++){
#ifndef LIVE
    myfile << buffer.x[j] << "\t" << buffer.y[j] << "\n";
#else
    cout << buffer.x[j] << "\t" << buffer.y[j] << "\n";
#endif 
  }
}

int main(int argc, char* argv[])
{
#ifndef LIVE
  if (argc < 2){
    cout << "\nLittle-Simulation-Software-Development-Kit (LSSDK)\n";
    cout << "Developer: Konrad Merkel (2014)\n";
    cout << "--------------------------------------------------\n\n";
    cout << "Use a data file: ./sim <path of datafile>\n\n";
    return 0;
  }
#endif

  struct koordinatesBuffer buffer, file_buffer;
  buffer.x = (double*)malloc(sizeof(double) * buf);
  buffer.y = (double*)malloc(sizeof(double) * buf);
  file_buffer.x = (double*)malloc(sizeof(double) * buf);
  file_buffer.y = (double*)malloc(sizeof(double) * buf);
  unsigned long int i = 0;
  bool status = true;
  ofstream myfile;
  
#ifndef LIVE
  double runtime = omp_get_wtime();
  unsigned long int k = 0;
  
  myfile.open (argv[1]);
  if(!myfile.is_open()){
    cerr << "Error: open the file!\n";
    return 1;
  }
  
  welcome();
  cout << "Buffersize: 2*" << 2*sizeof(double) * buf / 8000 << " KB\n";
  cout << "Simulation runs.\n";
#endif

  begin();
  
  for(i=0; i< buf; i++){
    if (!simulation(buffer.x[i] ,buffer.y[i]))
      break;
  }
  #ifndef LIVE
  k = i;
  #endif
  if (i < buf)
    status = false;
  do{
    if (i == buf) {
      #pragma omp parallel
      {
        #pragma omp for
        for (i=0; i < buf; i++){
          file_buffer.x[i] = buffer.x[i];
          file_buffer.y[i] = buffer.y[i];
        }
        #pragma omp barrier
        #pragma omp single
        {
          writeData(myfile, file_buffer);
        }
        #pragma omp single
        {
          i = 0;
          for(i=0; i< buf; i++){
            status = simulation(buffer.x[i] ,buffer.y[i]);
            if (!status)
              break;
          }
          #ifndef LIVE
          k +=i;
          #endif
        }
      }
    }
  }while (status);
    
  writeData(myfile,buffer, i);
#ifndef LIVE
  myfile.close();
  runtime = omp_get_wtime() - runtime;
  cout << "\nCalculation loops: " << k << " in " << runtime << " sec\n";
  cout << "Done! You can see the data in " << argv[1] << "\n\n";
#endif
  return 0;
}
