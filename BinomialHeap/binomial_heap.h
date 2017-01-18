/* binomial_heap.h */

#ifndef __BINOMIAL_HEAP_H__
#define __BINOMIAL_HEAP_H__

#include <iomanip>
#include <iostream>

using namespace std;

template<typename T>
struct BinomialNode {
  T key;
  int degree;
  BinomialNode<T>* child;
  BinomialNode<T>* parent;
  BinomialNode<T>* next;

  BinomialNode(T value)
    : key(value), degree(0), child(nullptr), parent(nullptr), next(nullptr) {  }
};

template<typename T>
class BinomialHeap {
 private:
  BinomialNode<T>* root_;

 public:
  BinomialHeap();
  ~BinomialHeap();

  T Minimum();
  bool Contains(T key);
  void Combine(BinomialHeap<T>* other);
  void Insert(T key);
  void Remove(T key);
  void RemoveMin();
  void Update(T oldkey, T newkey);

  void Print();

 private:
  void minimum(BinomialNode<T>* root,
               BinomialNode<T>* & prev_y, BinomialNode<T>* & y);
  BinomialNode<T>* search(BinomialNode<T>* root, T key);

  BinomialNode<T>* merge(BinomialNode<T>* h1, BinomialNode<T>* h2);
  void link(BinomialNode<T>* child, BinomialNode<T>* root);
  BinomialNode<T>* combine(BinomialNode<T>* h1, BinomialNode<T>* h2);

  BinomialNode<T>* reverse(BinomialNode<T>* root);
  BinomialNode<T>* remove(BinomialNode<T>* root, T key);
  BinomialNode<T>* remove_min(BinomialNode<T>* root);

  void increase(BinomialNode<T>* node, T key);
  void decrease(BinomialNode<T>* node, T key);
  void update(BinomialNode<T>* node, T key);

  void print(BinomialNode<T>* node, BinomialNode<T>* prev, int direction);
};

template<typename T>
BinomialHeap<T>::BinomialHeap() : root_(nullptr) {  }

template<typename T>
BinomialHeap<T>::~BinomialHeap() {  }

template<typename T>
void BinomialHeap<T>::minimum(BinomialNode<T>* root, BinomialNode<T>* & prev_y,
                              BinomialNode<T>* & y) {
  BinomialNode<T> *x, *prev_x;
  if (nullptr == root) return;
  prev_x = root;
  x = root->next;
  prev_y = nullptr;
  y = root;
  while (x != nullptr) {
    if (x->key < y->key) {
      y = x;
      prev_y = prev_x;
    }
    prev_x = x;
    x = x->next;
  }
}

template<typename T>
T BinomialHeap<T>::Minimum() {
  BinomialNode<T> *prev_y, *y;
  minimum(root_, prev_y, y);
  return y->key;
}

template<typename T>
BinomialNode<T>* BinomialHeap<T>::search(BinomialNode<T>* root, T key) {
  BinomialNode<T>* child;
  BinomialNode<T>* parent = root;
  while (parent != nullptr) {
    if (parent->key == key) {
      return parent;
    } else {
      child = search(parent->child, key);
      if (child != nullptr) return child;
      parent = parent->next;
    }
  }
  return nullptr;
}

template<typename T>
bool BinomialHeap<T>::Contains(T key) {
  return search(root_, key) != nullptr ? true : false;
}

/* Merge binomial heap h1 and h2 forming a list
 * in non-decreasing order of the degree.
 */
template<typename T>
BinomialNode<T>* BinomialHeap<T>::merge(BinomialNode<T>* h1,
                                        BinomialNode<T>* h2) {
  BinomialNode<T>* root = nullptr;
  BinomialNode<T>** pos = &root;

  while (h1 && h2) {
    if (h1->degree <= h2->degree) {
      *pos = h1;
      h1 = h1->next;
    } else {
      *pos = h2;
      h2 = h2->next;
    }
    pos = &(*pos)->next;
  }
  if (h1) {
    *pos = h1;
  } else {
    *pos = h2;
  }
  return root;
}

