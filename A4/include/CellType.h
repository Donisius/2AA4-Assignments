/**
 * \file CellType.h
 * \brief Provides the enumerated types and structure for representing a cell.
 * \author Donisius Wigie MacID: wigied
 * \date 2019-04-06
*/
#ifndef CELLTYPE_H
#define CELLTYPE_H

/**
 * \brief Enumerated type representing the state of a cell: Dead, Alive.
 */
enum StateT {Dead = 0, Alive = 1};

/**
 * \brief Structure representing a cell containing the enumerated state.
*/
struct CellT{
  StateT s;
};

#endif
