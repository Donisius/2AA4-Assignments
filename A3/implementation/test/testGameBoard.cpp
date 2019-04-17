#include <vector>
#include <stdexcept>

#include "catch.h"
#include "CardStack.h"
#include "CardTypes.h"
#include "GameBoard.h"

TEST_CASE("GameBoard regular test cases"){

  std::vector<CardT> d;
  for (RankT rank = ACE; rank <= KING; rank++) {
    for (unsigned int suit = 0; suit < 4; suit++) {
      CardT n = { static_cast<SuitT>(suit), rank };
      d.push_back(n);
      d.push_back(n);
    }
  }
  BoardT board(d);

  SECTION("is_valid_tab_mv with category as Waste and Deck should return false"){
    REQUIRE(board.is_valid_tab_mv(Waste, 0, 0) == false);
    REQUIRE(board.is_valid_tab_mv(Deck, 0, 0) == false);
  }

  SECTION("is_valid_tab_mv with category as Tableau should be false if size > 0 but suit is not the same"){
    REQUIRE(board.is_valid_tab_mv(Tableau, 0, 1) == false);
  }

  SECTION("is_valid_tab_mv with category as Tableau should be false if size > 0 but rank is not one less"){
    REQUIRE(board.is_valid_tab_mv(Tableau, 1, 2) == false);
  }

  SECTION("is_valid_tab_mv with category as Tableau should be false if size > 0 but rank is not one less"){
    REQUIRE(board.is_valid_tab_mv(Tableau, 1, 2) == false);
  }

  SECTION("is_valid_tab_mv with category as Tableau should be true if size > 0 and rank is one less"){
    REQUIRE(board.is_valid_tab_mv(Tableau, 4 ,2) == true);
  }

  SECTION("is_valid_tab_mv with category as Foundation should be false if size > 0 and rank of top of tableau is not ACE"){
    board.deck_mv();
    REQUIRE(board.is_valid_tab_mv(Foundation, 3 , 0) == false);
  }

  SECTION("is_valid_waste_mv with category as Foundation should be false if size = 0"){
    board.deck_mv();
    REQUIRE(board.is_valid_waste_mv(Foundation, 0) == false);
  }

  SECTION("is_valid_waste_mv with category as Tableau should return false if top of waste is not one less than top of tab"){
    board.deck_mv();
    REQUIRE(board.is_valid_waste_mv(Tableau, 0) == false);
  }

  SECTION("is_valid_waste_mv should return true if size of deck is greater than 0"){
    REQUIRE(board.is_valid_deck_mv() == true);
  }

  SECTION("tab_mv should move if conditions are met"){
    board.tab_mv(Tableau, 4, 2);
    REQUIRE(board.get_tab(2).toSeq()[4].r == 11);
    REQUIRE(board.get_tab(2).toSeq()[4].s == Club);
  }

  SECTION("deck_mv should move a card to waste if deck size > 0"){
    board.deck_mv();
    REQUIRE(board.get_waste().toSeq()[0].s == Spade);
    REQUIRE(board.get_waste().toSeq()[0].r == 8);
  }

  SECTION("get_tab should return the cardStackT at index i"){
    REQUIRE(board.get_tab(0).top().s == Club);
    REQUIRE(board.get_tab(1).top().s == Heart);
    REQUIRE(board.get_tab(2).top().s == Club);
    REQUIRE(board.get_tab(3).top().s == Heart);
    REQUIRE(board.get_tab(4).top().s == Club);
    REQUIRE(board.get_tab(5).top().s == Heart);
    REQUIRE(board.get_tab(6).top().s == Club);
    REQUIRE(board.get_tab(7).top().s == Heart);
    REQUIRE(board.get_tab(8).top().s == Club);
    REQUIRE(board.get_tab(9).top().s == Heart);
  }

  SECTION("get_deck should return the CardStackT representing deck"){
    REQUIRE(board.get_deck().top().s == Spade);
    REQUIRE(board.get_deck().top().r == 8);
  }

  SECTION("valid_mv_exists should return true if deck size is > 0"){
    REQUIRE(board.valid_mv_exists() == true);
  }

  SECTION("is_win_state should return false is foundation is not full"){
    REQUIRE(board.is_win_state() == false);
  }
}

