#include "GameBoard.h"

#include <vector>
#include <stdexcept>
#include <iostream>


BoardT::BoardT(std::vector<CardT> deck){
  if(deck.size() != 104){
    throw std::invalid_argument("invalid arguement");
  }
  //initiate the tableau
  for(int i = 0; i < 10; i++){
    std::vector<CardT> tabStack;
    for(int j = 0; j < 4; j++){
      tabStack.push_back(deck.back());
      deck.pop_back();
    }
    this->T.push_back(CardStackT(tabStack));
    tabStack.clear();
  }
  std::vector<CardT> waste;
  this->F = init_seq(8);
  this->D = CardStackT(deck);
  this->W = CardStackT(waste);

  // Checks to see if there is two of each card.
  for (RankT rk = ACE; rk <= KING; rk++) {
    for (unsigned int st = 0; st < 4; st++) {
      if(cnt_cards(this->T, this->F, this->D, this->W, rk, st) != 2){
        throw std::invalid_argument("invalid arguement");
      }
    }
  }
}

std::vector<CardStackT> BoardT::init_seq(int n){
  std::vector<CardStackT> seqCardStackT;
  for(int i = 0; i < n; i++){
    std::vector<CardT> d;
    seqCardStackT.push_back(CardStackT(d));
  }

  return seqCardStackT;
}


int BoardT::cnt_cards_stack(CardStackT s, RankT rk, unsigned int st){
  std::vector<CardT> c = s.toSeq();
  int counter = 0;
  for(unsigned int i = 0; i < c.size(); i++){
    if(c[i].r == rk && c[i].s == st){
      counter++;
    }
  }
  return counter;
}

int BoardT::cnt_cards_seq(std::vector<CardStackT> S, RankT rk, unsigned int st){
  int counter = 0;
  for(unsigned int i = 0; i < S.size(); i++){
    counter += cnt_cards_stack(S[i], rk, st);
  }
  return counter;
}

int BoardT::cnt_cards(std::vector<CardStackT> T, std::vector<CardStackT> F, CardStackT D, CardStackT W, RankT rk, unsigned int st){
  return cnt_cards_seq(T, rk, st) + cnt_cards_seq(F, rk, st) + cnt_cards_stack(D, rk, st) + cnt_cards_stack(W, rk, st);
}

bool BoardT::tab_placeable(CardT c, CardT d){
  if(c.s == d.s && c.r == d.r - 1){
    return true;
  }
  return false;
}

bool BoardT::foundation_placeable(CardT c, CardT d){
  if(c.s == d.s && c.r == d.r + 1){
    return true;
  }
  return false;
}

bool BoardT::valid_tab_tab(int n0, int n1){
  if(this->T[n0].size() > 0){
    if(this->T[n1].size() > 0){
      return tab_placeable(this->T[n0].top(), this->T[n1].top());
    }
    else if(this->T[n1].size() == 0){
      return true;
    }
  }
  return false;
}

bool BoardT::valid_tab_foundation(int n0, int n1){
  if(this->T[n0].size() > 0){
    if(this->F[n1].size() > 0){
      return foundation_placeable(this->T[n0].top(), this->F[n1].top());
    }
    else if(this->F[n1].size() == 0){
      return this->T[n0].top().r == ACE;
    }
  }
  return false;
}

bool BoardT::is_valid_tab_mv(CategoryT c, int n0, int n1){
  if(c == Tableau){
    if(is_valid_pos(Tableau, n0) != true || is_valid_pos(Tableau, n1) != true){
      throw std::out_of_range("out of range");
    }
    return valid_tab_tab(n0, n1);
  }
  else if(c == Foundation){
    if(is_valid_pos(Tableau, n0) != true || is_valid_pos(Foundation, n1) != true){
      throw std::out_of_range("out of range");
    }
    return valid_tab_foundation(n0, n1);
  }
  return false;
}

bool BoardT::is_valid_pos(CategoryT c, int n){
  if(c == Tableau){
    if(n < 0 || n > 9){
      return false;
    }
  }
  if(c == Foundation){
    if(n < 0 || n > 7){
      return false;
    }
  }
  return true;
}

bool BoardT::valid_waste_tab(int n){
  if(this->T[n].size() > 0 && this->W.size() > 0){
    return tab_placeable(this->W.top(), this->T[n].top());
  }
  return true;
}

bool BoardT::valid_waste_foundation(int n){
  if(this->F[n].size() > 0 && this->W.size() > 0){
    return foundation_placeable(this->W.top(), this->F[n].top());
  }
  if(this->F[n].size() == 0 && this->W.size() > 0){
    return this->W.top().r == ACE;
  }
  return false;
}

bool BoardT::is_valid_waste_mv(CategoryT c, int n){
  if(this->W.size() == 0){
    throw std::invalid_argument("invalid arguement");
  }
  if(c == Tableau){
    if(is_valid_pos(Tableau, n) != true){
      throw std::out_of_range("out of range");
    }
    return valid_waste_tab(n);
  }
  else if(c == Foundation){
    if(is_valid_pos(Foundation, n) != true){
      throw std::out_of_range("out of range");
    }
    return valid_waste_foundation(n);
  }
  return false;
}

bool BoardT::is_valid_deck_mv(){
  return this->D.size();
}

