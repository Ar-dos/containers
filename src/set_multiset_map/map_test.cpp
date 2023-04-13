#include <gtest/gtest.h>

#include <iostream>
#include <map>

#include "s21_map.h"

/*
 * Compares trees for matching each node
 */
template <typename Key, typename T>
bool eqMap(s21::map<Key, T> *map1, std::map<Key, T> *map2) {
  bool result = true;
  if (map1->size() == map2->size()) {
    if (map1->size() != 0) {
      typename s21::map<Key, T>::iterator iter1 = map1->begin();
      typename std::map<Key, T>::iterator iter2 = map2->begin();
      for (; iter1 != map1->end(); ++iter1, ++iter2) {
        if (!((*iter1)._first == (*iter2).first &&
              (*iter1)._second == (*iter2).second)) {
          result = false;
        }
      }
    }
  } else {
    result = false;
  }
  return result;
}

/* map() */
TEST(TestMap, defaultConstructorTest) {
  s21::map<int, int> map1 = s21::map<int, int>();
  std::map<int, int> map2 = std::map<int, int>();
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* map(std::initializer_list<std::pair<Key, T>> const& items) */
TEST(TestMap, constructorWithParametrsTest) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* map(const map& m) */
TEST(TestMap, copyConstructorTest) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  s21::map<int, int> map2 = s21::map<int, int>(map1);
  std::map<int, int> map3 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map4 = std::map<int, int>(map3);
  ASSERT_TRUE(eqMap(&map1, &map3) && eqMap(&map2, &map4));
}

/* map(map&& m) */
TEST(TestMap, moveConstructorTest) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  s21::map<int, int> map2 = s21::map<int, int>(std::move(map1));
  std::map<int, int> map3 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map4 = std::map<int, int>(std::move(map3));
  ASSERT_TRUE(eqMap(&map1, &map3) && eqMap(&map2, &map4));
}

/* map& operator=(map&& m) */
TEST(TestMap, equaloOperatorTest) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  s21::map<int, int> map2;
  std::map<int, int> map3 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map4;
  map2 = s21::map<int, int>({std::pair<int, int>(1, 1)});
  map4 = std::map<int, int>({std::pair<int, int>(1, 1)});
  ASSERT_TRUE(eqMap(&map1, &map3) && eqMap(&map2, &map4));
}

/* T& at(const Key& key) TEST - 1 */
TEST(TestMap, atTest_1) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  ASSERT_TRUE(map1.at(1) == map2.at(1) && map1.at(2) == map2.at(2) &&
              map1.at(3) == map2.at(3));
}

/* T& at(const Key& key) TEST - 2 */
TEST(TestMap, atTest_2) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(2, 2), std::pair<int, int>(1, 1),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  ASSERT_TRUE(map1.at(1) == map2.at(1) && map1.at(2) == map2.at(2) &&
              map1.at(3) == map2.at(3));
}

/* T& operator[](const Key& key) TEST - 1 */
TEST(TestMap, operatorSquareBraketsTest_1) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  ASSERT_TRUE(map1[1] == map2[1] && map1[2] == map2[2] && map1[3] == map2[3]);
}

/* T& operator[](const Key& key) TEST - 2 */
TEST(TestMap, operatorSquareBraketsTest_2) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(2, 2), std::pair<int, int>(1, 1),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(2, 2), std::pair<int, int>(1, 1),
                          std::pair<int, int>(3, 3)});
  ASSERT_TRUE(map1[1] == map2[1] && map1[2] == map2[2] && map1[3] == map2[3]);
}

/* bool empty() TEST - 1 */
TEST(TestMap, emptyTest_1) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  ASSERT_TRUE(map1.empty() == map2.empty());
}

/* bool empty() TEST - 2 */
TEST(TestMap, emptyTest_2) {
  s21::map<int, int> map1 = s21::map<int, int>();
  std::map<int, int> map2 = std::map<int, int>();
  ASSERT_TRUE(map1.empty() == map2.empty());
}

