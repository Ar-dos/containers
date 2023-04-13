#include <iostream>
#include <set>

#include "s21_set.h"

/*
 * Compares trees for matching each node
 */
template <typename Key>
bool eqSet(s21::set<Key> *set1, std::set<Key> *set2) {
  bool result = true;
  if (set1->size() == set2->size()) {
    if (set1->size() != 0) {
      typename s21::set<Key>::iterator iter1 = set1->begin();
      typename std::set<Key>::iterator iter2 = set2->begin();
      for (; iter1 != set1->end(); ++iter1, ++iter2) {
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

/* set() */
TEST(TestSet, defaultConstructorTest) {
  s21::set<int> set1 = s21::set<int>();
  std::set<int> set2 = std::set<int>();
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* set(std::initializer_list<value_type> const& items) TEST - 1*/
TEST(TestSet, constructorWithParametersTest_1) {
  s21::set<int> set1 = s21::set<int>({1, 2, 3});
  std::set<int> set2 = std::set<int>({1, 2, 3});
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* set(std::initializer_list<value_type> const& items) TEST - 2*/
TEST(TestSet, constructorWithParametersTest_2) {
  s21::set<int> set1 = s21::set<int>({0});
  std::set<int> set2 = std::set<int>({0});
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* set(const set &s) */
TEST(TestSet, copyConstructorTest) {
  s21::set<int> set1 = s21::set<int>({1, 2, 3});
  s21::set<int> set2 = s21::set<int>(set1);
  std::set<int> set3 = std::set<int>({1, 2, 3});
  std::set<int> set4 = std::set<int>(set3);
  ASSERT_TRUE(eqSet(&set1, &set3) && eqSet(&set2, &set4));
}

/* set(set&& s) */
TEST(TestSet, moveConstructorTest) {
  s21::set<int> set1 = s21::set<int>({1, 2, 3});
  s21::set<int> set2 = s21::set<int>(std::move(set1));
  std::set<int> set3 = std::set<int>({1, 2, 3});
  std::set<int> set4 = std::set<int>(std::move(set3));
  ASSERT_TRUE(eqSet(&set1, &set3) && eqSet(&set2, &set4));
}

/* bool empty() TEST - 1 */
TEST(TestSet, emptyTest_1) {
  s21::set<int> set1 = s21::set<int>({1});
  std::set<int> set2 = std::set<int>({1});
  ASSERT_TRUE(set1.empty() == set2.empty());
}

/* bool empty() TEST - 2 */
TEST(TestSet, emptyTest_2) {
  s21::set<int> set1 = s21::set<int>();
  std::set<int> set2 = std::set<int>();
  ASSERT_TRUE(set1.empty() == set2.empty());
}

/* bool empty() TEST - 3 */
TEST(TestSet, emptyTest_3) {
  s21::set<int> set1 = s21::set<int>({4, 2});
  std::set<int> set2 = std::set<int>({4, 2});
  ASSERT_TRUE(set1.empty() == set2.empty());
}

/* bool empty() TEST - 4 */
TEST(TestSet, emptyTest_4) {
  s21::set<int> set1 = s21::set<int>({4, 2, 6});
  std::set<int> set2 = std::set<int>({4, 2, 6});
  ASSERT_TRUE(set1.empty() == set2.empty());
}

/* size_type size() TEST - 1*/
TEST(TestSet, sizeTest_1) {
  s21::set<int> set1 = s21::set<int>({1, 2, 3});
  std::set<int> set2 = std::set<int>({1, 2, 3});
  ASSERT_TRUE(set1.size() == set2.size());
}

/* size_type size() TEST - 2 */
TEST(TestSet, sizeTest_2) {
  s21::set<int> set1 = s21::set<int>();
  std::set<int> set2 = std::set<int>();
  ASSERT_TRUE(set1.size() == set2.size());
}

/*
 * size_type max_size()
 * Test for test, because we have different size of nodes in our and default set
 */
TEST(TestSet, maxSizeTest) {
  s21::set<int> set1 = s21::set<int>({1, 2, 3});
  std::set<int> set2 = std::set<int>({1, 2, 3});
  ASSERT_TRUE(set1.size() > 0 && set2.size() > 0);
}

/* void clear() TEST - 1 */
TEST(TestSet, clearTest_1) {
  s21::set<int> set1 = s21::set<int>({1, 2, 3});
  std::set<int> set2 = std::set<int>({1, 2, 3});
  set1.clear();
  set2.clear();
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void clear() TEST - 2 */
TEST(TestSet, clearTest_2) {
  s21::set<int> set1 = s21::set<int>();
  std::set<int> set2 = std::set<int>();
  set1.clear();
  set2.clear();
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* std::pair<iterator, bool> insert(const value_type& value) TEST - 1 */
TEST(TestSet, insertTest_1) {
  s21::set<int> set1 = s21::set<int>();
  std::set<int> set2 = std::set<int>();
  set1.insert(1);
  set2.insert(1);
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* std::pair<iterator, bool> insert(const value_type& value) TEST - 2 */
TEST(TestSet, insertTest_2) {
  s21::set<int> set1 = s21::set<int>({1});
  std::set<int> set2 = std::set<int>({1});
  set1.insert(0);
  set2.insert(0);
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* std::pair<iterator, bool> insert(const value_type& value) TEST - 3 */
TEST(TestSet, insertTest_3) {
  s21::set<int> set1 = s21::set<int>();
  std::set<int> set2 = std::set<int>();
  set1.insert(4);
  set1.insert(3);
  set2.insert(4);
  set2.insert(3);
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* std::pair<iterator, bool> insert(const value_type& value) TEST - 4 */
TEST(TestSet, insertTest_4) {
  s21::set<int> set1 = s21::set<int>({1});
  std::set<int> set2 = std::set<int>({1});
  set1.insert(1);
  set2.insert(1);
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void swap(set& other) */
TEST(TestSet, swapTest) {
  s21::set<int> set1 = s21::set<int>({1, 2, 3});
  s21::set<int> set2 = s21::set<int>();
  std::set<int> set3 = std::set<int>({1, 2, 3});
  std::set<int> set4 = std::set<int>();
  set1.swap(set2);
  set3.swap(set4);
  ASSERT_TRUE(eqSet(&set1, &set3) && eqSet(&set2, &set4));
}

/* void merge(set& other) */
TEST(TestSet, mergeTest) {
  s21::set<int> set1 = s21::set<int>({1, 2});
  s21::set<int> set2 = s21::set<int>({3, 4});
  std::set<int> set3 = std::set<int>({1, 2, 3, 4});
  set1.merge(set2);
  ASSERT_TRUE(eqSet(&set1, &set3));
}

/* void erase(iterator pos) TEST - 1 */
TEST(TestSet, eraseTest_1) {
  s21::set<int> set1 = s21::set<int>({1, 4, 3});
  std::set<int> set2 = std::set<int>({1, 3});
  set1.erase(--set1.end());
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void erase(iterator pos) TEST - 2 */
TEST(TestSet, eraseTest_2) {
  s21::set<int> set1 = s21::set<int>({6, 2, 3});
  std::set<int> set2 = std::set<int>({6, 3});
  set1.erase(set1.begin());
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void erase(iterator pos) TEST - 3 */
TEST(TestSet, eraseTest_3) {
  s21::set<int> set1 = s21::set<int>({1, 2});
  std::set<int> set2 = std::set<int>({2});
  set1.erase(set1.begin());
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void erase(iterator pos) TEST - 4 */
TEST(TestSet, eraseTest_4) {
  s21::set<int> set1 = s21::set<int>({1});
  std::set<int> set2 = std::set<int>();
  set1.erase(set1.begin());
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void erase(iterator pos) TEST - 5 */
TEST(TestSet, eraseTest_5) {
  s21::set<int> set1 = s21::set<int>({6, 4, 5});
  std::set<int> set2 = std::set<int>({6, 4});
  typename s21::set<int>::iterator iter1 = set1.begin();
  set1.erase(++iter1);
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void erase(iterator pos) TEST - 6 */
TEST(TestSet, eraseTest_6) {
  s21::set<int> set1 = s21::set<int>({6, 8, 10});
  std::set<int> set2 = std::set<int>({6, 8});
  set1.erase(--set1.end());
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void erase(iterator pos) TEST - 7 */
TEST(TestSet, eraseTest_7) {
  s21::set<int> set1 = s21::set<int>({5, 3});
  std::set<int> set2 = std::set<int>({5});
  set1.erase(set1.begin());
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void erase(iterator pos) TEST - 8 */
TEST(TestSet, eraseTest_8) {
  s21::set<int> set1 = s21::set<int>({5, 3});
  std::set<int> set2 = std::set<int>({3});
  set1.erase(--set1.end());
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void erase(iterator pos) TEST - 9 */
TEST(TestSet, eraseTest_9) {
  s21::set<int> set1 = s21::set<int>({5, 3, 2, 4});
  std::set<int> set2 = std::set<int>({5, 2, 3});
  set1.erase(-- --set1.end());
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void erase(iterator pos) TEST - 10 */
TEST(TestSet, eraseTest_10) {
  s21::set<int> set1 = s21::set<int>({5, 3, 2, 4});
  std::set<int> set2 = std::set<int>({5, 2, 4});
  set1.erase(-- -- --set1.end());
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void erase(iterator pos) TEST - 11 */
TEST(TestSet, eraseTest_11) {
  s21::set<int> set1 = s21::set<int>({5, 3, 2, 4});
  std::set<int> set2 = std::set<int>({5, 4, 3});
  set1.erase(set1.begin());
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void erase(iterator pos) TEST - 12 */
TEST(TestSet, eraseTest_12) {
  s21::set<int> set1 = s21::set<int>({5, 3, 2, 4});
  std::set<int> set2 = std::set<int>({2, 4, 3});
  set1.erase(--set1.end());
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void erase(iterator pos) TEST - 13 */
TEST(TestSet, eraseTest_13) {
  s21::set<int> set1 = s21::set<int>({5, 3, 2});
  std::set<int> set2 = std::set<int>({5, 2});
  set1.erase(++set1.begin());
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* void erase(iterator pos) TEST - 14 */
TEST(TestSet, eraseTest_14) {
  s21::set<int> set1 = s21::set<int>({5, 20, 22, 10, 15, 12});
  std::set<int> set2 = std::set<int>({5, 20, 22, 10, 12});
  typename s21::set<int>::iterator iter1 = set1.begin();
  ++iter1;
  ++iter1;
  ++iter1;
  set1.erase(iter1);
  ASSERT_TRUE(eqSet(&set1, &set2));
}

/* vector<std::pair<iterator, bool>> emplace(Args&&... args) TEST - 1 */
TEST(TestSet, emplaceTest_1) {
  s21::set<int> set1 = s21::set<int>({1, 2, 3});
  std::set<int> set2 = std::set<int>({1, 2, 3});
  s21::vector<std::pair<typename s21::set<int>::iterator, bool>> v1(
      set1.emplace());
  ASSERT_TRUE(eqSet(&set1, &set2) && v1.empty());
}

/* vector<std::pair<iterator, bool>> emplace(Args&&... args) TEST - 2 */
TEST(TestSet, emplaceTest_2) {
  s21::set<int> set1 = s21::set<int>({1, 2});
  std::set<int> set2 = std::set<int>({1, 2, 3});
  s21::vector<std::pair<typename s21::set<int>::iterator, bool>> v1(
      set1.emplace(3));
  ASSERT_TRUE(eqSet(&set1, &set2) && *v1.at(0).first == 3 &&
              v1.at(0).second == true);
}

/* vector<std::pair<iterator, bool>> emplace(Args&&... args) TEST - 3 */
TEST(TestSet, emplaceTest_3) {
  s21::set<int> set1 = s21::set<int>({1, 2});
  std::set<int> set2 = std::set<int>({1, 2});
  s21::vector<std::pair<typename s21::set<int>::iterator, bool>> v1(
      set1.emplace(1));
  ASSERT_TRUE(eqSet(&set1, &set2) && *v1.at(0).first &&
              v1.at(0).second == false);
}

/* vector<std::pair<iterator, bool>> emplace(Args&&... args) TEST - 4 */
TEST(TestSet, emplaceTest_4) {
  s21::set<int> set1 = s21::set<int>({1, 2});
  std::set<int> set2 = std::set<int>({1, 2, 3, 4});
  s21::vector<std::pair<typename s21::set<int>::iterator, bool>> v1(
      set1.emplace(3, 4));
  ASSERT_TRUE(eqSet(&set1, &set2) && *v1.at(0).first == 3 &&
              v1.at(0).second == true && *v1.at(1).first == 4 &&
              v1.at(1).second == true);
}

/* vector<std::pair<iterator, bool>> emplace(Args&&... args) TEST - 5 */
TEST(TestSet, emplaceTest_5) {
  s21::set<int> set1 = s21::set<int>({1, 2});
  std::set<int> set2 = std::set<int>({1, 2, 4});
  s21::vector<std::pair<typename s21::set<int>::iterator, bool>> v1(
      set1.emplace(1, 4));
  ASSERT_TRUE(eqSet(&set1, &set2) && *v1.at(0).first == 1 &&
              v1.at(0).second == false && *v1.at(1).first == 4 &&
              v1.at(1).second == true);
}
