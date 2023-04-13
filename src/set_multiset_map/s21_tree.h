#ifndef SRC_SET_MULTISET_MAP_S21_TREE_H_
#define SRC_SET_MULTISET_MAP_S21_TREE_H_

#include <climits>
#include <cstddef>
#include <stdexcept>

#include "../vector/s21_vector.h"

namespace s21 {

template <typename T>
class Tree;
template <typename T>
class TNode;
template <typename T>
class TIter;

template <typename Key>
class TNode {
  friend class Tree<Key>;
  friend class TIter<Key>;

 private:
  Key _data;

 public:
  TNode *_left;
  TNode *_right;
  TNode *_parent;

  TNode() : _left(nullptr), _right(nullptr), _parent(nullptr) {}
  explicit TNode(const Key data)
      : _data(data), _left(nullptr), _right(nullptr), _parent(nullptr) {}
  TNode(const Key data, TNode *left, TNode *right)
      : _data(data), _left(left), _right(right), _parent(nullptr) {}
  TNode(const Key data, TNode *left, TNode *right, TNode *parent)
      : _data(data), _left(left), _right(right), _parent(parent) {}
};

template <typename Key>
class TIter {
  friend class Tree<Key>;

 private:
  typedef TNode<Key> node;

 public:
  node *_iter;

  TIter() : _iter(nullptr) {}
  explicit TIter(node *iter) : _iter(iter) {}

  Key &operator*() const;
  TIter operator++();
  TIter operator--();
  bool operator==(TIter const &iter);
  bool operator!=(TIter const &iter);
};

template <typename Key>
class Tree {
 protected:
  typedef TIter<Key> iterator;
  typedef TIter<Key> const_iterator;
  typedef Key key_type;
  typedef Key value_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;
  typedef TNode<Key> node;
  node *_root;

  Tree();
  explicit Tree(std::initializer_list<value_type> const &items);
  Tree(const Tree &other);
  Tree(Tree &&other);
  ~Tree();

  Tree &operator=(Tree &&other);

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const;
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(const value_type &value);
  void erase(iterator pos);
  void swap(Tree &other);
  void merge(Tree &other);

  size_type count(const Key &key);
  iterator find(const Key &key);
  bool contains(const Key &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

  template <typename... Args>
  vector<std::pair<iterator, bool>> emplace(Args &&...args);

  void freeNode(node *node);
  bool isContain(const Key &key, iterator *iter);

  bool isLeftNode(node *node) const;
  bool isRightNode(node *node) const;
  bool isLastNode(node *node) const;
  bool isNotRootNode(node *node) const;
  bool leftNodeIsNull(node *node) const;
  bool rightNodeIsNull(node *node) const;
};

}  // namespace s21

#include "s21_tree.cpp"

#endif  // SRC_SET_MULTISET_MAP_S21_TREE_H_