// Link the two binomial trees with a same degree.
template<typename T>
void BinomialHeap<T>::link(BinomialNode<T>* child, BinomialNode<T>* root) {
  child->parent = root;
  child->next = root->child;
  root->child = child;
  root->degree++;
}

template<typename T>
BinomialNode<T>* BinomialHeap<T>::combine(BinomialNode<T>* h1,
                                          BinomialNode<T>* h2) {
  BinomialNode<T>* root;
  BinomialNode<T> *prev_x, *x, *next_x;

  root = merge(h1, h2);
  if (nullptr == root) return nullptr;
  prev_x = nullptr;
  x = root;
  next_x = x->next;
  while (next_x != nullptr) {
    /* Case 1: x->degree != next_x->degree
     * Case 2: x->degree == next_x->degree == next_x->next->degree
     */
    if ( (x->degree != next_x->degree) ||
         ( (next_x->next != nullptr) &&
           (next_x->degree == next_x->next->degree) ) ) {
      prev_x = x;
      x = next_x;
    } else if (x->key <= next_x->key) {
      /* Case 3: x->degree == next_x->degree != next_x->next->degree
       *         && x->key <= next_x->key
       */
      x->next = next_x->next;
      link(next_x, x);  // Node next_x will be the child of node x.
    } else {
      /* Case 4: x->degree == next_x->degree != next_x->next->degree
       *         && x->key > next_x->key
       */
      if (nullptr == prev_x) {
        root = next_x;
      } else {
        prev_x->next = next_x;
      }
      link(x, next_x);  // Node x will be the child of node next_x.
      x = next_x;
    }
    next_x = x->next;
  }
  return root;
}

template<typename T>
void BinomialHeap<T>::Combine(BinomialHeap<T>* other) {
  if (other != nullptr && other->root_ != nullptr) {
    root_ = combine(root_, other->root_);
  }
}

template<typename T>
void BinomialHeap<T>::Insert(T key) {
  BinomialNode<T>* node;
  if (Contains(key)) {
    cout << "Insert Error: the key (" << key << ") is existed already!" << endl;
    return;
  }
  node = new BinomialNode<T>(key);
  if (nullptr == node) return;
  root_ = combine(root_, node);
}

// The root is the head of the list linked by pointer next
template<typename T>
BinomialNode<T>* BinomialHeap<T>::reverse(BinomialNode<T>* root) {
  BinomialNode<T>* next;
  BinomialNode<T>* tail = nullptr;
  if (!root) return root;
  root->parent = nullptr;
  while (root->next) {
    next = root->next;
    root->next = tail;
    tail = root;
    root = next;
    root->parent = nullptr;
  }
  root->next = tail;
  return root;
}

template<typename T>
BinomialNode<T>* BinomialHeap<T>::remove(BinomialNode<T>* root, T key) {
  BinomialNode<T> *node, *parent, *prev, *pos;
  if (nullptr == root) return root;

  node = search(root, key);
  if (nullptr == node) return root;
  parent = node->parent;
  while (parent != nullptr) {
    swap(node->key, parent->key);
    node = parent;
    parent = node->parent;
  }

  prev = nullptr;
  pos = root;
  while (pos != node) {
    prev = pos;
    pos = pos->next;
  }
  if (prev) {
    prev->next = node->next;
  } else {
    root = node->next;
  }

  BinomialNode<T>* node_child = reverse(node->child);
  root = combine(root, node_child);
  delete node;
  node = nullptr;
  return root;
}

template<typename T>
void BinomialHeap<T>::Remove(T key) {
  root_ = remove(root_, key);
}

