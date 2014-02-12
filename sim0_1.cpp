/*
** Simulator
***************************************************************
** (c) Konrad Merkel
** 15. Januar 2013
**************************************************************/
#define VERSION "0.1.1"
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

/* simulation */

// Variables

bool simulation(double &x, double &y)
{
  // Your program
  
  
  
  // Define what is x and y in the diagram?
  x = 0; /*your VAR instead of 0*/
  y = 0;
  
  // While
  if (/*condition*/) {return true;}
  else {return false;}
}



/*################ Only 4 developer´s eyes! ################*/

/* system */

void welcome()
{
  cout << "\n\nWelcome to KM-Simulationen\n";
  cout << "\nDeveloper: Konrad Merkel\nSDK-Version: "<< VERSION << "\n\n\n";
}


void writeData(ofstream &myfile, double const x, double const y)
{
  myfile << x << "\t" << y << "\n"; 
}

int main(int argc, char* argv[])
{
  if (argc < 2){
    cout << "Usage: " << *argv[0] << " <path of datafile>\n";
    return 0;
  }
  double x = 0;
  double y = 0;
  
  welcome();
  
  ofstream myfile;
  myfile.open (argv[1]);
  if(myfile.is_open()){
  
    cout << "Simulation runs\n...\n";
    unsigned long int i = 0;
    while (simulation(x ,y))
    {
      i++;
      writeData(myfile, x, y);
    }
    myfile.close();
    cout << "calculation loops: " << k << "\n";
    cout << "Done! You can see the data in " << argv[1] << "\n\n";
  }else{
    cerr << "Error: open the File!\n";
    return 1;
  }
  
  return 0;
}
