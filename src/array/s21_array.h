#ifndef SRC_ARRAY_S21_ARRAY_H_
#define SRC_ARRAY_S21_ARRAY_H_
#include <iostream>

namespace s21 {

template <class T, size_t L>

class array {
 private:
  typedef T value_type;

  typedef T &reference;
  typedef const T &const_reference;

  typedef T *iterator;
  typedef const T *const_iterator;

  typedef size_t size_type;

  T ptr_[L];
  size_type size_;

 public:
  array() : size_(L) { ptr_[L] = {}; }

  explicit array(std::initializer_list<value_type> const &items) : size_(L) {
    const T *p = items.begin();
    for (size_t i = 0; i < size_; i++) {
      ptr_[i] = *(p + i);
    }
  }

  array(const array &a) : size_(a.size_) {
    for (size_t i = 0; i < a.size_; i++) {
      ptr_[i] = a.ptr_[i];
    }
  }

  array(array &&a) = default;

  ~array() = default;

  array<T, L> &operator=(const array<T, L> &a) {
    if (ptr_ == a.ptr_) {
      size_ = 0;
    } else {
      size_ = a.size_;
      for (size_t i = 0; i < a.size_; i++) {
        ptr_[i] = a.ptr_[i];
      }
    }
    return *this;
  }

  reference at(size_type pos) {
    if (!(pos < size_)) {
      throw std::exception();
    }
    return ptr_[pos];
  }

  reference operator[](size_type pos) { return ptr_[pos]; }

  const_reference front() {
    if (size_ == 0) throw std::exception();
    return ptr_[0];
  }

  const_reference back() {
    if (size_ == 0) throw std::exception();
    return ptr_[size_ - 1];
  }

  iterator data() { return ptr_; }

  iterator begin() { return ptr_; }

  iterator end() { return &ptr_[size_]; }

  bool empty() { return L == 0; }

  size_type size() { return size_; }

  size_type max_size() { return size_; }

  void swap(array &other) {
    array<T, L> temp(other);
    other = *this;
    *this = temp;
  }
  void fill(const_reference value) {
    for (size_t i = 0; i < size_; i++) {
      ptr_[i] = value;
    }
  }
};
}  // namespace s21
#endif  // SRC_ARRAY_S21_ARRAY_H_