template<typename T>
BinomialNode<T>* BinomialHeap<T>::remove_min(BinomialNode<T>* root) {
  BinomialNode<T> *y, *prev_y;
  if (nullptr == root) return root;
  minimum(root, prev_y, y);
  if (nullptr == prev_y) {
    root = root->next;
  } else {
    prev_y->next = y->next;
  }
  BinomialNode<T>* child = reverse(y->child);
  root = combine(root, child);
  delete y;
  y = nullptr;
  return root;
}

template<typename T>
void BinomialHeap<T>::RemoveMin() {
  root_ = remove_min(root_);
}

template<typename T>
void BinomialHeap<T>::increase(BinomialNode<T>* node, T key) {
  if ( (key <= node->key) || Contains(key) ) {
    cout << "Increase failed: the new key(" << key << ") is existed already, "
         << "or is no greater than current key(" << node->key << ")." << endl;
    return;
  }

  node->key = key;
  BinomialNode<T> *cur, *child, *least;
  cur = node;
  child = cur->child;
  while (child != nullptr) {
    if (cur->key > child->key) {
      least = child;
      // Find the least node least in child and its siblings.
      while (child->next != nullptr) {
        if (least->key > child->next->key) {
          least = child->next;
        }
        child = child->next;
      }

      swap(least->key, cur->key);
      cur = least;
      child = cur->child;
    } else {
      child = child->next;
    }
  }
}

template<typename T>
void BinomialHeap<T>::decrease(BinomialNode<T>* node, T key) {
  if ( (key >= node->key) || Contains(key) ) {
    cout << "Decrease failed: the new key(" << key << ") is existed already, "
         << "or is no smaller than current key(" << node->key << ")." << endl;
    return;
  }

  node->key = key;
  BinomialNode<T> *child, *parent;
  child = node;
  parent = node->parent;
  while (parent != nullptr && child->key < parent->key) {
    swap(parent->key, child->key);
    child = parent;
    parent = child->parent;
  }
}

template<typename T>
void BinomialHeap<T>::update(BinomialNode<T>* node, T key) {
  if (nullptr == node) return;

  if (key < node->key) {
    decrease(node, key);
  } else if (key > node->key) {
    increase(node, key);
  } else {
    cout << "No need to update!" << endl;
  }
}

template<typename T>
void BinomialHeap<T>::Update(T oldkey, T newkey) {
  BinomialNode<T>* node;
  node = search(root_, oldkey);
  if (node != nullptr) {
    update(node, newkey);
  }
}

/* Print binomial tree 
 * node: current node
 * prev: the parent node of cur or the previous sibling node
 * direction: 1 -- child, 2 -- next sibling
 */
template<typename T>
void BinomialHeap<T>::print(BinomialNode<T>* prev, BinomialNode<T>* node,
                            int direction) {
  while (node != nullptr) {
    if (direction == 1) {
      cout << "\t" << setw(2) << node->key << "(" << node->degree << ") is "
           << setw(2) << prev->key << "'s child" << endl;
    } else {
      cout << "\t" << setw(2) << node->key << "(" << node->degree << ") is "
           << setw(2) << prev->key << "'s next sibling" << endl;
    }
    if (node->child != nullptr) {
      print(node, node->child, 1);
    }
    prev = node;
    node = node->next;
    direction = 2;
  }
}

// Print binomial heap
template<typename T>
void BinomialHeap<T>::Print() {
  BinomialNode<T>* p;
  if (nullptr == root_) return;
  cout << "Information of Binomial Heap( ";
  p = root_;
  while (p != nullptr) {
    cout << "B" << p->degree << " ";
    p = p->next;
  }
  cout << "):" << endl;

  int i = 0;
  p = root_;
  while (p != nullptr) {
    i++;
    cout << i << ". Binomial Tree B" << p->degree << ":" << endl;
    cout << "\t" << setw(2) << p->key << "(" << p->degree << ") is root."
         << endl;
    print(p, p->child, 1);
    p = p->next;
  }
  cout << endl;
}

#endif  // __BINOMIAL_HEAP_H__ 
