// Copyright 2020 DaniilRybakov <pochtaworld7@gmail.com>
#include <gtest/gtest.h>

#include "NotCopyableStack.hpp"
#include "Stack.hpp"
const int countIterationsForStack = 10;
TEST(templateStackTests, testHeadFunc) {
  Stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);
  EXPECT_EQ(stack.head(), 30);
}
class DataOfSTack {
 public:
  DataOfSTack() = default;
  DataOfSTack(int n, std::string d) : number(n), data(d) {}
  DataOfSTack(DataOfSTack&& value) noexcept = default;
  DataOfSTack(const DataOfSTack& value) = delete;
  auto operator=(DataOfSTack&& value) noexcept -> DataOfSTack& = default;
  auto operator=(const DataOfSTack& value) -> DataOfSTack& = delete;
  int number;
  std::string data;
};
TEST(templateStackTests, testPushFunc) {
  DataOfSTack a(100, "data");
  DataOfSTack b(200, "data1");
  Stack<DataOfSTack> StackDataClasses;
  StackDataClasses.push(std::move(a));
  StackDataClasses.push(std::move(b));
  EXPECT_EQ(StackDataClasses.getSizeOfStack(), 2);
}
TEST(moveStackNew, testTypeCanBeMoved) {
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_constructible<Stack<std::size_t>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<std::size_t>>::value);
  EXPECT_TRUE(std::is_move_constructible<Stack<DataOfSTack>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<DataOfSTack>>::value);
}
TEST(moveStackNew, testTypeCanBeCopyable) {
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack<std::size_t>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<std::size_t>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack<DataOfSTack>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<DataOfSTack>>::value);
}
TEST(templateStackTests, testPopFunc) {
  Stack<int> stack;
  for (int i = 0; i < countIterationsForStack; ++i) {
    stack.push(i);
  }
  stack.pop();
  stack.pop();
  EXPECT_EQ(stack.head(), 7);
  for (int i = 0; i < countIterationsForStack - 3; ++i) {
    stack.pop();
  }
  EXPECT_EQ(stack.head(), 0);
}
TEST(Exception, ExceptionStackIsEmpty) {
  Stack<int> stack;
  EXPECT_THROW(stack.pop(), std::out_of_range);
  EXPECT_THROW(stack.head(), std::out_of_range);
}
TEST(MoveStackTEST, ExceptionStackIsEmpty) {
  NotCopyableStack<DataOfSTack> stack;
  EXPECT_THROW(stack.pop(), std::out_of_range);
}
TEST(MoveStack, TestAddedElementsInStack) {
  NotCopyableStack<DataOfSTack> stack;
  DataOfSTack elem(1, "data");
  stack.push(std::move(elem));
  DataOfSTack elem1{stack.pop()};
  EXPECT_EQ(elem1.number, 1);
  EXPECT_EQ(elem1.data, "data");
}
TEST(MoveStack, TestPushEmplace) {
  NotCopyableStack<DataOfSTack> stack;
  stack.push_emplace(1334543523, "BIGDATA");
  EXPECT_EQ(stack.head().number, 1334543523);
  EXPECT_EQ(stack.head().data, "BIGDATA");
  stack.push_emplace(999, "BIGDATA1");
  EXPECT_EQ(stack.head().number, 999);
  EXPECT_EQ(stack.getSizeOfStack(), 2);
  stack.pop();
  EXPECT_EQ(stack.head().data, "BIGDATA");
  EXPECT_EQ(stack.getSizeOfStack(), 1);
}
