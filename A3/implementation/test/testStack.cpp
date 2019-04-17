#include "catch.h"
#include "Stack.h"
#include "CardStack.h"
#include "CardTypes.h"

#include <vector>
#include <stdexcept>

TEST_CASE("stack normal test cases"){

  std::vector<CardT> d;
  for (RankT rank = ACE; rank <= KING; rank++) {
    for (unsigned int suit = 0; suit < 4; suit++) {
      CardT n = { static_cast<SuitT>(suit), rank };
      d.push_back(n);
      d.push_back(n);
    }
  }

  CardStackT testCardStack = CardStackT(d);

  SECTION("push outputs a new stack containing the new pushed element"){
    CardT n = { static_cast<SuitT>(0), ACE };
    CardStackT newCardStack = testCardStack.push(n);
    REQUIRE(newCardStack.top().r == 1);
    REQUIRE(newCardStack.top().s == 0);
  }

  SECTION("pop outputs a new stack containing all elements except the top of the previous stack"){
    REQUIRE(testCardStack.top().r == KING);
    REQUIRE(testCardStack.top().s == 3);

    CardStackT newCardStack = testCardStack.pop();

    REQUIRE(newCardStack.top().r == KING);
    REQUIRE(newCardStack.top().s == 3);
  }

  SECTION("size will give the number of items in the stack"){
    REQUIRE(testCardStack.size() == 104);
  }

  SECTION("toSeq outputs a sequence of the stack data structure"){
    std::vector<CardT> testSeq = testCardStack.toSeq();
    for(int i = 0; i < 104; i++){
      REQUIRE(testSeq[i].r == d[i].r);
      REQUIRE(testSeq[i].s == d[i].s);
    }
  }
}

TEST_CASE("stack exception test cases"){
  std::vector<CardT> d;
  CardStackT testCardStack = CardStackT(d);

  SECTION("pop throws out_of_range exception if stack is empty"){
    bool exceptionTest = false;
    try{
      testCardStack.pop();
    }catch(std::out_of_range){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }

  SECTION("top throws out_of_range exception if stack is empty"){
    bool exceptionTest = false;
    try{
      testCardStack.top();
    }catch(std::out_of_range){
      exceptionTest = true;
    }
    REQUIRE(exceptionTest);
  }
}
