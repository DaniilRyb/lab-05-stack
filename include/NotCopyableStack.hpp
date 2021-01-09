// Copyright 2020 DaniilRybakov <pochtaworld7@gmail.com>

#ifndef LAB_05_STACK_NOTCOPYABLESTACK_HPP
#define LAB_05_STACK_NOTCOPYABLESTACK_HPP
#include "Stack.hpp"
#include <utility>
template <class T>
class StackNotCopyable : public Stack<T> {
 public:
  template <class... Args>
  void push_emplace(Args &&... value);
  T pop();
};
template <class T>
template <class... Args>
void StackNotCopyable<T>::push_emplace(Args &&... value) {
  auto *prevNode = Stack<T>::headNode;
  Stack<T>::headNode = new StackNode<T>{
      {std::forward<Args>(value)...},
      prevNode,
  };
}
template <class T>
T StackNotCopyable<T>::pop() {
  if (Stack<T>::headNode == nullptr) {
    throw std::out_of_range("Error! Stack is empty!");
  }
  auto *prevNode = Stack<T>::headNode;
  Stack<T>::headNode = Stack<T>::headNode->prev;
  T value = std::move(prevNode->value);
  delete prevNode;
  return value;
}
#endif  // LAB_05_STACK_NOTCOPYABLESTACK_HPP