TEST_CASE("GameBoard Exception test cases"){

  SECTION("Empty deck should cause constructor to throw invalid arguements exception"){
    std::vector<CardT> d;
    bool exceptionTest = false;
    try{
      BoardT board(d);
    }catch(std::invalid_argument){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }

  SECTION("Deck that does not have 2 of each card should throw invalid_arguement exception for contructor"){
    std::vector<CardT> d;
    for (RankT rank = ACE; rank <= 12; rank++) {
      for (unsigned int suit = 0; suit < 4; suit++) {
        CardT n = { static_cast<SuitT>(suit), rank };
        d.push_back(n);
        d.push_back(n);
      }
    }
    bool exceptionTest = false;
    try{
      BoardT board(d);
    }catch(std::invalid_argument){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }

  std::vector<CardT> d;
  for (RankT rank = ACE; rank <= KING; rank++) {
    for (unsigned int suit = 0; suit < 4; suit++) {
      CardT n = { static_cast<SuitT>(suit), rank };
      d.push_back(n);
      d.push_back(n);
    }
  }
  BoardT board(d);

  SECTION("is_valid_tab_mv throws exception when n is out of range for Tableau"){
    bool exceptionTest = false;
    try{
      board.is_valid_tab_mv(Tableau, 11, 11);
    }catch(std::out_of_range){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }

  SECTION("is_valid_tab_mv throws exception when n is out of range for Foundation"){
    bool exceptionTest = false;
    try{
      board.is_valid_tab_mv(Foundation, 8, 8);
    }catch(std::out_of_range){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }

  SECTION("is_valid_waste_mv throws exception when n is out of range for Tableau"){
    board.deck_mv();
    bool exceptionTest = false;
    try{
      board.is_valid_waste_mv(Tableau, 11);
    }catch(std::out_of_range){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }

  SECTION("is_valid_waste_mv throws exception when waste is empty"){
    bool exceptionTest = false;
    try{
      board.is_valid_waste_mv(Tableau, 4);
    }catch(std::invalid_argument){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }

  SECTION("tab_mv should throw an exception when is_valid_tab_mv is false"){
    bool exceptionTest = false;
    try{
      board.tab_mv(Foundation, 1, 1);
    }catch(std::invalid_argument){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
    exceptionTest = false;
    try{
      board.tab_mv(Tableau, 1, 2);
    }catch(std::invalid_argument){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }

  SECTION("waste_mv should throw an exception if is_valid_waste_mv is false"){
    bool exceptionTest = false;
    board.deck_mv();
    try{
      board.waste_mv(Foundation, 2);
    }catch(std::invalid_argument){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }

  SECTION("deck_mv should throw an exception if deck size is < 1"){
    bool exceptionTest = false;
    for(int i = 0; i < 64; i++){
      board.deck_mv();
    }
    try{
      board.deck_mv();
    }catch(std::invalid_argument){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }

  SECTION("get_tab should throw invalid argument exception if is_valid_pos is false"){
    bool exceptionTest = false;
    try{
      board.get_tab(11);
    }catch(std::out_of_range){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }

  SECTION("get_foundation should throw invalid arguement exception if is_valid_pos is false"){
    bool exceptionTest = false;
    try{
      board.get_foundation(8);
    }catch(std::out_of_range){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }
}

TEST_CASE("sample game"){
  std::vector<CardT> d;
  for (RankT rank = ACE; rank <= KING; rank++) {
    for (unsigned int suit = 0; suit < 4; suit++) {
      CardT n = { static_cast<SuitT>(suit), rank };
      d.push_back(n);
      d.push_back(n);
    }
  }

  BoardT board2(d);

  board2.deck_mv();

  SECTION("deck_mv"){
    board2.viewBoard();
    REQUIRE(board2.get_waste().toSeq()[0].r == 8);
    REQUIRE(board2.get_waste().toSeq()[0].s == Spade);
  }

  board2.deck_mv();
  board2.deck_mv();

  SECTION("is_valid_waste_mv"){
    REQUIRE(board2.is_valid_waste_mv(Tableau, 8) == true);
  }

  SECTION("is_valid_tab_mv"){
    REQUIRE(board2.is_valid_tab_mv(Tableau, 8, 6) == true);
  }

  board2.tab_mv(Tableau, 8, 6);

  SECTION("tab_mv"){
    REQUIRE(board2.get_tab(6).top().r == 9);
    REQUIRE(board2.get_tab(6).top().s == Club);
  }

  board2.waste_mv(Tableau, 8);
  SECTION("waste_mv"){
    REQUIRE(board2.get_tab(8).top().r == 8);
    REQUIRE(board2.get_tab(8).top().s == Club);
  }

  SECTION("is_valid_waste_mv"){
    REQUIRE(board2.is_valid_waste_mv(Tableau, 9) == false);
  }

  board2.deck_mv();

  SECTION("is_valid_waste_mv"){
    REQUIRE(board2.is_valid_waste_mv(Tableau, 8) == false);
  }
  SECTION("waste_mv"){
    bool exceptionTest = false;
    try{
      board2.waste_mv(Tableau, 8);
    }catch(std::invalid_argument){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }

  SECTION("is_valid_tab_mv - FOUNDATION"){
    REQUIRE(board2.is_valid_tab_mv(Foundation, 1, 1) == false);
  }

  for(int i = 0; i < 60; i++){
    board2.deck_mv();
  }

  board2.waste_mv(Foundation, 0);

  SECTION("waste_mv - FOUNDATION"){
    REQUIRE(board2.get_foundation(0).top().r == ACE);
    REQUIRE(board2.get_foundation(0).top().s == Heart);
  }

  SECTION("valid_mv_exists - foundation move only possible move"){
    REQUIRE(board2.valid_mv_exists() == true);
  }

  SECTION("is_win_state - false"){
    REQUIRE(board2.is_win_state() == false);
  }
}
