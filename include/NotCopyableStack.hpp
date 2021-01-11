// Copyright 2020 DaniilRybakov <pochtaworld7@gmail.com>

#ifndef INCLUDE_NOTCOPYABLESTACK_HPP_
#define INCLUDE_NOTCOPYABLESTACK_HPP_
#include <utility>

#include "Stack.hpp"
template <class T>
class NotCopyableStack : public Stack<T> {
 public:
  template <class... Args>
  void push_emplace(Args &&... value);
  T pop();
};
template <class T>
template <class... Args>
void NotCopyableStack<T>::push_emplace(Args &&... value) {
  auto *prevNode = Stack<T>::headNode;
  Stack<T>::headNode = new StackNode<T>{
      {std::forward<Args>(value)...},
      prevNode,
  };
}
template <class T>
T NotCopyableStack<T>::pop() {
  if (Stack<T>::headNode == nullptr) {
    throw std::out_of_range("Error! Stack is empty!");
  }
  auto *prevNode = Stack<T>::headNode;
  Stack<T>::headNode = Stack<T>::headNode->prev;
  T value = std::move(prevNode->value);
  delete prevNode;
  return value;
}
#endif  // INCLUDE_NOTCOPYABLESTACK_HPP_
