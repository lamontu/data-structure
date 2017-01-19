/* fibonacci_heap.h
 * The roots of all minimum trees form a doubly linked circular list.
 * All children of a tree node form a doubly linked circular list.
 */

#ifndef __FIBONACCI_HEAP_H__
#define __FIBONACCI_HEAP_H__

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

template<typename T>
struct FibNode {
  T key;
  int degree;
  FibNode<T>* left;
  FibNode<T>* right;
  FibNode<T>* child;
  FibNode<T>* parent;
  bool marked;

  FibNode(T value) : key(value), degree(0), marked(false),
                     child(nullptr), parent(nullptr) {
    left = this;
    right = this;
  }
};

template<typename T>
class FibHeap {
 private:
  int key_num_;
  int max_degree_;
  FibNode<T>* min_;
  FibNode<T>* * consolidate_;

 public:
  FibHeap();
  ~FibHeap();

  void Insert(T key);
  void Combine(FibHeap<T>* other);
  void RemoveMin();
  void Remove(T key);
  bool Contains(T key);
  bool Minimum(T* pkey);
  void Update(T oldkey, T newkey);
  void Destroy();
  void Print();

 private:
  void add_list_node(FibNode<T>* node, FibNode<T>* head);
  void remove_list_node(FibNode<T>* node);
  void insert(FibNode<T>* node);
  void link_lists(FibNode<T>* a, FibNode<T>* b);

  void allocate();
  FibNode<T>* remove_min_tree();
  void attach_tree(FibNode<T>* node, FibNode<T>* root);
  void consolidate();

  void cut(FibNode<T>* node, FibNode<T>* parent);
  void cascading_cut(FibNode<T>* node);
  void decrease(FibNode<T>* node, T key);
  void increase(FibNode<T>* node, T key);

  FibNode<T>* search(FibNode<T>* root, T key);
  FibNode<T>* search(T key);

  void update(FibNode<T>* ndoe, T key);
  void destroy(FibNode<T>* node);
  void print(FibNode<T>* prev, FibNode<T>* node, int direction);
};

template<typename T>
FibHeap<T>::FibHeap() {
  key_num_ = 0;
  max_degree_ = 0;
  min_ = nullptr;
  consolidate_ = nullptr;
}

template<typename T>
FibHeap<T>::~FibHeap() {  }

template<typename T>
void FibHeap<T>::add_list_node(FibNode<T>* node, FibNode<T>* head) {
  node->left = head->left;
  head->left->right = node;
  node->right = head;
  head->left = node;
}

// The removed node still points to the its left node and right node.
template<typename T>
void FibHeap<T>::remove_list_node(FibNode<T>* node) {
  node->left->right = node->right;
  node->right->left = node->left;
}

template<typename T>
void FibHeap<T>::insert(FibNode<T>* node) {
  if (0 == key_num_) {
    min_ = node;
  } else {
    add_list_node(node, min_);
    if (node->key < min_->key) {
      min_ = node;
    }
  }
  key_num_++;
}

template<typename T>
void FibHeap<T>::Insert(T key) {
  FibNode<T>* node;
  node = new FibNode<T>(key);
  if (nullptr == node) return;
  insert(node);
}

template<typename T>
void FibHeap<T>::link_lists(FibNode<T>* a, FibNode<T>* b) {
  FibNode<T>* tmp;
  tmp = a->right;
  a->right = b->right;
  b->right->left = a;
  b->right = tmp;
  tmp->left = b;
}

// Merge fibonacci heap other into this fibonacci heap
template<typename T>
void FibHeap<T>::Combine(FibHeap<T>* other) {
  if (nullptr == other) return;
  if (other->max_degree_ > this->max_degree_) {
    swap(*this, *other);
  }
  if (nullptr == min_) {
    this->min_ = other->min_;
    this->key_num_ = other->key_num_;
    free(other->consolidate_);
    delete other;
    other = nullptr;
  } else if (nullptr == other->min_) {
    free(other->consolidate_);
    delete other;
    other = nullptr;
  } else {
    link_lists(this->min_, other->min_);
    if (this->min_->key > other->min_->key) {
      this->min_ = other->min_;
    }
    this->key_num_ += other->key_num_;
    free(other->consolidate_);
    delete other;
    other = nullptr;
  }
}

