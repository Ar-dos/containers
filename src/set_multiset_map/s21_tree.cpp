#include "s21_tree.h"

/* TIter functions */

template <typename Key>
Key &s21::TIter<Key>::operator*() const {
  if (_iter == nullptr) {
    throw std::out_of_range("Zero iterator");
  }
  return _iter->_data;
}

template <typename Key>
s21::TIter<Key> s21::TIter<Key>::operator++() {
  if (_iter->_right != nullptr) {
    _iter = _iter->_right;
    while (_iter->_left != nullptr) {
      _iter = _iter->_left;
    }
  } else {
    while (_iter->_parent->_right == _iter) {
      _iter = _iter->_parent;
    }
    _iter = _iter->_parent;
  }
  return *this;
}

template <typename Key>
s21::TIter<Key> s21::TIter<Key>::operator--() {
  if (_iter->_left != nullptr) {
    _iter = _iter->_left;
    while (_iter->_right != nullptr) {
      _iter = _iter->_right;
    }
  } else {
    if (_iter->_parent == nullptr) {
      throw std::out_of_range("End element");
    } else {
      while (_iter->_parent->_left == _iter) {
        _iter = _iter->_parent;
        if (_iter->_parent == nullptr) {
          throw std::out_of_range("End element");
        }
      }
      _iter = _iter->_parent;
    }
  }
  return *this;
}

template <typename Key>
bool s21::TIter<Key>::operator==(TIter const &iter) {
  return _iter == iter._iter;
}

template <typename Key>
bool s21::TIter<Key>::operator!=(TIter const &iter) {
  return _iter != iter._iter;
}

/*-----------------*/

/* Tree functions */

/*
 * Returns a reference to the leftmost element.
 */
template <typename Key>
typename s21::Tree<Key>::iterator s21::Tree<Key>::begin() {
  iterator iter(_root);
  while (!leftNodeIsNull(iter._iter)) {
    iter._iter = iter._iter->_left;
  }
  return iter;
}

/*
 * Returns a reference to the rightmost element.
 */
template <typename Key>
typename s21::Tree<Key>::iterator s21::Tree<Key>::end() {
  iterator iter(_root);
  while (!rightNodeIsNull(iter._iter)) {
    iter._iter = iter._iter->_right;
  }
  return iter;
}

/*
 * Returns a const reference to the leftmost element.
 */
template <typename Key>
typename s21::Tree<Key>::iterator s21::Tree<Key>::cbegin() const {
  iterator iter(_root);
  while (!leftNodeIsNull(iter._iter)) {
    iter._iter = iter._iter->_left;
  }
  return iter;
}

/*
 * Returns a const reference to the rightmost element.
 */
template <typename Key>
typename s21::Tree<Key>::iterator s21::Tree<Key>::cend() const {
  iterator iter(_root);
  while (!rightNodeIsNull(iter._iter)) {
    iter._iter = iter._iter->_right;
  }
  return iter;
}

/*
 * Default constructor.
 */
template <typename Key>
s21::Tree<Key>::Tree() {
  _root = new node();
}

/*
 * Constructor with std::initializer_list.
 */
template <typename Key>
s21::Tree<Key>::Tree(std::initializer_list<value_type> const &items) {
  _root = new node();
  for (auto item : items) {
    insert(item);
  }
}

/*
 * Copy constructor.
 */
template <typename Key>
s21::Tree<Key>::Tree(const Tree &other) {
  _root = new node();
  if (other._root != _root && !other.empty()) {
    for (const_iterator iter = other.cbegin(); iter != other.cend(); ++iter) {
      insert(*iter);
    }
  }
}

/*
 * Move constructor.
 */
template <typename Key>
s21::Tree<Key>::Tree(Tree &&other) {
  _root = other._root;
  other._root = new node();
}

/*
 * Destructor.
 */
template <typename Key>
s21::Tree<Key>::~Tree() {
  freeNode(_root);
}

/*
 * Move operator.
 */
template <typename Key>
s21::Tree<Key> &s21::Tree<Key>::operator=(s21::Tree<Key> &&other) {
  if (_root != other._root) {
    std::swap(_root, other._root);
    other.clear();
  }
  return *this;
}

/*
 * Checks if there are elements in the tree.
 */
template <typename Key>
bool s21::Tree<Key>::empty() const {
  return (_root->_left == nullptr && _root->_right == nullptr);
}

/*
 * Returns the number of elements in the tree.
 */