bool BoardT::is_win_state(){
  for(int i = 0; i < 8; i++){
    return this->F[i].size() > 0 && this->F[i].top().r == KING;
  }
  return false;
}

bool BoardT::valid_mv_exists(){
  bool validTabMove = false;
  bool validWasteMove = false;

  CategoryT c[2] = {Tableau, Foundation};
  for(int i = 0; i < 2; i++){
    for(int n0 = 0; is_valid_pos(c[i], n0); n0++){
      for(int n1 = 0; is_valid_pos(c[i], n1); n1++){
        if(is_valid_tab_mv(c[i], n0, n1) == true){
          validTabMove = true;
          goto skip_loop;
        }
      }
    }
  }

  for(int i = 0; i < 2; i++){
    for(int n = 0; is_valid_pos(c[i], n); n++){
      if(is_valid_waste_mv(c[i], n) == true){
        validWasteMove = true;
        goto skip_loop;
      }
    }
  }

  return validTabMove || validWasteMove || is_valid_deck_mv();

  skip_loop:
  return true;
}

void BoardT::tab_mv(CategoryT c, int n0, int n1){
  if(is_valid_tab_mv(c, n0, n1) != true){
    throw std::invalid_argument("invalid argument");
  }
  if(c == Tableau){
    this->T[n1] = this->T[n1].push(this->T[n0].top());
    this->T[n0] = this->T[n0].pop();
  }
  else if(c == Foundation){
    this->F[n1] = this->F[n1].push(this->T[n0].top());
    this->T[n0] = this->T[n0].pop();
  }
}

void BoardT::deck_mv(){
  if(is_valid_deck_mv() != true){
    throw std::invalid_argument("invalid argument");
  }
  this->W = this->W.push(this->D.top());
  this->D = this->D.pop();
}

void BoardT::waste_mv(CategoryT c, int n){
  if(is_valid_waste_mv(c, n) != true){
    throw std::invalid_argument("invalid_argument");
  }
  if(c == Tableau){
    this->T[n] = this->T[n].push(this->W.top());
    this->W = this->W.pop();
  }
  else if(c == Foundation){
    this->F[n] = this->F[n].push(this->W.top());
    this->W = this->W.pop();
  }
}

CardStackT BoardT::get_tab(int i){
  if(is_valid_pos(Tableau, i) != true){
    throw std::out_of_range("out of range");
  }
  return this->T[i];
}

CardStackT BoardT::get_foundation(int i){
  if(is_valid_pos(Foundation, i) != true){
    throw std::out_of_range("out_of_range");
  }
  return this->F[i];
}

CardStackT BoardT::get_deck(){
  return this->D;
}

CardStackT BoardT::get_waste(){
  return this->W;
}

void BoardT::viewBoard(){
  std::cout << "____________________TABLEAU___________________" << "\n";
  for(int i = 0; i < 10; i++){
    std::cout << "           __________T" << i << "__________\n";
    std::vector<CardT> tabStack = T[i].toSeq();
    for(unsigned int j = 0; j < tabStack.size(); j++){
      CardT c = tabStack[j];
      std::cout << "                  " << c.r << "  ";
      if(c.s == Heart){
        std::cout << "HEART";
      }
      else if(c.s == Diamond){
        std::cout << "DIAMOND";
      }
      else if(c.s == Club){
        std::cout << "CLUB";
      }
      else if (c.s == Spade){
        std::cout << "SPADE";
      }
      std::cout << "\n";
    }
  }

  std::cout << "____________________FOUNDATION____________________" << "\n";
  for(int i = 0; i < 7; i++){
    std::cout << "           __________F" << i << "__________\n";
    int size = this->F[i].size();
    for(int j = 0; j < size; j++){
      CardT c = this->F[i].toSeq()[j];
      std::cout << "                  " << c.r << "  ";
      if(c.s == Heart){
        std::cout << "HEART";
      }
      else if(c.s == Diamond){
        std::cout << "DIAMOND";
      }
      else if(c.s == Club){
        std::cout << "CLUB";
      }
      else if (c.s == Spade){
        std::cout << "SPADE";
      }
      std::cout << "\n";
    }
  }

  std::cout << "____________________DECK____________________\n";
  std::vector<CardT> deck = this->D.toSeq();
  for(unsigned int i = 0; i < deck.size(); i++){
    std::cout <<"                  " << deck[i].r << "  ";
    if(deck[i].s == Heart){
      std::cout << "HEART";
    }
    else if(deck[i].s == Diamond){
      std::cout << "DIAMOND";
    }
    else if(deck[i].s == Club){
      std::cout << "CLUB";
    }
    else if (deck[i].s == Spade){
      std::cout << "SPADE";
    }
    std::cout << "\n";
  }

  std::cout << "____________________WASTE____________________\n";
  std::vector<CardT> waste = this->W.toSeq();
  for(unsigned int i = 0; i < waste.size(); i++){
    std::cout <<"                  " << waste[i].r << "  ";
    if(waste[i].s == Heart){
      std::cout << "HEART";
    }
    else if(waste[i].s == Diamond){
      std::cout << "DIAMOND";
    }
    else if(waste[i].s == Club){
      std::cout << "CLUB";
    }
    else if (waste[i].s == Spade){
      std::cout << "SPADE";
    }
    std::cout << "\n";
  }
}