template<typename T>
void FibHeap<T>::allocate() {
  int old = max_degree_;
  max_degree_ = ( log(key_num_) / log(2.0) ) + 1;
  if (old >= max_degree_) return;
  consolidate_ = (FibNode<T>**)realloc(consolidate_,
      sizeof(FibHeap<T>*) * (max_degree_ + 1));
}

/* Remove the minimum tree min_ from fibonacci heap.
 * Set the next minimum tree of the old min_ as min_ of the new fibonacci heap.
 */
template<typename T>
FibNode<T>* FibHeap<T>::remove_min_tree() {
  FibNode<T>* p = min_;
  if (p == p->right) {
    min_ = nullptr;
  } else {
    remove_list_node(p);
    min_ = p->right;
  }
  p->left = p->right = p;
  return p;
}

// Attach minimum tree to the the minimum tree root
template<typename T>
void FibHeap<T>::attach_tree(FibNode<T>* node, FibNode<T>* root) {
  remove_list_node(node);
  if (nullptr == root->child) {
    root->child = node;
  } else {
    add_list_node(node, root->child);
  }
  node->parent = root;
  root->degree++;
  node->marked = false;
}

template<typename T>
void FibHeap<T>::consolidate() {
  int i, d, D;
  FibNode<T> *x, *y, *tmp;
  allocate();
  D = max_degree_ + 1;
  for (i = 0; i < D; ++i) {
    consolidate_[i] = nullptr;
  }
  while (min_ != nullptr) {
    x = remove_min_tree();
    d = x->degree;
    // if (consolidate_[d] != nullptr) {
    while (consolidate_[d] != nullptr) {
      y = consolidate_[d];
      if (x->key > y->key) {
        swap(x, y);
      }
      attach_tree(y, x);
      consolidate_[d] = nullptr;
      d++;
    }
    consolidate_[d] = x;
  }
  min_ = nullptr;

  for (i = 0; i < D; ++i) {
    if (consolidate_[i] != nullptr) {
      if (nullptr == min_) {
        min_ = consolidate_[i];
      } else {
        add_list_node(consolidate_[i], min_);
        if (consolidate_[i]->key < min_->key) {
          min_ = consolidate_[i];
        }
      }
    }
  }
}

template<typename T>
void FibHeap<T>::RemoveMin() {
  if (nullptr == min_) return;
  FibNode<T>* child = nullptr;
  FibNode<T>* m = min_;
  while (m->child != nullptr) {
    child = m->child;
    remove_list_node(child);
    if (child->right == child) {
      m->child = nullptr;
    } else {
      m->child = child->right;
    }
    add_list_node(child, min_);
    child->parent = nullptr;
  }
  remove_list_node(m);
  if (m->right == m) {
    min_ = nullptr;
  } else {
    min_ = m->right;
    consolidate();
  }
  key_num_--;
  delete m;
  m = nullptr;
}

/* Cut non-root node from minimum tree,
 * and link it into the root list of the fibonacci heap. 
 */
template<typename T>
void FibHeap<T>::cut(FibNode<T>* node, FibNode<T>* parent) {
  remove_list_node(node);
  parent->degree--;
  if (node == node->right) {
    parent->child = nullptr;
  } else {
    parent->child = node->right;
  }
  node->parent = nullptr;
  node->left = node->right = node;
  node->marked = false;
  add_list_node(node, min_);
}

template<typename T>
void FibHeap<T>::cascading_cut(FibNode<T>* node) {
  FibNode<T>* parent = node->parent;
  if (parent != nullptr) {
    if (false == node->marked) {
      node->marked = true;
    } else {
      cut(node, parent);
      cascading_cut(parent);
    }
  }
}

template<typename T>
void FibHeap<T>::decrease(FibNode<T>* node, T key) {
  FibNode<T>* parent;
  if (nullptr == min_ || nullptr == node) return;
  if (key >= node->key) {
    cout << "Decrease failed: the new key(" << key << ") "
         << "is no smaller than current key(" << node->key << ")" << endl;
    return;
  }
  node->key = key;
  parent = node->parent;
  if ( (parent != nullptr) && (node->key < parent->key) ) {
    cut(node, parent);
    cascading_cut(parent);
  }
  if (node->key < min_->key) {
    min_ = node;
  }
}

