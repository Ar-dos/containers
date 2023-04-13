#ifndef SRC_LIST_S21_LIST_H_
#define SRC_LIST_S21_LIST_H_
#include <iostream>

namespace s21 {

template <class T>
class list {
 public:
  struct Iterator;

  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using const_iterator = const Iterator;
  using iterator = Iterator;
  using size_type = int;

  struct Node {
    friend class list;

    Node() {}
    explicit Node(value_type val) : value_(val), next_(nullptr) {}
    Node(value_type val, Node *next) : value_(val), next_(next) {}

   private:
    value_type value_;
    Node *next_;
  };

  struct Iterator {
    friend class list;

    explicit Iterator(Node *node) : m_node_(node) {}

    reference operator*() { return m_node_->value_; }
    reference operator->() { return &m_node_->value_; }

    iterator &operator++() {
      m_node_ = m_node_->next_;
      return *this;
    }

    iterator operator++(int) {
      Iterator old = *this;
      ++(*this);
      return old;
    }

    bool operator==(const iterator &other) const {
      return m_node_ == other.m_node_;
    }

    bool operator!=(const iterator &other) const {
      return m_node_ != other.m_node_;
    }

   private:
    Node *m_node_;
  };

  list() {
    border_ = new Node();
    border_->next_ = head_;
  }

  explicit list(size_type n) : border_(new Node()) {
    for (int i = 0; i < n; ++i) {
      push_back(0);
    }
  }

  list(std::initializer_list<value_type> const &items) : list() {
    for (auto it = items.begin(); it != items.end(); it++) {
      push_back(*it);
    }
  }

  list(const list &list) : border_(new Node()) {
    for (auto it = list.begin(); it != list.end(); it++) {
      push_back(*it);
    }
  }

  list(list &&l) { swap(l); }

  ~list() {
    clear();
    delete border_;
  }

  iterator begin() { return Iterator(head_); }
  iterator end() { return Iterator(border_); }
  const_iterator begin() const { return Iterator(head_); }
  const_iterator end() const { return Iterator(border_); }

  const_iterator tail() { return Iterator(tail_); }
  const_iterator find(const_reference val) const {
    return find(begin(), end(), val);
  }

  iterator find(Iterator head, Iterator tail, const_reference val) const {
    for (auto it = head; it != tail; it++) {
      if (*it == val) return it;
    }
    return tail;
  }

  iterator insert(Iterator pos, const_reference _val) {
    if (pos == begin()) {
      push_front(_val);
      return Iterator(head_);
    } else if (pos == end()) {
      push_back(_val);
      return Iterator(tail_);
    }

    Node *p = new Node(_val, pos.m_node_);
    auto prev_elem = get_prev_elem(pos);

    prev_elem.m_node_->next_ = p;
    size_++;

    return Iterator(p);
  }

  void erase(Iterator pos) {
    if (pos == end()) return;
    if (pos.m_node_ == head_) {
      pop_front();
    } else if (pos.m_node_ == tail_) {
      pop_back();
    } else {
      Node *to_del = pos.m_node_;
      Node *nextOne = pos.m_node_->next_;
      iterator prev_elem = get_prev_elem(pos);
      prev_elem.m_node_->next_ = nextOne;

      delete to_del;
      size_--;
    }
  }

  iterator get_prev_elem(Iterator pos) {
    auto prev_elem = begin();
    for (auto it = begin(); it != end() && it != pos; it++) prev_elem = it;
    return prev_elem;
  }

  void erase(const_reference val) { return erase(find(val)); }

  reference operator=(list &&l) { swap(l); }

  reference operator=(const list &list) {
    clear();

    for (auto it = list.begin(); it != list.end(); it++) {
      push_back(*it);
    }
  }

  reference operator[](int pos) {
    if (pos >= size_) {
      throw std::out_of_range("position is out of range");
    }

    iterator res = begin();

    for (auto it = begin(); it != end(); it++) {
      if (pos-- == 0) {
        res = it;
        break;
      }
    }

    return *res;
  }

