/*
** Simulator
***************************************************************
** (c) Konrad Merkel
** SKD-Version: 0.2.2
** 27. Mai 2013
**************************************************************/
unsigned long int const buf = 131072 ;
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

/* simulation */

// const

// Variables

void begin()
{
  // Something that have to do first and only once.
}

bool simulation(double &x, double &y)
{
  // Your program
  
  // C++ Math-help (german): http://www.willemer.de/informatik/cpp/mathlib.htm
  
  
  // Define what is x and y in the diagram?
  x = 0; /*your VAR instead of 0*/
  y = 0;
  
  // While
  if (/*condition while the simulation runs*/) {return true;}
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
    cout << "calculation loops: " << k << "\n";
    cout << "Done! You can see the data in " << argv[1] << "\n\n";
    
  }else{
    cerr << "Error: open the file!\n";
    return 1;
  }
  
  return 0;
}