/* size_type size() TEST - 1 */
TEST(TestMap, sizeTest_1) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  ASSERT_TRUE(map1.size() == map2.size());
}

/* size_type size() TEST - 2 */
TEST(TestMap, sizeTest_2) {
  s21::map<int, int> map1 = s21::map<int, int>();
  std::map<int, int> map2 = std::map<int, int>();
  ASSERT_TRUE(map1.size() == map2.size());
}

/* size_type max_size() */
TEST(TestMap, maxSizeTest_1) {
  s21::map<int, int> map1 = s21::map<int, int>();
  std::map<int, int> map2 = std::map<int, int>();
  ASSERT_TRUE(map1.max_size() > 0 && map2.max_size() > 0);
}

/* void clear() TEST - 1 */
TEST(TestMap, clearTest_1) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* void clear() TEST - 2 */
TEST(TestMap, clearTest_2) {
  s21::map<int, int> map1 = s21::map<int, int>();
  std::map<int, int> map2 = std::map<int, int>();
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* std::pair<iterator, bool> insert(const std::pair<Key, T>& value) TEST - 1 */
TEST(TestMap, insertTest_1) {
  s21::map<int, int> map1 = s21::map<int, int>();
  std::map<int, int> map2 = std::map<int, int>();
  map1.insert(std::pair<int, int>(1, 1));
  map2.insert(std::pair<int, int>(1, 1));
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* std::pair<iterator, bool> insert(const std::pair<Key, T>& value) TEST - 2 */
TEST(TestMap, insertTest_2) {
  s21::map<int, int> map1 = s21::map<int, int>();
  std::map<int, int> map2 = std::map<int, int>();
  map1.insert(std::pair<int, int>(1, 1));
  map1.insert(std::pair<int, int>(2, 2));
  map2.insert(std::pair<int, int>(1, 1));
  map2.insert(std::pair<int, int>(2, 2));
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* std::pair<iterator, bool> insert(const std::pair<Key, T>& value) TEST - 3 */
TEST(TestMap, insertTest_3) {
  s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1)});
  std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1)});
  map1.insert(std::pair<int, int>(1, 1));
  map1.insert(std::pair<int, int>(2, 2));
  map2.insert(std::pair<int, int>(1, 1));
  map2.insert(std::pair<int, int>(2, 2));
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* std::pair<iterator, bool> insert(const Key& key, const T& obj) */
TEST(TestMap, insertTest_4) {
  s21::map<int, int> map1 = s21::map<int, int>();
  std::map<int, int> map2 = std::map<int, int>();
  map1.insert(1, 1);
  map1.insert(2, 2);
  map2.insert(std::pair<int, int>(1, 1));
  map2.insert(std::pair<int, int>(2, 2));
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) TEST
 * - 1 */
TEST(TestMap, insertOrAssignTest_1) {
  s21::map<int, int> map1 = s21::map<int, int>();
  std::map<int, int> map2 = std::map<int, int>();
  map1.insert(1, 1);
  map1.insert_or_assign(1, 33);
  map2.insert(std::pair<int, int>(1, 33));
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) TEST
 * - 2 */
TEST(TestMap, insertOrAssignTest_2) {
  s21::map<int, int> map1 = s21::map<int, int>();
  std::map<int, int> map2 = std::map<int, int>();
  map1.insert(1, 1);
  map1.insert_or_assign(2, 2);
  map2.insert(std::pair<int, int>(1, 1));
  map2.insert(std::pair<int, int>(2, 2));
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* void swap(map& other) */
TEST(TestMap, swapTest) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  s21::map<int, int> map2 = s21::map<int, int>();
  std::map<int, int> map3 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map4 = std::map<int, int>();
  map1.swap(map2);
  map3.swap(map4);
  ASSERT_TRUE(eqMap(&map1, &map3) && eqMap(&map2, &map4));
}

/* void merge(map& other) */
TEST(TestMap, mergeTest) {
  s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1)});
  s21::map<int, int> map2 = s21::map<int, int>(
      {std::pair<int, int>(2, 2), std::pair<int, int>(3, 3)});
  std::map<int, int> map3 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  map1.merge(map2);
  ASSERT_TRUE(eqMap(&map1, &map3));
}

