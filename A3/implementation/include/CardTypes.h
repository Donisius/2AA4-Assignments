/**
 * \file CardTypes.h
 * \author Donisius Wigie MacID: wigied
 * \brief Provides the enumerated types and structure for representing a card.
 * \date 2019-03-21
 */
#ifndef A3_CARD_TYPES_H_
#define A3_CARD_TYPES_H_

/**
 * \brief Describes the rank of a card.
 */
typedef unsigned short int RankT;

/**
 * \brief RankT for an Ace.
 */
#define ACE    1

/**
 * \brief RankT for an Jack.
 */
#define JACK   11

/**
 * \brief RankT for a Queen.
 */
#define QUEEN  12

/**
 * \brief RankT for a King.
 */
#define KING   13

/**
 * \brief Enumerated type representing the four suits of a card: Heart, Diamond, Club and Spade.
*/
enum SuitT {Heart = 0, Diamond = 1, Club = 2, Spade = 3};

/**
 * \brief Enumerated type representing the four Categories in the game board: Tableau, Foundation, Deck, Waste.
*/
enum CategoryT {Tableau, Foundation, Deck, Waste};

/**
 * \brief Strucure representing a card containing the enumerated rank and suit of the card.
*/
struct CardT{
  SuitT s;
  RankT r;
};

#endif