  const_reference front() { return head_->value_; }
  const_reference back() { return tail_->value_; }

  bool empty() const { return head_ == nullptr; }

  void push_back(const_reference val) {
    size_++;

    if (empty()) {
      head_ = tail_ = new Node(val, border_);
      border_->next_ = head_;
    } else {
      tail_->next_ = new Node(val, border_);
      tail_ = tail_->next_;
    }
  }

  void push_front(const_reference val) {
    size_++;

    if (empty()) {
      head_ = tail_ = new Node(val, border_);
      border_->next_ = head_;
    } else {
      border_->next_ = new Node(val, head_);
      head_ = border_->next_;
    }
  }

  void pop_front() {
    if (empty()) return;

    if (size() == 1) {
      clear();
      tail_ = head_ = nullptr;
    } else {
      Node *tmp = head_;
      head_ = head_->next_;
      delete tmp;
      size_--;
    }

    border_->next_ = head_;
  }

  void pop_back() {
    if (empty()) return;

    if (size() == 1) {
      clear();
      tail_ = head_ = nullptr;
      border_->next_ = head_;
    } else {
      iterator prev_elem = get_prev_elem(tail());
      Node *tmp = tail_;
      tail_ = prev_elem.m_node_;
      tail_->next_ = border_;
      delete tmp;
      size_--;
    }
  }

  size_type size() const { return size_; }

  void clear() {
    if (size_ == 0) return;
    auto ptr = head_;

    while (ptr != border_) {
      auto to_del = ptr;
      ptr = ptr->next_;
      delete to_del;
    }

    size_ = 0;
  }

  void swap(list &other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(border_, other.border_);
    std::swap(size_, other.size_);
  }

  void merge(list &other) {
    iterator other_it = other.begin();
    for (iterator it = begin(); it != end() && other_it != other.end(); it++) {
      while (*other_it < *it) {
        insert(it, *other_it);
        other_it++;
      }
    }

    while (other_it != other.end()) {
      push_back(*other_it);
      other_it++;
    }
    other.clear();
  }

  void splice(const_iterator pos, list &other) {
    for (iterator it = other.begin(); it != other.end(); it++) {
      insert(pos, *it);
    }
    other.clear();
  }

  void reverse() {
    iterator curr = begin();
    iterator temp = end();
    iterator prev = end();

    while (curr != end()) {
      temp = curr;
      temp++;
      curr.m_node_->next_ = prev.m_node_;
      prev = curr;
      curr = temp;
    }

    Node *tempNode = head_;
    head_ = tail_;
    tail_ = tempNode;
  }

  void unique() {
    for (iterator it = begin(); it != end(); it++) {
      iterator tempStep = it;
      tempStep++;

      while (tempStep != end()) {
        if (*tempStep == *it) {
          iterator toRemove = tempStep++;
          erase(toRemove);
        } else {
          tempStep++;
        }
      }
    }
  }

  void sort() {
    for (iterator it = begin(); it != end(); it++) {
      iterator nextIter = it;
      nextIter++;

      while (nextIter != end()) {
        if (*it > *nextIter) {
          value_type temp = *it;
          *it = *nextIter;
          *nextIter = temp;
        }
        nextIter++;
      }
    }
  }

  template <class... Args>
  iterator emplace(const iterator &pos, Args &&...args) {
    return insert(pos, value_type(args...));
  }

  template <class... Args>
  void emplace_back(Args &&...args) {
    push_back(value_type(args...));
  }

  template <class... Args>
  void emplace_front(Args &&...args) {
    push_front(value_type(args...));
  }

 private:
  Node *head_ = nullptr;
  Node *tail_ = nullptr;
  Node *border_ = nullptr;
  size_type size_ = 0;
};

}  // namespace s21

#endif  // SRC_LIST_S21_LIST_H_
