#ifndef SRC_SET_MULTISET_MAP_S21_MULTISET_H_
#define SRC_SET_MULTISET_MAP_S21_MULTISET_H_

#include "s21_tree.h"

namespace s21 {
template <typename Key>
class multiset : public Tree<Key> {
 public:
  typedef typename Tree<Key>::iterator iterator;
  typedef typename Tree<Key>::const_iterator const_iterator;
  typedef typename Tree<Key>::key_type key_type;
  typedef typename Tree<Key>::value_type value_type;
  typedef typename Tree<Key>::reference reference;
  typedef typename Tree<Key>::const_reference const_reference;
  typedef typename Tree<Key>::size_type size_type;

  multiset() : Tree<Key>() {}
  explicit multiset(std::initializer_list<value_type> const &items)
      : Tree<Key>(items) {}
  multiset(const multiset &ms) : Tree<Key>(ms) {}
  multiset(multiset &&ms) : Tree<Key>(std::move(ms)) {}
  multiset &operator=(multiset &&ms) {
    if (ms._root != this->_root) {
      std::swap(this->_root, ms._root);
      ms.clear();
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
  iterator insert(const value_type &value) { return Tree<Key>::insert(value); }
  void erase(iterator pos) { Tree<Key>::erase(pos); }
  void swap(multiset &other) { Tree<Key>::swap(other); }
  void merge(multiset &other) { Tree<Key>::merge(other); }

  size_type count(const Key &key) { return Tree<Key>::count(key); }
  iterator find(const Key &key) { return Tree<Key>::find(key); }
  bool contains(const Key &key) { return Tree<Key>::contains(key); }
  std::pair<iterator, iterator> equal_range(const Key &key) {
    return Tree<Key>::equal_range(key);
  }
  iterator lower_bound(const Key &key) { return Tree<Key>::lower_bound(key); }
  iterator upper_bound(const Key &key) { return Tree<Key>::upper_bound(key); }

  template <typename... Args>
  vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    vector<std::pair<iterator, bool>> result;
    std::initializer_list<Key> list = {args...};
    for (auto item : list) {
      result.push_back(std::pair<iterator, bool>(insert(item), true));
    }
    return result;
  }
};
}  // namespace s21

#endif  // SRC_SET_MULTISET_MAP_S21_MULTISET_H_
