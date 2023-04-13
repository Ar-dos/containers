#include <iostream>
#include <queue>

#include "gtest/gtest.h"
#include "s21_queue.h"

TEST(Queue, push_pop_empty_size_front) {
  s21::Queue<int> ne_orig;
  ne_orig.push(3);
  ne_orig.push(444);
  ne_orig.push(7);
  std::queue<int> orig;
  orig.push(3);
  orig.push(444);
  orig.push(7);
  EXPECT_EQ(ne_orig.size(), orig.size());
  EXPECT_EQ(ne_orig.back(), orig.back());
  while (!ne_orig.empty() && !orig.empty()) {
    EXPECT_EQ(ne_orig.front(), orig.front());
    ne_orig.pop();
    orig.pop();
  }
  s21::Queue<int> empty;
  EXPECT_TRUE(empty.empty());
}

TEST(Queue, list) {
  std::initializer_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::Queue<int> ne_orig(list);
  std::queue<int> orig(list);
  EXPECT_EQ(ne_orig.size(), orig.size());
  while (!ne_orig.empty() && !orig.empty()) {
    EXPECT_EQ(ne_orig.front(), orig.front());
    ne_orig.pop();
    orig.pop();
  }
}

TEST(Queue, swap) {
  s21::Queue<int> ne_orig;
  ne_orig.push(9);
  std::initializer_list<int> list = {3, 444, 7};
  s21::Queue<int> swap_Queue(list);
  ne_orig.swap(swap_Queue);
  std::queue<int> orig(list);
  EXPECT_EQ(ne_orig.size(), orig.size());
  while (!ne_orig.empty() && !orig.empty()) {
    EXPECT_EQ(ne_orig.front(), orig.front());
    ne_orig.pop();
    orig.pop();
  }
}

TEST(Queue, copy) {
  std::initializer_list<int> list = {3, 444, 7};
  s21::Queue<int> orig(list);
  s21::Queue<int> copy(orig);
  EXPECT_EQ(copy.size(), orig.size());
  while (!copy.empty() && !orig.empty()) {
    EXPECT_EQ(copy.front(), orig.front());
    copy.pop();
    orig.pop();
  }
}

TEST(Queue, eq) {
  std::initializer_list<int> list = {3, 444, 7};
  s21::Queue<int> eq(list);
  s21::Queue<int> ne_orig;
  ne_orig = std::move(eq);
  std::queue<int> orig(list);
  EXPECT_EQ(ne_orig.size(), orig.size());
  while (!ne_orig.empty() && !orig.empty()) {
    EXPECT_EQ(ne_orig.front(), orig.front());
    ne_orig.pop();
    orig.pop();
  }
}

TEST(Queue, move) {
  std::initializer_list<int> list = {3, 444, 7};
  s21::Queue<int> ne_orig(list);
  s21::Queue<int> move(std::move(ne_orig));
  std::queue<int> orig(list);
  EXPECT_EQ(move.size(), orig.size());
  while (!move.empty() && !orig.empty()) {
    EXPECT_EQ(move.front(), orig.front());
    move.pop();
    orig.pop();
  }
}

TEST(Queue, emplace) {
  s21::Queue<int> ne_orig;
  ne_orig.emplace_back(3);
  std::queue<int> orig;
  orig.emplace(3);
  while (!ne_orig.empty() && !orig.empty()) {
    EXPECT_EQ(ne_orig.back(), orig.back());
    ne_orig.pop();
    orig.pop();
  }
}
