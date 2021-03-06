/*
** Simulator
***************************************************************
** (c) Konrad Merkel
** SDK-Version: 0.2.1
** 11. Februar 2014
**************************************************************/
unsigned long int const buf = 131072 ;
#include <iostream>
#include <fstream>
#include <math.h>
#include <omp.h>
using namespace std;

/* simulation */
#define PI 3.1415
struct vektor{
  double x;
  double y;
};

// const
double const c_a = 0.55;
double const c_w = 0.45;
double const roh = 1.29; // kg/m³
double const A = 0.1; // m²
double const v_o = 2.5; // m/s
double const m = 0.015; // kg
double const dt = 0.001; // s
double const alpha = PI / 18; // rad

// Variables
vektor pos; // m
vektor F_w; // N
vektor F_a; // N
vektor F_g; // N
vektor F_res; // N
vektor v; // m/s

void begin()
{
  pos.x = 0;
  pos.y = 2;
  F_g.x = 0;
  F_g.y = (-9.81) * m;
  
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
}

bool simulation(double &x, double &y)
{ 
  // lift force
  F_a.y = (v.x * c_a * A * roh * (v.x * v.x + v.y * v.y) * 0.5) / sqrt(v.x * v.x + v.y * v.y);
  F_a.x = (-v.y * F_a.y) / v.x;
  
  // aerodynamic resistance
  F_w.y = (v.y * c_w * A * roh * (v.x * v.x + v.y * v.y) * 0.5) / sqrt(v.x * v.x + v.y * v.y);
  F_w.x = (v.x * F_w.y) / v.y;
  
  // resultant force
  F_res.x = (F_a.x - F_w.x) + F_g.x;
  F_res.y = (F_a.y - F_w.y) + F_g.y;
  
  pos.x =  (0.5 * F_res.x/m * dt * dt) + v.x * dt + pos.x;
  pos.y =  (0.5 * F_res.y/m * dt * dt) + v.y * dt + pos.y;

  v.x = (F_res.x/m * dt) + v.x;
  v.y = (F_res.y/m * dt) + v.y;

  x = pos.x;
  y = pos.y;
   
  // While
  if (pos.y > 0) {return true;}
  else {return false;}
}



/*################ Only 4 developer´s eyes! ################*/

/* system */

struct koordinatesBuffer{
  double x[buf ];
  double y[buf ];
};

void welcome()
{
  cout << "\n\nWelcome to KM-Simulations\n";
  cout << "\nDeveloper: Konrad Merkel\nSDK-Version: 0.2.2\n\n\n";
}


void writeData(ofstream &myfile, struct koordinatesBuffer &buffer, unsigned long int buf_size = buf -1)
{
  for (int k=0 ; k<buf_size; k++)
    myfile << buffer.x[k] << "\t" << buffer.y[k] << "\n"; 
}

int main(int argc, char* argv[])
{
  if (argc < 2){
    cout << "Usage: " << *argv[0] << " <path of datafile>\n";
    return 0;
  }
  double runtime = omp_get_wtime();
  welcome();
  begin();
  
  ofstream myfile;
  myfile.open (argv[1]);
  if(myfile.is_open()){
  
    cout << "Simulation runs.\n";
    unsigned long int i = 0;
    unsigned long int k = 0;
    struct koordinatesBuffer buffer;
    while (simulation(buffer.x[i] ,buffer.y[i]))
    {
      k++;
      i++;
      if (i == buf -1) {
        writeData(myfile, buffer);
        i = 0;
      }
    }
    writeData(myfile,buffer, i);
    myfile.close();
    runtime = omp_get_wtime() - runtime;
    cout << "Calculation loops: " << k << " in " << runtime << " sec\n";
    cout << "Done! You can see the data in " << argv[1] << "\n\n";
    
  }else{
    cerr << "Error: open the file!\n";
    return 1;
  }
  
  return 0;
}
