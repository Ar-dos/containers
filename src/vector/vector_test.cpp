#include <gtest/gtest.h>

#include <vector>

#include "s21_vector.h"

TEST(vector_tests, constructor_param) {
  s21::vector<int> A(5);
  std::vector<int> B(5);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  s21::vector<int> C(0);
  std::vector<int> D(0);
  EXPECT_EQ(C.size(), D.size());
  EXPECT_EQ(C.capacity(), D.capacity());
  for (size_t i = 0; i < D.size(); i++) {
    EXPECT_EQ(C[i], D[i]);
  }
}

TEST(vector_tests, constructor_initializer_list) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(values);
  std::vector<int> B(values);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  s21::vector<int> C(values);
  std::vector<int> D(values);
  EXPECT_EQ(C.size(), D.size());
  EXPECT_EQ(C.capacity(), D.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(C[i], D[i]);
  }
}

TEST(vector_tests, constructor_copy) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(values);
  s21::vector<int> B(A);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(vector_tests, constructor_move) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(values);
  s21::vector<int> B(std::move(A));
  std::vector<int> C(values);
  std::vector<int> D(std::move(C));

  EXPECT_EQ(B.size(), D.size());
  EXPECT_EQ(B.capacity(), D.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(B[i], D[i]);
  }
}

TEST(vector_tests, reserve) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(values);
  std::vector<int> B(values);
  A.reserve(10);
  B.reserve(10);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(vector_tests, push_back) {
  std::vector<int> A;
  s21::vector<int> B;
  A.push_back(69);
  A.push_back(669);
  A.push_back(6699);
  B.push_back(69);
  B.push_back(669);
  B.push_back(6699);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  std::vector<int> C(10);
  s21::vector<int> D(10);
  C.push_back(69);
  C.push_back(669);
  C.push_back(6699);
  D.push_back(69);
  D.push_back(669);
  D.push_back(6699);
  EXPECT_EQ(C.size(), D.size());
  EXPECT_EQ(C.capacity(), D.capacity());
  for (size_t i = 0; i < D.size(); i++) {
    EXPECT_EQ(C[i], D[i]);
  }
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  std::vector<int> E(values);
  s21::vector<int> F(values);
  E.push_back(69);
  F.push_back(69);
  EXPECT_EQ(E.size(), F.size());
  EXPECT_EQ(E.capacity(), F.capacity());
  for (size_t i = 0; i < F.size(); i++) {
    EXPECT_EQ(E[i], F[i]);
  }
}

TEST(vector_tests, pop_back) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  std::vector<int> A(values);
  s21::vector<int> B(values);
  A.pop_back();
  B.pop_back();
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  for (size_t i = 0; i < B.size(); i++) {
    A.pop_back();
    B.pop_back();
  }
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(vector_tests, shrink_to_fit) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  std::vector<int> A(values);
  s21::vector<int> B(values);
  A.push_back(69);
  B.push_back(69);
  A.reserve(10);
  B.reserve(10);
  A.shrink_to_fit();
  B.shrink_to_fit();
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(vector_tests, swap) {
  s21::vector<int> A({0, 1, 2, 3, 4});
  s21::vector<int> B({5, 6, 7});
  A.swap(B);
  std::vector<int> C({0, 1, 2, 3, 4});
  std::vector<int> D({5, 6, 7});
  C.swap(D);
  EXPECT_EQ(A.size(), C.size());
  EXPECT_EQ(A.capacity(), C.capacity());
  for (size_t i = 0; i < C.size(); i++) {
    EXPECT_EQ(A[i], C[i]);
  }
  s21::vector<int> E;
  std::vector<int> F;
  A.swap(E);
  C.swap(F);
  EXPECT_EQ(A.size(), C.size());
  EXPECT_EQ(A.capacity(), C.capacity());
  for (size_t i = 0; i < C.size(); i++) {
    EXPECT_EQ(A[i], C[i]);
  }
}

TEST(vector_tests, empty) {
  s21::vector<int> A({0, 1, 2, 3, 4});
  std::vector<int> B({0, 1, 2, 3, 4});
  EXPECT_EQ(A.empty(), B.empty());

  s21::vector<int> C;
  std::vector<int> D;
  EXPECT_EQ(C.empty(), D.empty());

  s21::vector<int> E(0);
  std::vector<int> F(0);
  EXPECT_EQ(E.empty(), F.empty());
}

TEST(vector_tests, clear) {
  s21::vector<int> A({0, 1, 2, 3, 4});
  std::vector<int> B({0, 1, 2, 3, 4});
  A.clear();
  B.clear();
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < A.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(vector_tests, max_size) {
  s21::vector<int> A;
  std::vector<int> B;
  s21::vector<int> C({0, 1, 2, 3, 4});
  std::vector<int> D({0, 1, 2, 3, 4});
  EXPECT_EQ(A.max_size(), B.max_size());
  EXPECT_EQ(C.max_size(), D.max_size());
}

TEST(vector_tests, operator_equal) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(values);
  std::vector<int> B(values);
  A = std::move(A);
  B = std::move(B);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < A.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  s21::vector<int> C(values);
  std::vector<int> D(values);
  s21::vector<int> E;
  std::vector<int> F;
  E = C;
  F = D;
  EXPECT_EQ(E.size(), F.size());
  EXPECT_EQ(E.capacity(), F.capacity());
  for (size_t i = 0; i < C.size(); i++) {
    EXPECT_EQ(E[i], F[i]);
  }
  s21::vector<int> K(values);
  s21::vector<int> L(values);
  K = K;
  L = L;
  EXPECT_EQ(K.size(), K.size());
  EXPECT_EQ(L.capacity(), L.capacity());
  for (size_t i = 0; i < K.size(); i++) {
    EXPECT_EQ(K[i], L[i]);
  }
}

