/* skew_heap.h
 * The key of a node is less than or equal its children like minimum heap.
 */

#ifndef SKEW_HEAP_H_
#define SKEW_HEAP_H_

#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::setw;

template<typename T>
struct SkewNode {
  T key;
  SkewNode* left_child;
  SkewNode* right_child;

  SkewNode(T value, SkewNode* left, SkewNode* right)
    : key(value), left_child(left), right_child(right) {  }
};

template<typename T>
class SkewHeap {
 private:
  SkewNode<T>* root_;
  typedef void(*FuncType)(const T&);

 public:
  SkewHeap();
  ~SkewHeap();
  // Type FuncType shall be declared previous.
  void PreOrderTraverse(FuncType Visit);
  void InOrderTraverse(FuncType Visit);
  void PostOrderTraverse(FuncType Visit);

  void Merge(SkewHeap<T>* other);
  void Insert(T key);
  void RemoveMin();

  void Destroy();
  void Print();

 private:
  void pre_order_traverse(FuncType Visit, SkewNode<T>* heap) const;
  void in_order_traverse(FuncType Visit, SkewNode<T>* heap) const;
  void post_order_traverse(FuncType Visit, SkewNode<T>* heap) const;

  void swap_node(SkewNode<T>* & x, SkewNode<T>* & y);
  SkewNode<T>* merge(SkewNode<T>* & x, SkewNode<T>* & y);
  SkewNode<T>* insert(SkewNode<T>* heap, T key);
  SkewNode<T>* remove_min(SkewNode<T>* & heap);

  void destroy(SkewNode<T>* & heap);
  void print(SkewNode<T>* heap, T key, int direction);
};

template<typename T>
SkewHeap<T>::SkewHeap() : root_(nullptr) {  }

template<typename T>
SkewHeap<T>::~SkewHeap() {
  destroy(root_);
}

template<typename T>
void SkewHeap<T>::pre_order_traverse(FuncType Visit,
                                        SkewNode<T>* heap) const {
  if (heap != nullptr) {
    Visit(heap->key);
    pre_order_traverse(Visit, heap->left_child);
    pre_order_traverse(Visit, heap->right_child);
  }
}

template<typename T>
void SkewHeap<T>::PreOrderTraverse(FuncType Visit) {
  pre_order_traverse(Visit, root_);
}

template<typename T>
void SkewHeap<T>::in_order_traverse(FuncType Visit,
                                        SkewNode<T>* heap) const {
  if (heap != nullptr) {
    in_order_traverse(Visit, heap->left_child);
    Visit(heap->key);
    in_order_traverse(Visit, heap->right_child);
  }
}

template<typename T>
void SkewHeap<T>::InOrderTraverse(FuncType Visit) {
  in_order_traverse(Visit, root_);
}

template<typename T>
void SkewHeap<T>::post_order_traverse(FuncType Visit,
                                        SkewNode<T>* heap) const {
  if (heap != nullptr) {
    post_order_traverse(Visit, heap->left_child);
    post_order_traverse(Visit, heap->right_child);
    Visit(heap->key);
  }
}

template<typename T>
void SkewHeap<T>::PostOrderTraverse(FuncType Visit) {
  post_order_traverse(Visit, root_);
}

template<typename T>
void SkewHeap<T>::swap_node(SkewNode<T>* & x, SkewNode<T>* & y) {
  SkewNode<T>* tmp = x;
  x = y;
  y = tmp;
}

/* Let the larger heap as the right child as the smaller heap.
 * This method is a fundamental difference from LeftistHeap.
 */
template<typename T>
SkewNode<T>* SkewHeap<T>::merge(SkewNode<T>* &x, SkewNode<T>* &y) {
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

  // This part is different from LeftistHeap.
  SkewNode<T>* tmp = merge(x->right_child, y);
  x->right_child = x->left_child;
  x->left_child = tmp;

  return x;
}

template<typename T>
void SkewHeap<T>::Merge(SkewHeap<T>* other) {
  root_ = merge(root_, other->root_);
}

template<typename T>
SkewNode<T>* SkewHeap<T>::insert(SkewNode<T>* heap, T key) {
  SkewNode<T>* node;
  node = new SkewNode<T>(key, nullptr, nullptr);
  if (nullptr == node) {
    cout << "ERROR: create node failed!" << endl;
    return heap;
  }
  return merge(root_, node);
}

template<typename T>
void SkewHeap<T>::Insert(T key) {
  root_ = insert(root_, key);
}

template<typename T>
SkewNode<T>* SkewHeap<T>::remove_min(SkewNode<T>* & heap) {
  if (nullptr == heap) return nullptr;
  SkewNode<T>* l = heap->left_child;
  SkewNode<T>* r = heap->right_child;

  delete heap;
  heap = nullptr;

  return merge(l, r);
}

template<typename T>
void SkewHeap<T>::RemoveMin() {
  root_ = remove_min(root_);
}

template<typename T>
void SkewHeap<T>::destroy(SkewNode<T>* & heap) {
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
void SkewHeap<T>::Destroy() {
  destroy(root_);
}

template<typename T>
void SkewHeap<T>::print(SkewNode<T>* heap, T key, int direction) {
  if (heap != nullptr) {
    if (direction == 0) {
      cout << setw(2) << heap->key << " is root." << endl;
    } else {
      cout << setw(2) << heap->key << " is "
           << setw(2) << key << "'s"
           << setw(12) << (direction == 1 ? "right child" : "left child")
           << endl;
    }
    print(heap->left_child, heap->key, -1);
    print(heap->right_child, heap->key, 1);
  }
}

template<typename T>
void SkewHeap<T>::Print() {
  if (root_ != nullptr) {
    print(root_, root_->key, 0);
  }
}

#endif  // SKEW_HEAP_H_
