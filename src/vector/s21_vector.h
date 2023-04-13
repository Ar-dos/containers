#ifndef SRC_VECTOR_S21_VECTOR_H_
#define SRC_VECTOR_S21_VECTOR_H_
#include <iostream>

namespace s21 {

template <class T>

class vector {
 private:
  typedef T value_type;

  typedef T &reference;
  typedef const T &const_reference;

  typedef T *iterator;
  typedef const T *const_iterator;

  typedef size_t size_type;

  size_type size_;
  size_type cap_;
  T *ptr_;

  bool find(const_iterator ptr) {
    bool res = false;
    if (ptr == ptr_) {
      res = true;
    } else {
      for (size_t i = 0; i < size_; i++) {
        if ((ptr_ + i) == ptr) {
          res = true;
        }
      }
    }
    return res;
  }

  void rereserve() {
    if (cap_ == 0) reserve(cap_ + 1);
    if (size_ == cap_) reserve(cap_ * 2);
  }

  void alloc(size_type size) {
    if (size != 0)
      ptr_ = new T[size]{};
    else
      ptr_ = nullptr;
    cap_ = size;
  }

  void del(T **p) {
    if (*p != nullptr) {
      delete[] * p;
      *p = nullptr;
    }
  }

 public:
  vector() : size_(0), cap_(0), ptr_(nullptr) { reserve(cap_); }

  explicit vector(size_type size) : size_(0), cap_(0), ptr_(nullptr) {
    reserve(size);
    size_ = size;
  }

  explicit vector(std::initializer_list<value_type> const &items)
      : size_(0), cap_(0), ptr_(nullptr) {
    reserve(items.size());
    size_ = items.size();
    const T *p = items.begin();
    for (size_t i = 0; i < size_; i++) {
      ptr_[i] = *(p + i);
    }
  }

  vector(const vector &v) : size_(0), cap_(0), ptr_(nullptr) {
    reserve(v.cap_);
    size_ = v.size_;
    for (size_t i = 0; i < v.size_; i++) {
      ptr_[i] = v.ptr_[i];
    }
  }

  vector(vector &&v) : size_(v.size_), cap_(v.cap_), ptr_(v.ptr_) {
    v.ptr_ = nullptr;
    v.size_ = 0;
    v.cap_ = 0;
  }

  ~vector() {
    del(&ptr_);
    ptr_ = nullptr;
  }

  vector<T> &operator=(const vector<T> &V) {
    if (ptr_ != V.ptr_) {
      del(&ptr_);
      size_ = V.size_;
      alloc(V.cap_);
      for (size_t i = 0; i < V.size_; i++) {
        ptr_[i] = V.ptr_[i];
      }
    } else {
      cap_ = 0;
      size_ = 0;
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_) {
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

  bool empty() {
    bool res = false;
    if (size_ == 0) res = true;
    return res;
  }

  size_type size() { return size_; }

  size_type max_size() { return LLONG_MAX / sizeof(T); }

  void reserve(size_type size) {
    if (size > cap_) {
      T *p = ptr_;
      alloc(size);
      for (size_t i = 0; i < size_; i++) {
        ptr_[i] = p[i];
      }
      del(&p);
    }
  }

  size_type capacity() { return cap_; }

  void shrink_to_fit() {
    if (cap_ > size_) cap_ = size_;
  }

  void clear() {
    for (T *it = ptr_; it != ptr_ + size_; ++it) it->~T();
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    iterator res = nullptr;
    if (find(pos)) {
      int poss = pos - ptr_;
      rereserve();
      for (int i = size_; i > poss - 1; i--) ptr_[i + 1] = ptr_[i];
      ptr_[poss] = value;
      size_++;
      res = &ptr_[poss];
    }
    return res;
  }

  iterator erase(iterator pos) {
    iterator res = nullptr;
    if (find(pos)) {
      int poss = pos - ptr_;
      for (int i = poss; i < end() - ptr_; i++) {
        ptr_[i] = ptr_[i + 1];
      }
      size_--;
      res = &ptr_[poss];
    }
    return res;
  }

  void push_back(const_reference value) {
    rereserve();
    ptr_[size_++] = value;
  }

  void pop_back() {
    if (size_ > 0) size_--;
  }

  void swap(vector &other) {
    vector<T> temp(other);
    other = *this;
    *this = temp;
  }

  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    auto it = insert((iterator)pos, T(args...));
    return it;
  }

  template <class... Args>
  void emplace_back(Args &&...args) {
    push_back(T(args...));
  }
};
}  // namespace s21
#endif  // SRC_VECTOR_S21_VECTOR_H_
