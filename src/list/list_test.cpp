#include <cstddef>
#include <list>
#include <stdexcept>

#include "gtest/gtest.h"
#include "s21_list.h"

TEST(list_constructors, default_constructor) {
  s21::list<int> foo;
  ASSERT_EQ(foo.size(), 0);
}

TEST(list_constructors, copy_constructor) {
  s21::list<int> foo;
  for (int i = 0; i < 10; i++) {
    foo.push_back(i);
  }

  s21::list<int> bar(foo);
  for (int i = 0; i < foo.size(); i++) {
    ASSERT_EQ(foo[i], bar[i]);
  }
  ASSERT_EQ(bar.size(), 10);
}

TEST(list_constructors, move_constructor) {
  s21::list<int> foo;
  for (int i = 0; i < 10; i++) {
    foo.push_back(i);
  }

  s21::list<int> bar(std::move(foo));
  for (int i = 0; i < foo.size(); i++) {
    ASSERT_EQ(bar[i], i);
  }
  ASSERT_EQ(bar.size(), 10);
}

TEST(list_constructors, sized_constructor) {
  s21::list<int> foo(5);
  ASSERT_EQ(foo.size(), 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(foo[i], 0);
  }
}

///

TEST(list_methods, push_front_method) {
  s21::list<int> foo;
  for (int i = 0; i < 10; i++) {
    foo.push_front(i);
    ASSERT_EQ(foo.front(), i);
  }
}

TEST(list_methods, push_back_method) {
  s21::list<int> foo;
  for (int i = 0; i < 10; i++) {
    foo.push_back(i);
    ASSERT_EQ(foo.back(), i);
  }
}

TEST(list_methods, pop_front_method) {
  s21::list<int> foo;
  for (int i = 0; i < 10; i++) {
    foo.push_back(i);
  }

  for (int n = 0; n < 10; n++) {
    foo.pop_front();
    if (foo.size() > 0) {
      ASSERT_EQ(foo.front(), n + 1);
    }
  }

  ASSERT_EQ(foo.size(), 0);
}

TEST(list_methods, pop_back_method) {
  s21::list<int> foo;
  for (int i = 0; i < 10; i++) {
    foo.push_back(i);
  }

  for (int n = 0; n < 10; n++) {
    foo.pop_back();
    if (foo.size() > 0) {
      ASSERT_EQ(foo.back(), 10 - n - 2);
    }
  }

  ASSERT_EQ(foo.size(), 0);
}

TEST(list_methods, find_method) {
  s21::list<int> foo;
  for (int i = 0; i < 10; i++) {
    foo.push_back(i);
  }

  for (auto it = foo.begin(); it != foo.end(); it++) {
    auto target = foo.find(*it);
    ASSERT_EQ(*target, *it);
  }
}

TEST(list_methods, insert_method) {
  s21::list<int> foo = {1, 2, 3, 4};
  s21::list<int> bar = {1, 2, 5, 3, 4};
  s21::list<int> baz;

  auto it = foo.find(3);
  foo.insert(it, 5);

  ASSERT_EQ(foo.size(), bar.size());

  for (int n = 0; n < 10; n++) {
    baz.insert(baz.end(), n);
    ASSERT_EQ(baz.back(), n);
    ASSERT_EQ(baz.size(), n + 1);
  }
}

TEST(list_methods, erase_method) {
  s21::list<int> foo;
  for (int i = 0; i < 10; i++) {
    foo.push_back(i);
  }
  for (int n = 0; n < 10; n++) {
    foo.erase(n);
  }

  ASSERT_EQ(foo.size(), 0);

  s21::list<int> bar;
  for (int i = 0; i < 10; i++) {
    bar.push_back(i);
  }

  for (int n = 10 - 1; n >= 0; n--) {
    bar.erase(n);
  }
  ASSERT_EQ(bar.size(), 0);

  s21::list<int> baz = {1, 2, 3};
  baz.erase(2);
  ASSERT_EQ(baz.find(2), baz.end());
  ASSERT_EQ(baz.size(), 2);
}

TEST(list_methods, reverse_method) {
  s21::list<int> foo = {3, 2, 1, 0};
  foo.reverse();
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(foo[i], i);
  }
}

TEST(list_methods, unique_method) {
  s21::list<int> foo = {2, 3, 3, 2, 2, 1};
  foo.unique();
  ASSERT_EQ(foo.size(), 3);
}

TEST(list_methods, swap_method) {
  s21::list<int> foo = {3, 2, 1, 0};
  s21::list<int> bar = {1, 2, 3, 4, 5};
  s21::list<int> baz = {1, 2, 3, 4, 5};

  foo.swap(bar);

  ASSERT_EQ(foo.size(), baz.size());
  for (int i = 0; i < foo.size(); i++) {
    ASSERT_EQ(foo[i], baz[i]);
  }
}

TEST(list_methods, sort_method) {
  s21::list<int> foo = {3, 2, 1, 0};
  s21::list<int> bar = {0, 1, 2, 3};

  foo.sort();

  for (int i = 0; i < foo.size(); i++) {
    ASSERT_EQ(foo[i], bar[i]);
  }
}

TEST(list_methods, merge_method) {
  s21::list<int> foo = {0, 1, 4};
  s21::list<int> bar = {2, 3, 5, 6};
  s21::list<int> baz = {0, 1, 2, 3, 4, 5, 6};

  foo.merge(bar);

  ASSERT_EQ(foo.size(), baz.size());
  for (int i = 0; i < foo.size(); i++) {
    ASSERT_EQ(foo[i], baz[i]);
  }
}

TEST(list_methods, splice_method) {
  s21::list<int> foo = {0, 1, 4};
  auto it = foo.find(1);

  s21::list<int> bar = {2, 3, 5, 6};
  s21::list<int> baz = {0, 2, 3, 5, 6, 1, 4};

  foo.splice(it, bar);

  ASSERT_EQ(bar.size(), 0);
  ASSERT_EQ(foo.size(), baz.size());

  for (int i = 0; i < foo.size(); i++) {
    ASSERT_EQ(foo[i], baz[i]);
  }
}

TEST(list_methods, emplace_method) {
  s21::list<int> list({3000});
  std::list<int> stdList({3000});

  auto iter = list.begin();
  auto jter = stdList.begin();

  list.emplace(iter, 33);
  stdList.emplace(jter, 33);

  list.emplace_back(359);
  stdList.emplace_back(359);

  list.emplace_front(1703);
  stdList.emplace_front(1703);

  EXPECT_EQ(list.size(), stdList.size());
}

///

TEST(list_operators, move_operator) {
  s21::list<int> foo;
  for (int i = 0; i < 10; i++) {
    foo.push_back(i);
  }

  s21::list<int> bar = std::move(foo);
  for (int i = 0; i < foo.size(); i++) {
    ASSERT_EQ(bar[i], i);
  }
  ASSERT_EQ(bar.size(), 10);
}

TEST(list_operators, move_constructor) {
  s21::list<int> foo;
  for (int i = 0; i < 10; i++) {
    foo.push_back(i);
  }

  s21::list<int> bar = foo;
  for (int i = 0; i < foo.size(); i++) {
    ASSERT_EQ(bar[i], i);
  }
  ASSERT_EQ(bar.size(), 10);
}
