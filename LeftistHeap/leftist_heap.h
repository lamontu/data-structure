/* leftist_heap.h
 * The key of a node is less than or equal its children like minimum heap.
 * Null path length, NPL
 * NPL of leaf = 0
 * NPL  Nil = -1
 * NPL of left child >= NPL of right child
 * NPL of node = NPL of right child + 1
 */

#ifndef LEFTIST_HEAP_H_
#define LEFTIST_HEAP_H_

#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::setw;

template<typename T>
struct LeftistNode {
  T key;
  int null_path_length;
  LeftistNode* left_child;
  LeftistNode* right_child;

  LeftistNode(T value, LeftistNode* l, LeftistNode* r)
    : key(value), null_path_length(0), left_child(l), right_child(r) {  }
};

template<typename T>
class LeftistHeap {
 private:
  LeftistNode<T>* root_;
  typedef void(*FuncType)(const T&);

 public:
  LeftistHeap();
  ~LeftistHeap();
  // Type FuncType shall be declared previous.
  void PreOrderTraverse(FuncType Visit);
  void InOrderTraverse(FuncType Visit);
  void PostOrderTraverse(FuncType Visit);

  void Merge(LeftistHeap<T>* other);
  void Insert(T key);
  void RemoveMin();

  void Destroy();
  void Print();

 private:
  void pre_order_traverse(FuncType Visit, LeftistNode<T>* heap) const;
  void in_order_traverse(FuncType Visit, LeftistNode<T>* heap) const;
  void post_order_traverse(FuncType Visit, LeftistNode<T>* heap) const;

  void swap_node(LeftistNode<T>* & x, LeftistNode<T>* & y);
  LeftistNode<T>* merge(LeftistNode<T>* & x, LeftistNode<T>* & y);
  LeftistNode<T>* insert(LeftistNode<T>* heap, T key);
  LeftistNode<T>* remove_min(LeftistNode<T>* & heap);

  void destroy(LeftistNode<T>* & heap);
  void print(LeftistNode<T>* heap, T key, int direction);
};

template<typename T>
LeftistHeap<T>::LeftistHeap() : root_(nullptr) {  }

template<typename T>
LeftistHeap<T>::~LeftistHeap() {
  destroy(root_);
}

template<typename T>
void LeftistHeap<T>::pre_order_traverse(FuncType Visit,
                                        LeftistNode<T>* heap) const {
  if (heap != nullptr) {
    Visit(heap->key);
    pre_order_traverse(Visit, heap->left_child);
    pre_order_traverse(Visit, heap->right_child);
  }
}

template<typename T>
void LeftistHeap<T>::PreOrderTraverse(FuncType Visit) {
  pre_order_traverse(Visit, root_);
}

template<typename T>
void LeftistHeap<T>::in_order_traverse(FuncType Visit,
                                        LeftistNode<T>* heap) const {
  if (heap != nullptr) {
    in_order_traverse(Visit, heap->left_child);
    Visit(heap->key);
    in_order_traverse(Visit, heap->right_child);
  }
}

template<typename T>
void LeftistHeap<T>::InOrderTraverse(FuncType Visit) {
  in_order_traverse(Visit, root_);
}

template<typename T>
void LeftistHeap<T>::post_order_traverse(FuncType Visit,
                                        LeftistNode<T>* heap) const {
  if (heap != nullptr) {
    post_order_traverse(Visit, heap->left_child);
    post_order_traverse(Visit, heap->right_child);
    Visit(heap->key);
  }
}

template<typename T>
void LeftistHeap<T>::PostOrderTraverse(FuncType Visit) {
  post_order_traverse(Visit, root_);
}

template<typename T>
void LeftistHeap<T>::swap_node(LeftistNode<T>* & x, LeftistNode<T>* & y) {
  LeftistNode<T>* tmp = x;
  x = y;
  y = tmp;
}

// Let the larger heap as the right child as the smaller heap.
template<typename T>
LeftistNode<T>* LeftistHeap<T>::merge(LeftistNode<T>* &x, LeftistNode<T>* &y) {
  if (nullptr == x) {
    return y;
  }
  if (nullptr == y) {
    return x;
  }
  // Let x be the root of new merged tree.
  if (x->key > y->key) {
    swap_node(x, y);
  }

  x->right_child = merge(x->right_child, y);

  if (nullptr == x->left_child ||
      x->left_child->null_path_length < x->right_child->null_path_length) {
    LeftistNode<T>* tmp = x->left_child;
    x->left_child = x->right_child;
    x->right_child = tmp;
  }
  if (nullptr == x->left_child || nullptr == x->right_child) {
    x->null_path_length = 0;
  } else {
    x->null_path_length = (x->left_child->null_path_length >
                           x->right_child->null_path_length) ?
              (x->right_child->null_path_length + 1) :
              (x->left_child->null_path_length + 1);
  }
  return x;
}

template<typename T>
void LeftistHeap<T>::Merge(LeftistHeap<T>* other) {
  root_ = merge(root_, other->root_);
}

template<typename T>
LeftistNode<T>* LeftistHeap<T>::insert(LeftistNode<T>* heap, T key) {
  LeftistNode<T>* node;
  node = new LeftistNode<T>(key, nullptr, nullptr);
  if (nullptr == node) {
    cout << "ERROR: create node failed!" << endl;
    return heap;
  }
  return merge(root_, node);
}

template<typename T>
void LeftistHeap<T>::Insert(T key) {
  root_ = insert(root_, key);
}

template<typename T>
LeftistNode<T>* LeftistHeap<T>::remove_min(LeftistNode<T>* & heap) {
  if (nullptr == heap) return nullptr;
  LeftistNode<T>* l = heap->left_child;
  LeftistNode<T>* r = heap->right_child;

  delete heap;
  heap = nullptr;

  return merge(l, r);
}

template<typename T>
void LeftistHeap<T>::RemoveMin() {
  root_ = remove_min(root_);
}

template<typename T>
void LeftistHeap<T>::destroy(LeftistNode<T>* & heap) {
  if (nullptr == heap) return;
  if (heap->left_child != nullptr) {
    destroy(heap->left_child);
  }
  if (heap->right_child != nullptr) {
    destroy(heap->right_child);
  }
  delete heap;
  heap = nullptr;
}

template<typename T>
void LeftistHeap<T>::Destroy() {
  destroy(root_);
}

template<typename T>
void LeftistHeap<T>::print(LeftistNode<T>* heap, T key, int direction) {
  if (heap != nullptr) {
    if (direction == 0) {
      cout << setw(2) << heap->key << "(" << heap->null_path_length
           << ") is root." << endl;
    } else {
      cout << setw(2) << heap->key << "(" << heap->null_path_length
           << ") is " << setw(2)
           << key << "'s" << setw(12)
           << (direction == 1 ? "right child" : "left child") << endl;
    }
    print(heap->left_child, heap->key, -1);
    print(heap->right_child, heap->key, 1);
  }
}

template<typename T>
void LeftistHeap<T>::Print() {
  if (root_ != nullptr) {
    print(root_, root_->key, 0);
  }
}

#endif  // LEFTIST_HEAP_H_
