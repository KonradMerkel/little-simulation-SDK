/*
** Simulator
***************************************************************
** (c) Konrad Merkel
** SDK-Version: 0.2.2
** 12. Feb 2014
**************************************************************/
unsigned long int const buf = 131072 ;
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

/* simulation */

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
  if (t<=15) {return true;}
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
  
  welcome();
  //begin();
  
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
    cout << "calculation loops: " << k << "\n";
    cout << "Done! You can see the data in " << argv[1] << "\n\n";
    
  }else{
    cerr << "Error: open the file!\n";
    return 1;
  }
  
  return 0;
}
