// Copyright 2020 DaniilRybakov <pochtaworld7@gmail.com>

#ifndef INCLUDE_STACK_HPP_
#define INCLUDE_STACK_HPP_
#include <iostream>
#include <string>

#include "utility"
template <class T>
struct StackNode {
  T value;
  StackNode *prev = nullptr;
};
template <class T>
class Stack {
 public:
  Stack() = default;
  Stack(const Stack &stack) = delete;
  auto operator=(const Stack<T> &stack) -> Stack<T> & = delete;
  Stack(Stack &&stack) = default;
  auto operator=(Stack<T> &&stack) noexcept -> Stack<T> & = default;
  void push(const T &value);
  void push(T &&value);
  void pop();
  size_t getSizeOfStack() const;
  const T &head() const;
  ~Stack();

 protected:
  StackNode<T> *headNode = nullptr;
};

template <class T>
void Stack<T>::push(const T &value) {
  auto *prevNode = headNode;
  headNode = new StackNode<T>{value, prevNode};
}
template <class T>
void Stack<T>::push(T &&value) {
  auto *prevNode = headNode;
  headNode = new StackNode<T>{std::forward<T>(value), prevNode};
}
template <class T>
void Stack<T>::pop() {
  if (headNode == nullptr) {
    throw std::out_of_range("Error! Stack is empty!");
  }
  StackNode<T> *elem = headNode;
  headNode = headNode->prev;
  delete elem;
}
template <class T>
const T &Stack<T>::head() const {
  if (headNode == nullptr) {
    throw std::out_of_range("Error! Stack is empty!");
  }
  return headNode->value;
}
template <class T>
Stack<T>::~Stack() {
  while (headNode != nullptr) {
    auto *currentNode = headNode;
    headNode = currentNode->prev;
    delete currentNode;
  }
}
template <class T>
size_t Stack<T>::getSizeOfStack() const {
  size_t size = 0;
  StackNode<T> *element = headNode;
  while (element != nullptr) {
    ++size;
    element = element->prev;
  }
  return size;
}
#endif  // INCLUDE_STACK_HPP_
