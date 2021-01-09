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
class TestStackClass {
 public:
  TestStackClass() {}
  TestStackClass(int n, std::string d) : number(n), data(d) {}

 private:
  int number;
  std::string data;
};
TEST(templateStackTests, testPushFunc) {
  TestStackClass a(100, "data");
  TestStackClass b(200, "data1");
  TestStackClass c = b;
  Stack<TestStackClass> StackDataClasses;
  StackDataClasses.push(a);
  StackDataClasses.push(b);
  StackDataClasses.push(c);
  EXPECT_EQ(StackDataClasses.getSizeOfStack(), 3);
}
TEST(moveStackNew, testTypeCanBeMoved) {
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_constructible<Stack<std::size_t>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<std::size_t>>::value);
  EXPECT_TRUE(std::is_move_constructible<Stack<TestStackClass>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<TestStackClass>>::value);
}
TEST(moveStackNew, testTypeCanBeCopyable) {
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack<std::size_t>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<std::size_t>>::value);
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
