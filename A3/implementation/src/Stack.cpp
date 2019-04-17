// Implementation here
#include "Stack.h"
#include "CardTypes.h"

#include <vector>
#include <stdexcept>

template<class T>
Stack<T>::Stack(std::vector<T> s){
  this->S = s;
}

template<class T>
Stack<T>::Stack(){}

template <class T>
Stack<T> Stack<T>::push(T e){
  std::vector<T> new_(this->S);
  new_.push_back(e);
  return Stack<T>(new_);
}

template <class T>
Stack<T> Stack<T>::pop(){
  if(this->S.size() == 0){
    throw std::out_of_range("stack is out of range pop");
  }
  std::vector<T> new_(this->S);
  new_.pop_back();
  return Stack<T>(new_);
}

template <class T>
T Stack<T>::top(){
  if(this->S.size() == 0){
    throw std::out_of_range("stack is out of range top");
  }
  return this->S.back();
}

template <class T>
unsigned int Stack<T>::size(){
  return this->S.size();
}

template <class T>
std::vector<T> Stack<T>::toSeq(){
	return this->S;
}

// Keep this at bottom
template class Stack<CardT>;
