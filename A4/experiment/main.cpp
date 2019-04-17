#include <iostream>
#include "../include/Grid2D.h"

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <sstream>
#include <string>
#include <fstream>
#include <unistd.h>

void static initGrid(int numRows, int numCols);

int main(){

  Grid2D a("initialState.txt");
  a.viewGenerations(40, "nextState.txt");


  return 0;
}

//Only used to create a graphical representation of the grid with dead cells.
//Use this for convenience before calling any other function and intialize the
//grid yourself.
void static initGrid(int numRows, int numCols){

  std::ofstream file("initialState.txt");
  if(file.is_open()){
    for(int i = 0; i < numRows; i++){
      std::ostringstream os;
      for(int j = 0; j < numCols; j++){
        os << ".  ";
      }
      os << "\n";
      std::string s = os.str();
      file << s;
    }
    file.close();
  }
  else{
    std::cout << "Unable to open file";
  }
}