template<typename T>
void FibHeap<T>::increase(FibNode<T>* node, T key) {
  FibNode<T> *child, *parent, *right;
  if (nullptr == min_ || nullptr == node) return;
  if (key <= node->key) {
    cout << "Increase failed: the new key(" << key << ") "
         << "is no greater than current key(" << node->key << ")" << endl;
    return;
  }

  /* Avoid checking whether the property of minimum tree has been broken.
   * Cut all children of node from the minimum tree, and link into root list.
   */
  while (node->child != nullptr) {
    child = node->child;
    remove_list_node(child);
    if (child->right == child) {
      node->child = nullptr;
    } else {
      node->child = child->right;
    }
    add_list_node(child, min_);
    child->parent = nullptr;
  }
  node->degree = 0;
  node->key = key;
  parent = node->parent;
  if (parent != nullptr) {  // The node is not in root list.
    cut(node, parent);
    cascading_cut(parent);
  } else if (min_ == node) {  // The node is in root list and is node min_.
    right = node->right;
    while (right != node) {
      if (node->key > right->key) {
        min_ = right;
      }
      right = right->right;
    }
  }
}

// Find key in minimum tree root
template<typename T>
FibNode<T>* FibHeap<T>::search(FibNode<T>* root, T key) {
  if (nullptr == root) return nullptr;
  FibNode<T>* child;
  FibNode<T>* parent = root;
  do {
    if (parent->key == key) {
      return parent;
    } else {
      child = search(parent->child, key);
      if (child != nullptr) return child;
    }
    parent = parent->right;
  } while (parent != root);
  return nullptr;
}

// Find key in fibonacci heap
template<typename T>
FibNode<T>* FibHeap<T>::search(T key) {
  if (nullptr == min_) return nullptr;
  return search(min_, key);
}

template<typename T>
bool FibHeap<T>::Contains(T key) {
  return search(key) != nullptr ? true : false;
}

template<typename T>
bool FibHeap<T>::Minimum(T* pkey) {
  if (nullptr == min_ || nullptr == pkey) {
    return false;
  }
  *pkey = min_->key;
  return true;
}

template<typename T>
void FibHeap<T>::update(FibNode<T>* node, T key) {
  if (key < node->key) {
    decrease(node, key);
  } else if (key > node->key) {
    increase(node, key);
  } else {
    cout << "No need to update!" << endl;
  }
}

template<typename T>
void FibHeap<T>::Update(T oldkey, T newkey) {
  FibNode<T>* node;
  node = search(oldkey);
  if (node != nullptr) {
    update(node, newkey);
  }
}

template<typename T>
void FibHeap<T>::destroy(FibNode<T>* node) {
  FibNode<T>* start = node;
  if (nullptr == node) return;
  do {
    destroy(node->child);
    node = node->right;
    delete node->left;
    node->left = nullptr;
  } while (node != start);
}

template<typename T>
void FibHeap<T>::Destroy() {
  destroy(min_);
}

template<typename T>
void FibHeap<T>::print(FibNode<T>* prev, FibNode<T>* node, int direction) {
  FibNode<T>* start = node;
  if (nullptr == node) return;
  do {
    if (direction == 1) {
      cout << setw(8) << node->key << "(" << node->degree << ") is " << setw(2)
           << prev->key << "'s child" << endl;
    } else {
      cout << setw(8) << node->key << "(" << node->degree << ") is " << setw(2)
           << prev->key << "'s next sibling" << endl;
    }
    if (node->child != nullptr) {
      print(node, node->child, 1);
    }
    prev = node;
    node = node->right;
    direction = 2;
  } while (node != start);
}

template<typename T>
void FibHeap<T>::Print() {
  int i = 0;
  FibNode<T>* p;
  if (nullptr == min_) return;
  cout << "Information of Fibonacci Heap:" << endl;
  p = min_;
  do {
    i++;
    cout << setw(2) << i << ". " << setw(4) << p->key << "(" << p->degree
         << ") is root." << endl;
    print(p, p->child, 1);
    p = p->right;
  } while (p != min_);
  cout << endl;
}

#endif  // __FIBONACCI_HEAP_H__