TEST(vector_tests, at) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(values);
  std::vector<int> B(values);
  EXPECT_EQ(A.at(4), B.at(4));
  EXPECT_EQ(A.at(0), B.at(0));
}

TEST(vector_tests, front) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(values);
  std::vector<int> B(values);
  EXPECT_EQ(A.front(), B.front());
}

TEST(vector_tests, back) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(values);
  std::vector<int> B(values);
  EXPECT_EQ(A.back(), B.back());
}

TEST(vector_tests, data) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(values);
  std::vector<int> B(values);
  EXPECT_EQ(*A.data(), *B.data());
  EXPECT_EQ(*(A.data() + A.size() - 1), *(B.data() + B.size() - 1));
}

TEST(vector_tests, begin) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(values);
  std::vector<int> B(values);
  auto ptr_21 = A.begin();
  auto ptr_ = B.begin();
  EXPECT_EQ(*ptr_21, *ptr_);
}

TEST(vector_tests, end) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(values);
  std::vector<int> B(values);
  auto ptr_21 = A.end();
  auto ptr_ = B.end();
  EXPECT_EQ(*(--ptr_21), *(--ptr_));
}

TEST(vector_tests, insert) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(10);
  std::vector<int> B(10);
  int test = 69;
  EXPECT_EQ(*(A.insert(A.begin() + 2, test)), *(B.insert(B.begin() + 2, test)));
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < A.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  s21::vector<int> C;
  std::vector<int> D;
  EXPECT_EQ(*(C.insert(C.begin(), 69)), *(D.insert(D.begin(), 69)));
  EXPECT_EQ(C.size(), D.size());
  EXPECT_EQ(C.capacity(), D.capacity());
  for (size_t i = 0; i < C.size(); i++) {
    EXPECT_EQ(C[i], D[i]);
  }
  s21::vector<int> E(values);
  std::vector<int> F(values);
  EXPECT_EQ(*(E.insert(E.end() - 1, 69)), *(F.insert(F.end() - 1, 69)));
  EXPECT_EQ(E.size(), F.size());
  EXPECT_EQ(E.capacity(), F.capacity());
  for (size_t i = 0; i < E.size(); i++) {
    EXPECT_EQ(E[i], F[i]);
  }
}

TEST(vector_tests, erase) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(values);
  std::vector<int> B(values);
  A.erase(A.begin());
  B.erase(B.begin());
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < A.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  s21::vector<int> C(values);
  std::vector<int> D(values);
  C.erase((C.begin() + 3));
  D.erase((D.begin() + 3));
  EXPECT_EQ(C.size(), D.size());
  EXPECT_EQ(C.capacity(), D.capacity());
  for (size_t i = 0; i < D.size(); i++) {
    EXPECT_EQ(C[i], D[i]);
  }
}

TEST(vector_tests, emplace) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(values);
  std::vector<int> B(values);
  EXPECT_EQ(*(A.emplace(A.begin(), 69)), *(B.emplace(B.begin(), 69)));
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < A.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  s21::vector<int> C;
  std::vector<int> D;
  EXPECT_EQ(*(C.emplace(C.begin(), 69)), *(D.emplace(D.begin(), 69)));
  EXPECT_EQ(C.size(), D.size());
  EXPECT_EQ(C.capacity(), D.capacity());
  for (size_t i = 0; i < C.size(); i++) {
    EXPECT_EQ(C[i], D[i]);
  }
  s21::vector<int> E(values);
  std::vector<int> F(values);
  EXPECT_EQ(*(C.emplace(C.end() - 1, 69)), *(D.emplace(--(D.end()), 69)));
  EXPECT_EQ(E.size(), F.size());
  EXPECT_EQ(E.capacity(), F.capacity());
  for (size_t i = 0; i < E.size(); i++) {
    EXPECT_EQ(E[i], F[i]);
  }
}

TEST(vector_tests, emplace_back) {
  std::initializer_list<int> values{0, 1, 2, 3, 4};
  s21::vector<int> A(5);
  std::vector<int> B(5);
  A.emplace_back(69);
  B.emplace_back(69);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < A.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  s21::vector<int> C;
  std::vector<int> D;
  C.emplace_back(69);
  D.emplace_back(69);
  EXPECT_EQ(C.size(), D.size());
  EXPECT_EQ(C.capacity(), D.capacity());
  for (size_t i = 0; i < C.size(); i++) {
    EXPECT_EQ(C[i], D[i]);
  }
  s21::vector<int> E(values);
  std::vector<int> F(values);
  E.emplace_back(69);
  F.emplace_back(69);
  EXPECT_EQ(E.size(), F.size());
  EXPECT_EQ(E.capacity(), F.capacity());
  for (size_t i = 0; i < E.size(); i++) {
    EXPECT_EQ(E[i], F[i]);
  }
}
