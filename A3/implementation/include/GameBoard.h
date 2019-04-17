/**
 * \file GameBoard.h
 * \brief An abstract data type (ADT) for representing the state of a game of Forty Thieves.
 * \author Donisius Wigie MacID: wigied
 * \date 2019-03-21
*/

#ifndef A3_GAME_BOARD_H_
#define A3_GAME_BOARD_H_

#include <vector>
#include "CardStack.h"

/**
 *  \brief Class for representing the gameboard of a game of Forty Thieves.
 *  \details Implements a class for representing the gameboard of a Forty thieves game,
 *  as well as functions for making and validating moves and checking whether or not the board is in
 *  a win state.
 */
class BoardT{
private:
  std::vector<CardStackT> T;
  std::vector<CardStackT> F;
  CardStackT D;
  CardStackT W;
  std::vector<CardStackT> tab_deck(std::vector<CardT>);
  std::vector<CardStackT> init_seq(int n);
  int cnt_cards_stack(CardStackT s, RankT rk, unsigned int st);
  int cnt_cards_seq(std::vector<CardStackT> S, RankT rk, unsigned int st);
  int cnt_cards(std::vector<CardStackT> T, std::vector<CardStackT> F, CardStackT D, CardStackT W, RankT rk, unsigned int st);
  bool tab_placeable(CardT c, CardT d);
  bool foundation_placeable(CardT c, CardT d);
  bool valid_tab_tab(int n0, int n1);
  bool valid_tab_foundation(int n0, int n1);
  bool is_valid_pos(CategoryT c, int n);
  bool valid_waste_tab(int n);
  bool valid_waste_foundation(int n);

public:

  /**
   *  \brief Construct a new Forty Thieves gameboard
   *  \details Create a new instance of a Forty Thieves gameboard by placing a given deck of
   *  Card types on the Tableau.
   *  \throws invalid_argument The given initial deck does not have 104 cards and if there doesn''t valid_mv_exists
   *  two of each type of card in the given deck.
   */
  BoardT(std::vector<CardT>);

  /**
   *  \brief Verifies a move from Tableau
   *  \details Checks to see if moving a card from Tableau to another cell type or another Tableau is valid
   *  \param c The type of cell for the "from" cell to move the card to.
   *  \param n0 The index of the cell of type cell from which to move a card.
   *  \param n1 The index of the cell of type cell to which to move the card.
   *  \throws out_of_range if n0 or n1 are not possible indices for the type cell to move to.
   */
  bool is_valid_tab_mv(CategoryT c, int n0, int n1);

  /**
   *  \brief Verifies a move from Waste
   *  \details Checks to see if moving a card from Waste to another cell type is valid
   *  \param c The type of cell for the "from" cell to move the card to.
   *  \param n The index of the cell of type cell from which to move a card to.
   *  \throws out_of_range if n is a possible index for the type cell to move to.
   */
  bool is_valid_waste_mv(CategoryT c, int n);

  /**
   *  \brief Verifies a move from Waste
   *  \details Checks to see if moving a card from Waste to another cell type is valid
   *  \param c The type of cell for the "from" cell to move the card to.
   *  \param n The index of the cell of type cell from which to move a card to.
   *  \throws out_of_range if n0 or n1 are not possible indices .
   */
  bool is_valid_deck_mv();

  /**
   *  \brief Checks to see if the game board is currently in the win state.
   *  \details Checks to see if the game board is currently in the win state. This would mean that all eight Foundation
   *  are stacked from Ace to King of each suit.
   *  \return true if the gameboard is currently in a winning state, false otherwise.
   */
  bool is_win_state();

  /**
   *  \brief Checks to see if there is a possible move that currently exists on the gameboard.
   *  \details Checks to see if there is a possible move that currently exists on the gameboard.
   *  It will check to see if there exists a valid deck, tab, or waste move.
   *  \return true if there exists a possible move on the gameboard , false otherwise.
   */
  bool valid_mv_exists();

  /**
   *  \brief Make a move from Tableau cell to another cell.
   *  \details Moves the card from the top of the Tableau cell at index n0 to another cell represented by c
   *  \param c The type of cell for the "from" cell to move the card to.
   *  \param n0 The identifier of the cell of type cell from which to move a card.
   *  \param n1 The identifier of the cell of type cell to which to move the card.
   *  \throws invalid_argument id is_valid_tab_mv returns false.
   */
  void tab_mv(CategoryT c, int n0, int n1);

  /**
   *  \brief Make a move from deck stack to waste stack.
   *  \details Moves the card from the top of the deck stack to the top of the waste stack
   *  \throws invalid_argument id is_valid_deck_mv returns false.
   */
  void deck_mv();

  /**
   *  \brief Make a move from waste stack to deck stack.
   *  \details Moves the card from the top of the waste stack to the top of the deck stack
   *  \throws invalid_argument id is_valid_waste_mv returns false.
   */
  void waste_mv(CategoryT c, int n);

  /**
   *  \brief Return the cards in the tableau cell in the given index.
   *  \details Returns the cards in the tableau cell on the gameboard in the given index.
   *  \param i The index of the Tableau cell to be returned.
   *  \return The iterable representation of the Tableau cell.
   *  \throws out_of_range if i is not a valid index (i.e greater than 9 or less than 0).
   */
  CardStackT get_tab(int i);

  /**
   *  \brief Return the cards in the foundation cell in the given index.
   *  \details Returns the cards in the foundation cell on the gameboard in the given index.
   *  \param i The index of the Foundation cell to be returned.
   *  \return The iterable representation of the Foundation cell.
   *  \throws out_of_range if i is not a valid index (i.e greater than 7 or less than 0).
   */
  CardStackT get_foundation(int i);

  /**
   *  \brief Return the cards in the Deck stack.
   *  \details Returns the cards in Deck stack as an iterable representation.
   *  \return The iterable representation of the deck.
   */
  CardStackT get_deck();

  /**
   *  \brief Return the cards in the Waste stack.
   *  \details Returns the cards in Waste stack as an iterable representation.
   *  \return The iterable representation of the Waste stack.
   */
  CardStackT get_waste();

  /**
   *  \brief View the current game board
   *  \details Prints out the current game board.
   */
  void viewBoard();
};

#endif