/* bool contains(const Key& key) */
TEST(TestMap, containsTest_1) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  ASSERT_TRUE(map1.contains(1) == true && map1.contains(33) == false);
}

/* bool contains(const Key& key) */
TEST(TestMap, containsTest_2) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(2, 1), std::pair<int, int>(1, 1),
                          std::pair<int, int>(3, 3)});
  ASSERT_TRUE(map1.contains(1) == true && map1.contains(33) == false &&
              map1.contains(0) == false);
}

/* void erase(iterator pos) TEST - 1 */
TEST(TestMap, eraseTest_1) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map2 = std::map<int, int>(
      {std::pair<int, int>(1, 1), std::pair<int, int>(2, 2)});
  map1.erase(--map1.end());
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* void erase(iterator pos) TEST - 2 */
TEST(TestMap, eraseTest_2) {
  s21::map<int, int> map1 =
      s21::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  std::map<int, int> map2 = std::map<int, int>(
      {std::pair<int, int>(2, 2), std::pair<int, int>(3, 3)});
  map1.erase(map1.begin());
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* void erase(iterator pos) TEST - 3 */
TEST(TestMap, eraseTest_3) {
  s21::map<int, int> map1 = s21::map<int, int>(
      {std::pair<int, int>(1, 1), std::pair<int, int>(2, 2)});
  std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(2, 2)});
  map1.erase(map1.begin());
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* void erase(iterator pos) TEST - 4 */
TEST(TestMap, eraseTest_4) {
  s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1)});
  std::map<int, int> map2 = std::map<int, int>();
  map1.erase(map1.begin());
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* void erase(iterator pos) TEST - 5 */
TEST(TestMap, eraseTest_5) {
  s21::map<int, int> map1 = s21::map<int, int>(
      {std::pair<int, int>(5, 5), std::pair<int, int>(3, 3)});
  std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(5, 5)});
  map1.erase(map1.begin());
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* void erase(iterator pos) TEST - 6 */
TEST(TestMap, eraseTest_6) {
  s21::map<int, int> map1 = s21::map<int, int>(
      {std::pair<int, int>(5, 5), std::pair<int, int>(3, 3),
       std::pair<int, int>(2, 2), std::pair<int, int>(4, 4)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(5, 5), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  map1.erase(-- --map1.end());
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* void erase(iterator pos) TEST - & */
TEST(TestMap, eraseTest_7) {
  s21::map<int, int> map1 = s21::map<int, int>(
      {std::pair<int, int>(5, 5), std::pair<int, int>(3, 3),
       std::pair<int, int>(2, 2), std::pair<int, int>(4, 4)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(5, 5), std::pair<int, int>(2, 2),
                          std::pair<int, int>(4, 4)});
  map1.erase(-- -- --map1.end());
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* void erase(iterator pos) TEST - 8 */
TEST(TestMap, eraseTest_8) {
  s21::map<int, int> map1 = s21::map<int, int>(
      {std::pair<int, int>(5, 5), std::pair<int, int>(3, 3),
       std::pair<int, int>(2, 2), std::pair<int, int>(4, 4)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(5, 5), std::pair<int, int>(4, 4),
                          std::pair<int, int>(3, 3)});
  map1.erase(map1.begin());
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* void erase(iterator pos) TEST - 9 */
TEST(TestMap, eraseTest_9) {
  s21::map<int, int> map1 = s21::map<int, int>(
      {std::pair<int, int>(5, 5), std::pair<int, int>(3, 3),
       std::pair<int, int>(2, 2), std::pair<int, int>(4, 4)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(2, 2), std::pair<int, int>(4, 4),
                          std::pair<int, int>(3, 3)});
  map1.erase(--map1.end());
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* void erase(iterator pos) TEST - 10 */
TEST(TestMap, eraseTest_10) {
  s21::map<int, int> map1 = s21::map<int, int>(
      {std::pair<int, int>(3, 3), std::pair<int, int>(2, 2),
       std::pair<int, int>(1, 1), std::pair<int, int>(4, 4)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(3, 3), std::pair<int, int>(1, 1),
                          std::pair<int, int>(4, 4)});
  map1.erase(++map1.begin());
  ASSERT_TRUE(eqMap(&map1, &map2));
}

/* std::vector<std::pair<iterator, bool>> emplace(Args&&... args) TEST - 1 */
TEST(TestMap, emplaceTest_1) {
  s21::map<int, int> map1 = s21::map<int, int>(
      {std::pair<int, int>(1, 1), std::pair<int, int>(2, 2)});
  std::map<int, int> map2 = std::map<int, int>(
      {std::pair<int, int>(1, 1), std::pair<int, int>(2, 2)});
  s21::vector<std::pair<typename s21::map<int, int>::iterator, bool>> v1(
      map1.emplace());
  ASSERT_TRUE(eqMap(&map1, &map2) && v1.empty());
}

/* std::vector<std::pair<iterator, bool>> emplace(Args&&... args) TEST - 2 */
TEST(TestMap, emplaceTest_2) {
  s21::map<int, int> map1 = s21::map<int, int>(
      {std::pair<int, int>(1, 1), std::pair<int, int>(2, 2)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(3, 3)});
  s21::vector<std::pair<typename s21::map<int, int>::iterator, bool>> v1(
      map1.emplace(std::pair<int, int>(3, 3)));
  ASSERT_TRUE(eqMap(&map1, &map2) && (*v1.at(0).first)._first == 3 &&
              v1.at(0).second == true);
}

/* std::vector<std::pair<iterator, bool>> emplace(Args&&... args) TEST - 3 */
TEST(TestMap, emplaceTest_3) {
  s21::map<int, int> map1 = s21::map<int, int>(
      {std::pair<int, int>(1, 1), std::pair<int, int>(2, 2)});
  std::map<int, int> map2 = std::map<int, int>(
      {std::pair<int, int>(1, 1), std::pair<int, int>(2, 2)});
  s21::vector<std::pair<typename s21::map<int, int>::iterator, bool>> v1(
      map1.emplace(std::pair<int, int>(1, 1)));
  ASSERT_TRUE(eqMap(&map1, &map2) && (*v1.at(0).first)._first == 1 &&
              v1.at(0).second == false);
}

/* std::vector<std::pair<iterator, bool>> emplace(Args&&... args) TEST - 4 */
TEST(TestMap, emplaceTest_4) {
  s21::map<int, int> map1 = s21::map<int, int>(
      {std::pair<int, int>(1, 1), std::pair<int, int>(2, 2)});
  std::map<int, int> map2 = std::map<int, int>(
      {std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
       std::pair<int, int>(3, 3), std::pair<int, int>(4, 4)});
  s21::vector<std::pair<typename s21::map<int, int>::iterator, bool>> v1(
      map1.emplace(std::pair<int, int>(3, 3), std::pair<int, int>(4, 4)));
  ASSERT_TRUE(eqMap(&map1, &map2) && (*v1.at(0).first)._first == 3 &&
              v1.at(0).second == true && (*v1.at(1).first)._first == 4 &&
              v1.at(1).second == true);
}

/* std::vector<std::pair<iterator, bool>> emplace(Args&&... args) TEST - 5 */
TEST(TestMap, emplaceTest_5) {
  s21::map<int, int> map1 = s21::map<int, int>(
      {std::pair<int, int>(1, 1), std::pair<int, int>(2, 2)});
  std::map<int, int> map2 =
      std::map<int, int>({std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                          std::pair<int, int>(4, 4)});
  s21::vector<std::pair<typename s21::map<int, int>::iterator, bool>> v1(
      map1.emplace(std::pair<int, int>(1, 1), std::pair<int, int>(4, 4)));
  ASSERT_TRUE(eqMap(&map1, &map2) && (*v1.at(0).first)._first == 1 &&
              v1.at(0).second == false && (*v1.at(1).first)._first == 4 &&
              v1.at(1).second == true);
}
