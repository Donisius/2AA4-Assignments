#define CATCH_CONFIG_MAIN
#include "../catch/catch.h"
#include "../include/Grid2D.h"
#include "../include/CellType.h"

#include <vector>

//This is just a helper function to help read the file containing the states of the grid.
//This is actually the same helper function in Grid2D
std::vector<std::string> split(std::string str){

  std::vector<std::string> wordVector;
  std::stringstream ss(str);
  std::string temp;
  while(ss >> temp){
    wordVector.push_back(temp);
  }
  return wordVector;
}

TEST_CASE("Regular test cases for Grid2D"){

  Grid2D testCase("initialStateTest.txt");

  SECTION("Test cases based on expected patterns from https://bitstorm.org/gameoflife/"){

    testCase.evolveGrid();

    std::vector<std::vector<CellT>> testGrid = testCase.getGrid();
    REQUIRE(testGrid[2][1].s == Alive);
    REQUIRE(testGrid[3][2].s == Alive);
    REQUIRE(testGrid[4][2].s == Alive);
    REQUIRE(testGrid[2][3].s == Alive);
    REQUIRE(testGrid[3][3].s == Alive);
    REQUIRE(testGrid[0][0].s == Dead);

    testCase.evolveGrid();
    testGrid = testCase.getGrid();
    REQUIRE(testGrid[3][1].s == Alive);
    REQUIRE(testGrid[4][2].s == Alive);
    REQUIRE(testGrid[2][3].s == Alive);
    REQUIRE(testGrid[3][3].s == Alive);
    REQUIRE(testGrid[4][3].s == Alive);
    REQUIRE(testGrid[7][10].s == Dead);

    testCase.evolveGrid();
    testGrid = testCase.getGrid();
    REQUIRE(testGrid[2][2].s == Alive);
    REQUIRE(testGrid[4][2].s == Alive);
    REQUIRE(testGrid[3][3].s == Alive);
    REQUIRE(testGrid[4][3].s == Alive);
    REQUIRE(testGrid[3][4].s == Alive);
    REQUIRE(testGrid[3][10].s == Dead);

    testCase.evolveGrid();
    testGrid = testCase.getGrid();
    REQUIRE(testGrid[4][2].s == Alive);
    REQUIRE(testGrid[2][3].s == Alive);
    REQUIRE(testGrid[4][3].s == Alive);
    REQUIRE(testGrid[4][4].s == Alive);
    REQUIRE(testGrid[3][4].s == Alive);
    REQUIRE(testGrid[11][11].s == Dead);

    testCase.evolveGrid();
    testGrid = testCase.getGrid();
    REQUIRE(testGrid[3][2].s == Alive);
    REQUIRE(testGrid[4][3].s == Alive);
    REQUIRE(testGrid[5][3].s == Alive);
    REQUIRE(testGrid[3][4].s == Alive);
    REQUIRE(testGrid[4][4].s == Alive);
    REQUIRE(testGrid[20][20].s == Dead);
  }

  SECTION("Test cases to make sure viewGrid will write the correct graphical representation of the grid into the nextState file"){

    testCase.viewGrid("nextState.txt");

    std::vector<std::vector<std::string>> gridRep;
    std::ifstream file("nextState.txt");
    std::string str;

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

    std::vector<std::vector<std::string>> gridRepTest;
    std::ifstream fileTest("nextStateTest.txt");
    std::string strTest;

    if(fileTest.is_open()){
      while(getline(fileTest, strTest)){
        std::vector<std::string> row = split(strTest);
        gridRepTest.push_back(row);
      }
      fileTest.close();
    }
    else{
      throw std::invalid_argument("Could not open file");
    }

    //This will cause a lot of assertions but it is necessary to test to make sure viewGrid write the correct
    //output to the file
    for(int i = 0; i < gridRep.size(); i++){
      for(int j = 0; j < gridRep[0].size(); j++){
        REQUIRE(gridRep[i][j] == gridRepTest[i][j]);
      }
    }
  }
}

TEST_CASE("Test cases for exceptions"){

  SECTION("Constructor should throw an invalid_argument exception there is a problem opening the file"){
    bool exceptionTest = false;
    try{
      Grid2D testException("This_Should_Fail.txt");
    }catch(std::invalid_argument){
      exceptionTest = true;
    }

    REQUIRE(exceptionTest);
  }

  SECTION("Constructor should throw an invalid_argument exception if nothing is provided as input"){
    bool exceptionTest = false;
    try{
      Grid2D testException("");
    }catch(std::invalid_argument){
      exceptionTest = true;
    }

    REQUIRE(exceptionTest);
  }

}
