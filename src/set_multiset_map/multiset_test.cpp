#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "s21_multiset.h"

/*
 * Compares trees for matching each node
 */
template <typename Key>
bool eqMultiset(s21::multiset<Key> *ms1, std::multiset<Key> *ms2) {
  bool result = true;
  if (ms1->size() == ms2->size()) {
    if (ms1->size() != 0) {
      typename s21::multiset<Key>::iterator iter1 = ms1->begin();
      typename std::multiset<Key>::iterator iter2 = ms2->begin();
      for (; iter1 != ms1->end(); ++iter1, ++iter2) {
        if (*iter1 != *iter2) {
          result = false;
        }
      }
    }
  } else {
    result = false;
  }
  return result;
}

/* multiset() */
TEST(TestMultiset, defaultConstructorTest) {
  s21::multiset<int> ms1 = s21::multiset<int>();
  std::multiset<int> ms2 = std::multiset<int>();
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* multiset(std::initializer_list<value_type> const &items) */
TEST(TestMultiset, constructorWithParametrsTest) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
  std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* multiset(const multiset &ms) */
TEST(TestMultiset, copyConstructorTest) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
  s21::multiset<int> ms2 = s21::multiset<int>(ms1);
  std::multiset<int> ms3 = std::multiset<int>({1, 2, 3});
  std::multiset<int> ms4 = std::multiset<int>(ms3);
  ASSERT_TRUE(eqMultiset(&ms1, &ms3) && eqMultiset(&ms2, &ms4));
}

/* multiset(multiset &&ms) */
TEST(TestMultiset, moveConstructorTest) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
  s21::multiset<int> ms2 = s21::multiset<int>(std::move(ms1));
  std::multiset<int> ms3 = std::multiset<int>({1, 2, 3});
  std::multiset<int> ms4 = std::multiset<int>(std::move(ms3));
  ASSERT_TRUE(eqMultiset(&ms1, &ms3) && eqMultiset(&ms2, &ms4));
}

/* bool empty() TEST - 1 */
TEST(TestMultiset, emptyTest_1) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
  std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
  ASSERT_TRUE(ms1.empty() == ms2.empty());
}

/* bool empty() TEST - 2 */
TEST(TestMultiset, emptyTest_2) {
  s21::multiset<int> ms1 = s21::multiset<int>();
  std::multiset<int> ms2 = std::multiset<int>();
  ASSERT_TRUE(ms1.empty() == ms2.empty());
}

/* size_type size() TEST - 1 */
TEST(TestMultiset, sizeTest_1) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
  std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
  ASSERT_TRUE(ms1.size() == ms2.size());
}

/* size_type size() TEST - 2 */
TEST(TestMultiset, sizeTest_2) {
  s21::multiset<int> ms1 = s21::multiset<int>();
  std::multiset<int> ms2 = std::multiset<int>();
  ASSERT_TRUE(ms1.size() == ms2.size());
}

/* size_type max_size() */
TEST(TestMultiset, maxSizeTest) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
  std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
  ASSERT_TRUE(ms1.max_size() > 0 && ms2.max_size() > 0);
}

/* void clear() TEST - 1 */
TEST(TestMultiset, clearTest_1) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
  std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
  ms1.clear();
  ms2.clear();
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* void clear() TEST - 2 */
TEST(TestMultiset, clearTest_2) {
  s21::multiset<int> ms1 = s21::multiset<int>();
  std::multiset<int> ms2 = std::multiset<int>();
  ms1.clear();
  ms2.clear();
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* iterator insert(const value_type &value) TEST - 1 */
TEST(TestMultiset, insertTest_1) {
  s21::multiset<int> ms1 = s21::multiset<int>();
  std::multiset<int> ms2 = std::multiset<int>();
  ms1.insert(1);
  ms2.insert(1);
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* iterator insert(const value_type &value) TEST - 2 */
TEST(TestMultiset, insertTest_2) {
  s21::multiset<int> ms1 = s21::multiset<int>({1});
  std::multiset<int> ms2 = std::multiset<int>({1});
  ms1.insert(1);
  ms2.insert(1);
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* iterator insert(const value_type &value) TEST - 3 */
TEST(TestMultiset, insertTest_3) {
  s21::multiset<int> ms1 = s21::multiset<int>();
  std::multiset<int> ms2 = std::multiset<int>();
  ms1.insert(1);
  ms1.insert(2);
  ms2.insert(1);
  ms2.insert(2);
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* void swap(multiset &other) */
TEST(TestMultiset, swapTest) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
  s21::multiset<int> ms2 = s21::multiset<int>();
  std::multiset<int> ms3 = std::multiset<int>({1, 2, 3});
  std::multiset<int> ms4 = std::multiset<int>();
  ms1.swap(ms2);
  ms3.swap(ms4);
  ASSERT_TRUE(eqMultiset(&ms1, &ms3) && eqMultiset(&ms2, &ms4));
}

/* void merge(multiset &other) */
TEST(TestMultiset, mergeTest) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2});
  s21::multiset<int> ms2 = s21::multiset<int>({3, 4});
  std::multiset<int> ms3 = std::multiset<int>({1, 2, 3, 4});
  ms1.merge(ms2);
  ASSERT_TRUE(eqMultiset(&ms1, &ms3));
}

