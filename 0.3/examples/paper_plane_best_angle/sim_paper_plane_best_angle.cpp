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
#define PI 3.1415

struct vektor{
  double x;
  double y;
};

// const
double const c_a = 0.4;
double const c_w = 0.06;
double const roh = 1.29; // kg/m³
double const A = 0.2; // m²
double const v_o = 2.5; // m/s
double const m = 0.015; // kg
double const dt = 0.01; // s

// Variables
vektor pos; // m
vektor F_w; // N
vektor F_a; // N
vektor F_g; // N
vektor F_res; // N
vektor v; // m/s
double alpha = -PI + 0.01; // rad

void begin()
{
  F_g.x = 0;
  F_g.y = (-9.81) * m;
}

bool simulation(double &x, double &y)
{
  pos.x = 0;
  pos.y = 2;
  
  // velocity at the beginning
  if (alpha == PI){
    v.x = 0;
    v.y = v_o;
  }else if (alpha == -PI){
    v.x = 0;
    v.y = -v_o;
  }else if (alpha == 0){
    v.x = v_o;
    v.y = 0;
  }else{
    v.x = cos(alpha) * v_o;
    v.y = sin(alpha) * v_o;
  }
  
  do{
  // lift force
  F_a.y = (v.x * c_a * A * roh * (v.x * v.x + v.y * v.y) * 0.5) / sqrt(v.x * v.x + v.y * v.y);
  F_a.x = (-v.y * F_a.y) / v.x;
  
  // aerodynamic resistance
  F_w.y = (v.y * c_w * A * roh * (v.x * v.x + v.y * v.y) * 0.5) / sqrt(v.x * v.x + v.y * v.y);
  F_w.x = (v.x * F_w.y) / v.y;
  
  // result. force
  F_res.x = (F_a.x - F_w.x) + F_g.x;
  F_res.y = (F_a.y - F_w.y) + F_g.y;
  
  pos.x =  (0.5 * F_res.x/m * dt * dt) + v.x * dt + pos.x;
  pos.y =  (0.5 * F_res.y/m * dt * dt) + v.y * dt + pos.y;

  v.x = (F_res.x/m * dt) + v.x;
  v.y = (F_res.y/m * dt) + v.y;
  
  }while(pos.y > 0);
  
  // x and y axes in the diagram
  x = alpha * 180 / PI;
  y = pos.x;
  alpha = alpha + 0.01;
  
  // While
  if (alpha < (PI+ 0.01)) {return true;}
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
