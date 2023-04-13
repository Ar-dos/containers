#ifndef SRC_SET_MULTISET_MAP_S21_MAP_H_
#define SRC_SET_MULTISET_MAP_S21_MAP_H_

#include "s21_tree.h"

namespace s21 {
template <typename Key, typename T>
class Pair {
 public:
  Key _first;
  T _second;

  Pair() {}
  Pair(const Key &first, const T &second) : _first(first), _second(second) {}
  explicit Pair(const std::pair<Key, T> &value)
      : _first(value.first), _second(value.second) {}

  Pair &operator=(const std::pair<Key, T> &pair) {
    _first = pair.first;
    _second = pair.second;
    return *this;
  }
  Pair &operator=(std::pair<Key, T> &&pair) {
    std::swap(_first, pair.first);
    std::swap(_second, pair.second);
    return *this;
  }

  friend bool operator!=(const Pair<Key, T> &a, const Pair<Key, T> &b) {
    return a._first != b._first;
  }
  friend bool operator==(const Pair<Key, T> &a, const Pair<Key, T> &b) {
    return a._first == b._first;
  }
  friend bool operator>(const Pair<Key, T> &a, const Pair<Key, T> &b) {
    return a._first > b._first;
  }
  friend bool operator<(const Pair<Key, T> &a, const Pair<Key, T> &b) {
    return a._first < b._first;
  }
};

template <typename Key, typename T>
class map : public Tree<Pair<Key, T>> {
 public:
  typedef typename Tree<Pair<Key, T>>::iterator iterator;
  typedef typename Tree<Pair<Key, T>>::const_iterator const_iterator;
  typedef T mapped_type;
  typedef Key key_type;
  typedef Pair<Key, T> value_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;

  map() : Tree<value_type>() {}
  explicit map(std::initializer_list<std::pair<Key, T>> const &items)
      : Tree<value_type>() {
    for (auto item : items) {
      insert(value_type(item));
    }
  }
  map(const map &m) : Tree<value_type>(m) {}
  map(map &&m) : Tree<value_type>(std::move(m)) {}
  map &operator=(map &&m) {
    if (m._root != this->_root) {
      std::swap(this->_root, m._root);
      m.clear();
    }
    return *this;
  }

  iterator begin() { return Tree<value_type>::begin(); }
  iterator end() { return Tree<value_type>::end(); }
  const_iterator cbegin() const { return Tree<value_type>::cbegin(); }
  const_iterator cend() const { return Tree<value_type>::cend(); }

  T &at(const Key &key) {
    T *result;
    if (contains(key)) {
      result = &((*find(key))._second);
    }
    return *result;
  }
  T &operator[](const Key &key) {
    T *result;
    if (contains(key)) {
      result = &((*find(key))._second);
    } else {
      result = &((*insert(key, 0).first)._second);
    }
    return *result;
  }

  bool empty() const { return Tree<value_type>::empty(); }
  size_type size() { return Tree<value_type>::size(); }
  size_type max_size() { return Tree<value_type>::max_size(); }

  void clear() { Tree<value_type>::clear(); }
  std::pair<iterator, bool> insert(const value_type &value) {
    std::pair<iterator, bool> result;
    if (contains(value._first)) {
      result.first = find(value._first);
      result.second = false;
    } else {
      result.first = Tree<value_type>::insert(value);
      result.second = true;
    }
    return result;
  }
  std::pair<iterator, bool> insert(const std::pair<Key, T> &value) {
    return insert(value_type(value));
  }
  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return insert(value_type(key, obj));
  }
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    std::pair<iterator, bool> result = insert(key, obj);
    if (result.second == false) {
      (*(result.first))._second = obj;
    }
    return result;
  }
  void erase(iterator pos) { Tree<value_type>::erase(pos); }
  void swap(map &other) { Tree<value_type>::swap(other); }
  void merge(map &other) { Tree<value_type>::merge(other); }

  iterator find(const Key &key) {
    return Tree<value_type>::find(value_type(key, 0));
  }
  bool contains(const Key &key) {
    return Tree<value_type>::contains(value_type(key, 0));
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    vector<std::pair<iterator, bool>> result;
    std::initializer_list<std::pair<Key, T>> list = {args...};
    for (auto item : list) {
      result.push_back(insert(value_type(item)));
    }
    return result;
  }
};
}  // namespace s21

#endif  // SRC_SET_MULTISET_MAP_S21_MAP_H_