/* iterator find(const Key &key) */
TEST(TestMultiset, findTest) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
  std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
  ASSERT_TRUE(*ms1.find(1) == *ms2.find(1) && *ms1.find(2) == *ms2.find(2) &&
              *ms1.find(3) == *ms2.find(3));
}

/* bool contains(const Key &key) */
TEST(TestMultiset, containsTest) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
  ASSERT_TRUE(ms1.contains(1) && !ms1.contains(4));
}

/* size_type count(const Key& key) */
TEST(TestMultiset, countTest) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 2, 2, 3});
  std::multiset<int> ms2 = std::multiset<int>({1, 2, 2, 2, 3});
  ASSERT_TRUE(ms1.count(1) == ms2.count(1) && ms1.count(2) == ms2.count(2) &&
              ms1.count(3) == ms2.count(3) && ms1.count(4) == ms2.count(4));
}

/* iterator lower_bound(const Key& key) */
TEST(TestMultiset, lowerBoundTest) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 2, 2, 3});
  std::multiset<int> ms2 = std::multiset<int>({1, 2, 2, 2, 3});
  s21::multiset<int>::iterator iter1 = ms1.lower_bound(2);
  std::multiset<int>::iterator iter2 = ms2.lower_bound(2);
  ASSERT_TRUE(*(iter1) == *(iter2) && *(--iter1) == *(--iter2) &&
              *(++ ++iter1) == *(++ ++iter2));
}

/* iterator upper_bound(const Key& key) */
TEST(TestMultiset, upperBoundTest) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 2, 2, 3});
  std::multiset<int> ms2 = std::multiset<int>({1, 2, 2, 2, 3});
  s21::multiset<int>::iterator iter1 = ms1.upper_bound(2);
  std::multiset<int>::iterator iter2 = ms2.upper_bound(2);
  ASSERT_TRUE(*(iter1) == *(iter2) && *(--iter1) == *(--iter2));
}

/* std::pair<iterator,iterator> equal_range(const Key& key) */
TEST(TestMultiset, equalRangeTest) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 2, 2, 3});
  std::multiset<int> ms2 = std::multiset<int>({1, 2, 2, 2, 3});
  std::pair<typename s21::multiset<int>::iterator,
            typename s21::multiset<int>::iterator>
      iter1 = ms1.equal_range(2);
  std::pair<typename std::multiset<int>::iterator,
            typename std::multiset<int>::iterator>
      iter2 = ms2.equal_range(2);
  bool result = true;
  for (; iter1.first != iter1.second || iter2.first != iter2.second;
       ++iter1.first, ++iter2.first) {
    if (*(iter1.first) != *(iter2.first)) result = false;
  }
  ASSERT_TRUE(result);
}

