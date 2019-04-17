#include "../include/Grid2D.h"
#include "../include/CellType.h"

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>
#include <unistd.h>
#include <stdexcept>

Grid2D::Grid2D(std::string fileName){

  std::vector<std::vector<std::string>> gridRep;
  std::ifstream file(fileName);
  std::string str;
  CellT cellDead = {static_cast<StateT>(Dead)};
  CellT cellAlive = {static_cast<StateT>(Alive)};

  if(file.is_open()){
    while(getline(file, str)){
      std::vector<std::string> row = split(str);
      gridRep.push_back(row);
    }
    file.close();
  }
  else{
    throw std::invalid_argument("Could not open file");
  }

  for(unsigned int i = 0; i < gridRep.size(); i++){
    std::vector<CellT> initRow(gridRep[0].size());
    this->grid.push_back(initRow);
    this->temporaryStorage.push_back(initRow);
  }

  for(unsigned int i = 0; i < gridRep[0].size(); i++){
    for(unsigned int j = 0; j < gridRep.size(); j++){
      if(gridRep[i][j] == "O"){
        this->grid[i][j] = cellAlive;
      }
      else if (gridRep[i][j] == "."){
        this->grid[i][j] = cellDead;
      }
    }
  }
}

void Grid2D::viewGrid(std::string fileName){
  std::ofstream file(fileName);
  if(file.is_open()){
    for(unsigned int i = 0; i < this->grid.size(); i++){
      std::ostringstream os;
      for(unsigned int j = 0; j < this->grid[i].size(); j++){
        if(this->grid[i][j].s == Alive){
          std::cout << "O  ";
          os << "O  ";
        }
        if(this->grid[i][j].s == Dead){
          std::cout << ".  ";
          os << ".  ";
        }
      }
      std::cout << "\n";
      os << "\n";
      std::string s = os.str();
      file << s;
    }
    file.close();
  }
  else{
    throw std::invalid_argument("Could not open file");
  }
}

int Grid2D::countNeighbours(int row, int col){

  int sum = 0;

  for(int i = - 1; i < 2; i++){
    for(int j = - 1; j < 2; j++){
      if(row + i > - 1 && row + i < this->grid.size() && col + j > -1 && col + j < this->grid[0].size()){
        sum += this->grid[row + i][col + j].s;
      }
    }
  }
  sum -= this->grid[row][col].s;
  return sum;
}

void Grid2D::evolveGrid(){

  for(unsigned int i = 0; i < this->grid.size(); i++){
    for(unsigned int j = 0; j < this->grid[i].size(); j++){
      findNextState(i, j);
    }
  }
  this->grid = this->temporaryStorage;
}

void Grid2D::findNextState(int i, int j){

  CellT cellDead = {static_cast<StateT>(Dead)};
  CellT cellAlive = {static_cast<StateT>(Alive)};

  if(this->grid[i][j].s == Dead && countNeighbours(i, j) == 3){
    this->temporaryStorage[i][j] = cellAlive;
  }

  if(this->grid[i][j].s == Alive && countNeighbours(i, j) >= 2 && countNeighbours(i, j) <= 3){
    this->temporaryStorage[i][j] = cellAlive;
  }

  if(this->grid[i][j].s == Alive && countNeighbours(i, j) > 3){
    this->temporaryStorage[i][j] = cellDead;
  }

  if(this->grid[i][j].s == Alive && countNeighbours(i, j) < 2){
    this->temporaryStorage[i][j] = cellDead;
  }

  if(this->grid[i][j].s == Dead && countNeighbours(i, j) != 3){
    this->temporaryStorage[i][j] = cellDead;
  }
}

void Grid2D::viewGenerations(int n, std::string fileName){
  for(int i = 0; i < n; i++){
    std::cout << "Generation: " << i << "\n";
    viewGrid(fileName);
    evolveGrid();
    std::cout << "\n";
    sleep(1);
  }
}

std::vector<std::vector<CellT>> Grid2D::getGrid(){
  return this->grid;
}

std::vector<std::string> Grid2D::split(std::string str){

  std::vector<std::string> stringStore;
  std::string tempString;
  std::stringstream inputString(str);
  while(inputString >> tempString){
    stringStore.push_back(tempString);
  }
  return stringStore;
}