template <typename Key>
typename s21::Tree<Key>::size_type s21::Tree<Key>::size() {
  size_type size = 0;
  for (auto iter = begin(); iter != end(); ++iter, ++size) {
  }
  return size;
}

/*
 * Returns the maximum possible number of elements in the tree.
 */
template <typename Key>
typename s21::Tree<Key>::size_type s21::Tree<Key>::max_size() {
  return LLONG_MAX / sizeof(node);
}

/*
 * Clear tree values.
 */
template <typename Key>
void s21::Tree<Key>::clear() {
  freeNode(_root);
  _root = new node();
}

/*
 * Insert value in the tree.
 */
template <typename Key>
typename s21::Tree<Key>::iterator s21::Tree<Key>::insert(
    const s21::Tree<Key>::value_type &value) {
  iterator result;
  if (leftNodeIsNull(_root) && rightNodeIsNull(_root)) {
    _root->_right = new node();
    _root->_right->_parent = _root;
    _root->_data = value;
    iterator temp(_root);
    result = temp;
  } else {
    iterator iter(_root);
    bool stop = false;
    bool moveRight = true;
    while (!stop) {
      if (value < (*iter)) {
        if (leftNodeIsNull(iter._iter)) {
          iter._iter->_left = new node(value);
          iter._iter->_left->_parent = iter._iter;
          stop = true;
        }
        moveRight = false;
        iter._iter = iter._iter->_left;
      } else if (value > (*iter)) {
        if (moveRight && isLastNode(iter._iter)) {
          node *newNode =
              new node(value, nullptr, iter._iter->_right, iter._iter);
          iter._iter->_right->_parent = newNode;
          iter._iter->_right = newNode;
          stop = true;
        } else if (rightNodeIsNull(iter._iter)) {
          iter._iter->_right = new node(value);
          iter._iter->_right->_parent = iter._iter;
          stop = true;
        }
        iter._iter = iter._iter->_right;
      } else {
        node *newNode = new node(value, iter._iter->_left, nullptr, iter._iter);
        if (!leftNodeIsNull(iter._iter)) {
          iter._iter->_left->_parent = newNode;
        }
        iter._iter->_left = newNode;
        stop = true;
      }
    }
    result = iter;
  }
  return result;
}

/*
 * Erases the selected value from the tree.
 */
template <typename Key>
void s21::Tree<Key>::erase(typename s21::Tree<Key>::iterator pos) {
  if (isNotRootNode(pos._iter) || !leftNodeIsNull(pos._iter) ||
      !rightNodeIsNull(pos._iter)) {
    if (leftNodeIsNull(pos._iter) && rightNodeIsNull(pos._iter)) {
      if (isNotRootNode(pos._iter)) {
        if (isLeftNode(pos._iter)) {
          pos._iter->_parent->_left = nullptr;
        } else {
          pos._iter->_parent->_right = nullptr;
        }
      }
      delete (pos._iter);
    } else if (leftNodeIsNull(pos._iter)) {
      if (isNotRootNode(pos._iter)) {
        if (isLeftNode(pos._iter)) {
          pos._iter->_parent->_left = pos._iter->_right;
        } else {
          pos._iter->_parent->_right = pos._iter->_right;
        }
        pos._iter->_right->_parent = pos._iter->_parent;
      } else {
        pos._iter->_right->_parent = nullptr;
        _root = pos._iter->_right;
      }
      delete (pos._iter);
    } else if (rightNodeIsNull(pos._iter)) {
      if (isNotRootNode(pos._iter)) {
        if (isLeftNode(pos._iter)) {
          pos._iter->_parent->_left = pos._iter->_left;
        } else {
          pos._iter->_parent->_right = pos._iter->_left;
        }
        pos._iter->_left->_parent = pos._iter->_parent;
      } else {
        pos._iter->_left->_parent = nullptr;
        _root = pos._iter->_left;
      }
      delete (pos._iter);
    } else {
      iterator temp = pos;
      if (temp._iter->_parent == nullptr && temp._iter->_right == end()._iter) {
        temp._iter = temp._iter->_left;
        while (!rightNodeIsNull(temp._iter)) {
          temp._iter = temp._iter->_right;
        }
      } else {
        if (temp._iter->_right != end()._iter) {
          temp._iter = temp._iter->_right;
        }
        while (!leftNodeIsNull(temp._iter)) {
          temp._iter = temp._iter->_left;
        }
      }
      pos._iter->_data = temp._iter->_data;
      erase(temp);
    }
  }
}

/*
 * Swap the roots.
 */