/* void erase(iterator pos) TEST - 1 */
TEST(TestMultiset, eraseTest_1) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
  std::multiset<int> ms2 = std::multiset<int>({1, 2});
  ms1.erase(--ms1.end());
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* void erase(iterator pos) TEST - 2 */
TEST(TestMultiset, eraseTest_2) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
  std::multiset<int> ms2 = std::multiset<int>({2, 3});
  ms1.erase(ms1.begin());
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* void erase(iterator pos) TEST - 3 */
TEST(TestMultiset, eraseTest_3) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2});
  std::multiset<int> ms2 = std::multiset<int>({2});
  ms1.erase(ms1.begin());
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* void erase(iterator pos) TEST - 4 */
TEST(TestMultiset, eraseTest_4) {
  s21::multiset<int> ms1 = s21::multiset<int>({1});
  std::multiset<int> ms2 = std::multiset<int>();
  ms1.erase(ms1.begin());
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* void erase(iterator pos) TEST - 5 */
TEST(TestMultiset, eraseTest_5) {
  s21::multiset<int> ms1 = s21::multiset<int>({5, 3});
  std::multiset<int> ms2 = std::multiset<int>({5});
  ms1.erase(ms1.begin());
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* void erase(iterator pos) TEST - 6 */
TEST(TestMultiset, eraseTest_6) {
  s21::multiset<int> ms1 = s21::multiset<int>({5, 3, 2, 4});
  std::multiset<int> ms2 = std::multiset<int>({5, 2, 3});
  ms1.erase(-- --ms1.end());
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* void erase(iterator pos) TEST - 7 */
TEST(TestMultiset, eraseTest_7) {
  s21::multiset<int> ms1 = s21::multiset<int>({5, 3, 2, 4});
  std::multiset<int> ms2 = std::multiset<int>({5, 2, 4});
  ms1.erase(-- -- --ms1.end());
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* void erase(iterator pos) TEST - 8 */
TEST(TestMultiset, eraseTest_8) {
  s21::multiset<int> ms1 = s21::multiset<int>({5, 3, 2, 4});
  std::multiset<int> ms2 = std::multiset<int>({5, 4, 3});
  ms1.erase(ms1.begin());
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* void erase(iterator pos) TEST - 9 */
TEST(TestMultiset, eraseTest_9) {
  s21::multiset<int> ms1 = s21::multiset<int>({5, 3, 2, 4});
  std::multiset<int> ms2 = std::multiset<int>({2, 4, 3});
  ms1.erase(--ms1.end());
  ASSERT_TRUE(eqMultiset(&ms1, &ms2));
}

/* vector<std::pair<iterator, bool>> emplace(Args &&...args) TEST - 1 */
TEST(TestMultiset, emplaceTest_1) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
  std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
  s21::vector<std::pair<typename s21::multiset<int>::iterator, bool>> v1(
      ms1.emplace());
  ASSERT_TRUE(eqMultiset(&ms1, &ms2) && v1.empty());
}

/* vector<std::pair<iterator, bool>> emplace(Args &&...args) TEST - 2 */
TEST(TestMultiset, emplaceTest_2) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2});
  std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
  s21::vector<std::pair<typename s21::multiset<int>::iterator, bool>> v1(
      ms1.emplace(3));
  ASSERT_TRUE(eqMultiset(&ms1, &ms2) && *v1.at(0).first == 3 &&
              v1.at(0).second == true);
}

/* vector<std::pair<iterator, bool>> emplace(Args &&...args) TEST - 3 */
TEST(TestMultiset, emplaceTest_3) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2});
  std::multiset<int> ms2 = std::multiset<int>({1, 1, 2});
  s21::vector<std::pair<typename s21::multiset<int>::iterator, bool>> v1(
      ms1.emplace(1));
  ASSERT_TRUE(eqMultiset(&ms1, &ms2) && *v1.at(0).first == 1 &&
              v1.at(0).second == true);
}

/* vector<std::pair<iterator, bool>> emplace(Args &&...args) TEST - 4 */
TEST(TestMultiset, emplaceTest_4) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2});
  std::multiset<int> ms2 = std::multiset<int>({1, 2, 3, 4});
  s21::vector<std::pair<typename s21::multiset<int>::iterator, bool>> v1(
      ms1.emplace(3, 4));
  ASSERT_TRUE(eqMultiset(&ms1, &ms2) && *v1.at(0).first == 3 &&
              v1.at(0).second == true && *v1.at(1).first == 4 &&
              v1.at(1).second == true);
}

/* vector<std::pair<iterator, bool>> emplace(Args &&...args) TEST - 5 */
TEST(TestMultiset, emplaceTest_5) {
  s21::multiset<int> ms1 = s21::multiset<int>({1, 2});
  std::multiset<int> ms2 = std::multiset<int>({1, 1, 2, 4});
  s21::vector<std::pair<typename s21::multiset<int>::iterator, bool>> v1(
      ms1.emplace(1, 4));
  ASSERT_TRUE(eqMultiset(&ms1, &ms2) && *v1.at(0).first == 1 &&
              v1.at(0).second == true && *v1.at(1).first == 4 &&
              v1.at(1).second == true);
}

/* multiset &operator=(multiset &&ms) */
TEST(TestMultiset, operatorEqualTest) {
  s21::multiset<int> ms1({1, 2, 2, 2, 3});
  std::multiset<int> ms2({1, 2, 2, 2, 3});
  s21::multiset<int> ms3({1});
  std::multiset<int> ms4({1});
  ms3 = std::move(ms1);
  ms4 = std::move(ms2);
  ASSERT_TRUE(eqMultiset(&ms1, &ms2) && eqMultiset(&ms3, &ms4));
}
