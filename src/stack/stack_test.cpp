#include <iostream>
#include <stack>

#include "gtest/gtest.h"
#include "s21_stack.h"

TEST(stack, push_pop_empty_size_top) {
  s21::Stack<int> ne_orig;
  ne_orig.push(3);
  ne_orig.push(444);
  ne_orig.push(7);
  std::stack<int> orig;
  orig.push(3);
  orig.push(444);
  orig.push(7);
  EXPECT_EQ(ne_orig.size(), orig.size());
  while (!ne_orig.empty() && !orig.empty()) {
    EXPECT_EQ(ne_orig.top(), orig.top());
    ne_orig.pop();
    orig.pop();
  }
  s21::Stack<int> empty;
  EXPECT_TRUE(empty.empty());
}

TEST(stack, list) {
  std::initializer_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::Stack<int> ne_orig(list);
  std::stack<int> orig(list);
  EXPECT_EQ(ne_orig.size(), orig.size());
  while (!ne_orig.empty() && !orig.empty()) {
    EXPECT_EQ(ne_orig.top(), orig.top());
    ne_orig.pop();
    orig.pop();
  }
}

TEST(stack, swap) {
  s21::Stack<int> ne_orig;
  ne_orig.push(9);
  std::initializer_list<int> list = {3, 444, 7};
  s21::Stack<int> swap_stack(list);
  ne_orig.swap(swap_stack);
  std::stack<int> orig(list);
  EXPECT_EQ(ne_orig.size(), orig.size());
  while (!ne_orig.empty() && !orig.empty()) {
    EXPECT_EQ(ne_orig.top(), orig.top());
    ne_orig.pop();
    orig.pop();
  }
}

TEST(stack, copy) {
  std::initializer_list<int> list = {3, 444, 7};
  s21::Stack<int> orig(list);
  s21::Stack<int> copy(orig);
  EXPECT_EQ(copy.size(), orig.size());
  while (!copy.empty() && !orig.empty()) {
    EXPECT_EQ(copy.top(), orig.top());
    copy.pop();
    orig.pop();
  }
}

TEST(stack, eq) {
  std::initializer_list<int> list = {3, 444, 7};
  s21::Stack<int> eq(list);
  s21::Stack<int> ne_orig;
  ne_orig = std::move(eq);
  std::stack<int> orig(list);
  EXPECT_EQ(ne_orig.size(), orig.size());
  while (!ne_orig.empty() && !orig.empty()) {
    EXPECT_EQ(ne_orig.top(), orig.top());
    ne_orig.pop();
    orig.pop();
  }
}

TEST(stack, move) {
  std::initializer_list<int> list = {3, 444, 7};
  s21::Stack<int> ne_orig(list);
  s21::Stack<int> move(std::move(ne_orig));
  std::stack<int> orig(list);
  EXPECT_EQ(move.size(), orig.size());
  while (!move.empty() && !orig.empty()) {
    EXPECT_EQ(move.top(), orig.top());
    move.pop();
    orig.pop();
  }
}

TEST(stack, emplace) {
  s21::Stack<int> ne_orig;
  ne_orig.emplace_front(3);
  std::stack<int> orig;
  orig.emplace(3);
  while (!ne_orig.empty() && !orig.empty()) {
    EXPECT_EQ(ne_orig.top(), orig.top());
    ne_orig.pop();
    orig.pop();
  }
}
