#ifndef SRC_SET_MULTISET_MAP_S21_SET_H_
#define SRC_SET_MULTISET_MAP_S21_SET_H_

#include "s21_tree.h"

namespace s21 {
template <typename Key>
class set : public Tree<Key> {
 public:
  typedef typename Tree<Key>::iterator iterator;
  typedef typename Tree<Key>::const_iterator const_iterator;
  typedef typename Tree<Key>::key_type key_type;
  typedef typename Tree<Key>::value_type value_type;
  typedef typename Tree<Key>::reference reference;
  typedef typename Tree<Key>::const_reference const_reference;
  typedef typename Tree<Key>::size_type size_type;

  set() : Tree<Key>() {}
  explicit set(std::initializer_list<value_type> const &items)
      : Tree<Key>(items) {}
  set(const set &s) : Tree<Key>(s) {}
  set(set &&s) : Tree<Key>(std::move(s)) {}
  set &operator=(set &&s) {
    if (s._root != this->_root) {
      std::swap(this->_root, s._root);
      s.clear();
    }
    return *this;
  }

  iterator begin() { return Tree<Key>::begin(); }
  iterator end() { return Tree<Key>::end(); }
  const_iterator cbegin() const { return Tree<Key>::cbegin(); }
  const_iterator cend() const { return Tree<Key>::cend(); }

  bool empty() { return Tree<Key>::empty(); }
  size_type size() { return Tree<Key>::size(); }
  size_type max_size() { return Tree<Key>::max_size(); }

  void clear() { Tree<Key>::clear(); }
  std::pair<iterator, bool> insert(const value_type &value) {
    std::pair<iterator, bool> result;
    if (contains(value)) {
      result.first = find(value);
      result.second = false;
    } else {
      result.first = Tree<Key>::insert(value);
      result.second = true;
    }
    return result;
  }
  void erase(iterator pos) { Tree<Key>::erase(pos); }
  void swap(set &other) { Tree<Key>::swap(other); }
  void merge(set &other) { Tree<Key>::merge(other); }

  iterator find(const Key &key) { return Tree<Key>::find(key); }
  bool contains(const Key &key) { return Tree<Key>::contains(key); }
  template <typename... Args>
  vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    vector<std::pair<iterator, bool>> result;
    std::initializer_list<Key> list = {args...};
    for (auto item : list) {
      result.push_back(insert(item));
    }
    return result;
  }
};
}  // namespace s21

#endif  // SRC_SET_MULTISET_MAP_S21_SET_H_
