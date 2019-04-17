/**
 * \file Grid2D.h
 * \brief An abstract data type (ADT) for representing a grid of cell types in John Conway's Game of Life.
 * \author Donisius Wigie MacID: wigied
 * \date 2019-04-06
*/
#ifndef GRID2D_H
#define GRID2D_H

#include "../include/CellType.h"
#include <vector>
#include <string>

/**
 *  \brief Class for representing a grid of cell types in John Conway's Game of Life.
 *  \details Implements a class for representing a grid of cell types in John Conway's Game of Life,
 *  as well as functions to evolve the grid into the next transitions based on the rules provided at
 *  https://bitstorm.org/gameoflife/
 */
class Grid2D{

private:
  std::vector<std::vector<CellT>> temporaryStorage;
  std::vector<std::vector<CellT>> grid;
  int countNeighbours(int row, int col);
  std::vector<std::string> split(std::string str);
  void findNextState(int i, int j);

public:

  /**
   *  \brief Construct a new grid for John Conway's Game of Life.
   *  \details Create a new instance of aJohn Conway's Game of Life grid by interpreting the given
   *  graphical representation of the grid into a grid containing cell types determining whther a cell
   *  at a given location is dead or alive.
   *  \throws invalid_argument There was a problem opening the file containing the initial graphical
   *  representation of the grid of cells.
   *  \param fileName The name of the file containing the graphical representation of the intiial state of the grid.
   */
  Grid2D(std::string fileName);

  /**
   *  \brief View each generation from the initial configuration of cells up to the nth generation
   *  writing to a text file after each iteration the graphical representation of the state of the grid.
   *  \details Takes in an integer input which determines how many generations are viewed and written
   *  to a text file.
   *  \param n The number of generations to be viewed graphically and written into a text file.
   *  \param fileName The name of the file that the method should write the file to.
   */
  void viewGenerations(int n, std::string fileName);

  /**
   *  \brief View the graphical represenation of the current state of the grid and write the represenation into
   *  a text file.
   *  \details Translates the grid of cell types and converts it into a graphical representation where
   *  "." represents a dead cell and "O" represents a cell that is alive.
   *  \param fileName The name of the file that the method should write the file to.
   */
  void viewGrid(std::string fileName);

  /**
   *  \brief Evolves the grid into the next generation by following the rules from
   *  https://bitstorm.org/gameoflife/.
   *  \details Determines which cells in the grid should be alive in the next generation and
   *  which cells should be dead based on the rules given in the above website.
   */
  void evolveGrid();

  /**
   *  \brief A getter function for the grid at the current state.
   *  \details Returns the grid of CellTypes, mostly used for testing purposes.
   *  \return Grid of CellTypes.
   */
  std::vector<std::vector<CellT>> getGrid();

};

#endif