template <typename Key>
void s21::Tree<Key>::swap(s21::Tree<Key> &other) {
  if (_root != other._root) {
    std::swap(_root, other._root);
  }
}

/*
 * Insert other tree in this tree.
 */
template <typename Key>
void s21::Tree<Key>::merge(s21::Tree<Key> &other) {
  if (_root != other._root) {
    for (iterator iter = other.begin(); iter != other.end(); ++iter) {
      insert(iter._iter->_data);
    }
    other.clear();
  }
}

/*
 * Returns the number of elements matching specific key
 */
template <typename Key>
typename s21::Tree<Key>::size_type s21::Tree<Key>::count(const Key &key) {
  iterator iter = find(key);
  size_type result = 0;
  if (iter._iter != end()._iter) {
    result++;
    while (!leftNodeIsNull(iter._iter) && iter._iter->_left->_data == key) {
      result++;
      iter._iter = iter._iter->_left;
    }
  }
  return result;
}

/*
 * Find value and return its iterator.
 */
template <typename Key>
typename s21::Tree<Key>::iterator s21::Tree<Key>::find(const Key &key) {
  iterator result(nullptr);
  isContain(key, &result);
  return result;
}

/*
 * Checks for the presence of a value.
 */
template <typename Key>
bool s21::Tree<Key>::contains(const Key &key) {
  iterator iter(nullptr);
  return isContain(key, &iter);
}

/*
 * Returns range of elements matching a specific key
 */
template <typename Key>
std::pair<typename s21::Tree<Key>::iterator, typename s21::Tree<Key>::iterator>
s21::Tree<Key>::equal_range(const Key &key) {
  std::pair<iterator, iterator> result(lower_bound(key), upper_bound(key));
  return result;
}

/*
 * Returns an iterator to the first element not less than the given key
 */
template <typename Key>
typename s21::Tree<Key>::iterator s21::Tree<Key>::lower_bound(const Key &key) {
  iterator result = find(key);
  if (result != end()) {
    while (!leftNodeIsNull(result._iter) && result._iter->_left->_data == key) {
      result._iter = result._iter->_left;
    }
  }
  return result;
}

/*
 * Returns an iterator to the first element greater than the given key
 */
template <typename Key>
typename s21::Tree<Key>::iterator s21::Tree<Key>::upper_bound(const Key &key) {
  iterator result = find(key);
  if (result._iter != end()._iter) {
    ++result;
  }
  return result;
}

/* Helpfull functions */

/*
 * Recursive free tree nodes
 */
template <typename Key>
void s21::Tree<Key>::freeNode(node *node) {
  if (node->_left != nullptr) {
    freeNode(node->_left);
  }
  if (node->_right != nullptr) {
    freeNode(node->_right);
  }
  delete (node);
}

/*
 * Used in contatin() and find() as the contain and find functions use the same
 * algorithm but with different return parameters
 */
template <typename Key>
bool s21::Tree<Key>::isContain(const Key &key,
                               typename s21::Tree<Key>::iterator *iter) {
  bool result = true;
  node *node = _root;
  bool stop = false;
  bool moveRight = true;
  while (!stop) {
    if (key < node->_data) {
      if (leftNodeIsNull(node)) {
        result = false;
        *iter = end();
        stop = true;
      }
      node = node->_left;
      moveRight = false;
    } else if (key > node->_data) {
      if (rightNodeIsNull(node) || (moveRight && isLastNode(node))) {
        result = false;
        *iter = end();
        stop = true;
      }
      node = node->_right;
    } else {
      stop = true;
      iter->_iter = node;
    }
  }
  return result;
}

template <typename Key>
bool s21::Tree<Key>::isLeftNode(node *node) const {
  return node->_parent->_left == node;
}

template <typename Key>
bool s21::Tree<Key>::isRightNode(node *node) const {
  return node->_parent->_right == node;
}

/*
 * Return true if next node is end().
 * Doesn't check which branch of the tree it is on.
 */
template <typename Key>
bool s21::Tree<Key>::isLastNode(node *node) const {
  return node->_right->_right == nullptr && node->_right->_left == nullptr;
}

template <typename Key>
bool s21::Tree<Key>::isNotRootNode(node *node) const {
  return node->_parent != nullptr;
}

template <typename Key>
bool s21::Tree<Key>::leftNodeIsNull(node *node) const {
  return node->_left == nullptr;
}

template <typename Key>
bool s21::Tree<Key>::rightNodeIsNull(node *node) const {
  return node->_right == nullptr;
}
