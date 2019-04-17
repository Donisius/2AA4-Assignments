/**
 * \file Stack.h
 * \brief A template module for a stack.
 * \author Donisius Wigie MacID: wigied
 * \date 2019-03-21
*/

#ifndef A3_STACK_H_
#define A3_STACK_H_

#include <vector>

/**
 *  \brief Template class for a stack.
 *  \details Implements a stack template.
 */
template <class T>
class Stack{
private:
  std::vector<T> S;

public:

  /**
   *  \brief Construct a new stack.
   *  \details Create a new instance of a stack with some given elements.
   *  \param s The initial elements to push on to the stack.
   */
  Stack(std::vector<T> s);

  Stack();

  /**
   *  \brief Creates a new stack by pushing a given value to the top of the current stack.
   *  \details Create a new instance of stack containing the given value put on top of the current stack.
   *  \param e The new element of type T to place on top of the stack.
   *  \return A new instance of stack containing the given value put on top of the current stack.
   */
  Stack<T> push(T e);

  /**
   *  \brief Get the top of the current stack.
   *  \details Returns the topmost value on the current stack.
   *  \return The top value of the current stack.
   *  \throw out_of_range if the stack is empty when executing the top function.
   */
  T top();

  /**
   *  \brief Creates a new stack by popping the top off the current one.
   *  \details Create a new instance of stack containing one less value which was popped off the current stack.
   *  \return A new instance of stack containing one less value which was popped off the current stack.
   *  \throw out_of_range The size of the current stack is 0.
   */
  Stack<T> pop();

  /**
   *  \brief Get the number of elements of the stack.
   *  \details Returns the number of elements contained in the stack.
   *  \return The number of elements contained in the stack.
   */
  unsigned int size();

  /**
   *  \brief Get an iterable representation of the current stack.
   *  \details Returns a sequence of elements which represents the stack.
   *  \return The sequence representation of the current stack.
   */
  std::vector<T> toSeq();
};
#endif
