#ifndef TREAP_H_
#define TREAP_H_

#include <algorithm>
#include <iostream>

using std::max;
using std::sort;
using std::cout;
using std::endl;

static int COUNT;  // Count different key

template<typename T>
struct TreapNode {
  TreapNode<T>* left;
  TreapNode<T>* right;
  T key;
  int priority;
  int size;
  int count;

  TreapNode(T value=T()) : left(nullptr), right(nullptr), key(value),
    priority(rand()), size(1), count(1) {  }

  void Update() {
    size = count;
    if (left != nullptr) {
      size += left->size;
    }
    if (right != nullptr) {
      size += right->size;
    }
  }

  int LeftSize() {
    return nullptr == left ? 0 : left->size;
  }

  int RightSize() {
    return nullptr == right ? 0 : right->size;
  }
};

template<typename T>
class Treap {
 private:
  TreapNode<T>* root_;
  typedef void(*FuncType)(const T&);

 public:
  Treap();
  ~Treap();

  TreapNode<T>* Root() const;
  int Height() const;
  TreapNode<T>* Search(T key) const;
  T MinKth(int k) const;
  T MaxKth(int k) const;
  int RankMin(T key) const;
  void InOrderTraverse(FuncType Visit) const;
  void Insert(T key);
  void Remove(T key);

 private:
  int height(TreapNode<T>* root) const;
  TreapNode<T>* search(TreapNode<T>* root, T key) const;
  TreapNode<T>* min_kth(TreapNode<T>* root, int k) const;
  int rank_min(TreapNode<T>* root, T key) const;
  void in_order_traverse(TreapNode<T>* root, FuncType Visit) const;
  void rotate_left(TreapNode<T>* & node);
  void rotate_right(TreapNode<T>* & node);
  //TreapNode<T>* insert(TreapNode<T>* & root, TreapNode<T>* node);
  TreapNode<T>* insert(TreapNode<T>* & root, T key);
  TreapNode<T>* remove(TreapNode<T>* & root, TreapNode<T>* node);
};

template<typename T>
Treap<T>::Treap() : root_(nullptr) {  }

template<typename T>
Treap<T>::~Treap() {  }

template<typename T>
TreapNode<T>* Treap<T>::Root() const {
  return root_;
}

template<typename T>
int Treap<T>::height(TreapNode<T>* root) const {
  if (nullptr == root) return 0;
  return 1 + max(height(root->left), height(root->right));
}

template<typename T>
int Treap<T>::Height() const {
  return height(root_);
}

template<typename T>
TreapNode<T>* Treap<T>::search(TreapNode<T>* root, T key) const {
  while ( (root != nullptr) && (root->key != key) ) {
    if (key < root->key) {
      root = root->left;
    } else {
      root = root->right;
    }
  }
  return root;
}

template<typename T>
TreapNode<T>* Treap<T>::Search(T key) const {
  return search(root_, key);
}

template<typename T>
TreapNode<T>* Treap<T>::min_kth(TreapNode<T>* root, int k) const {
  if (nullptr == root || k > root->size || k < 1) return nullptr;
  if (k <= root->LeftSize()) {
    return min_kth(root->left, k);
  } else if (k > root->LeftSize() + root->count) {
    return min_kth(root->right, k - root->LeftSize() - root->count);
  } else {
    return root;
  }
}

template<typename T>
T Treap<T>::MinKth(int k) const {
  TreapNode<T>* node;
  if (k < 1 || k > root_->size) {
    cout << "Invalid position." << endl;
    exit(1);
  }
  node = min_kth(root_, k);
  return node->key;
}

template<typename T>
T Treap<T>::MaxKth(int k) const {
  TreapNode<T>* node;
  if (k < 1 || k > root_->size) {
    cout << "Invalid position." << endl;
    exit(1);
  }
  node = min_kth(root_, root_->size - k + 1);
  return node->key;
}

template<typename T>
int Treap<T>::rank_min(TreapNode<T>* root, T key) const {
  if (nullptr == search(root, key)) return -1;
  if (nullptr == root) return 0;
  if (key == root->key) {
    return root->LeftSize() + 1;
  } else if (key < root->key) {
    return rank_min(root->left, key);
  } else {
    return root->LeftSize() + root->count + rank_min(root->right, key);
  }
}

template<typename T>
int Treap<T>::RankMin(T key) const {
  return rank_min(root_, key);
}

template<typename T>
void Treap<T>::in_order_traverse(TreapNode<T>* root, FuncType Visit) const {
  if (root != nullptr) {
    in_order_traverse(root->left, Visit);
    Visit(root->key);
    in_order_traverse(root->right, Visit);
  }
}

template<typename T>
void Treap<T>::InOrderTraverse(FuncType Visit) const {
  in_order_traverse(root_, Visit);
}

template<typename T>
void Treap<T>::rotate_left(TreapNode<T>* & node) {
  if (nullptr == node) return;
  TreapNode<T>* rchild = node->right;
  node->right = rchild->left;
  rchild->left = node;
  node->Update();
  rchild->Update();
  node = rchild;  // This is necessary.
}

template<typename T>
void Treap<T>::rotate_right(TreapNode<T>* & node) {
  if (nullptr == node) return;
  TreapNode<T>* lchild = node->left;
  node->left = lchild->right;
  lchild->right = node;
  node->Update();
  lchild->Update();
  node = lchild;
}

/*
template<typename T>
TreapNode<T>* Treap<T>::insert(TreapNode<T>* & root, TreapNode<T>* node) {
  if (nullptr == node) return root;
  if (nullptr == root) {
    root = node;
  } else if (node->key < root->key) {
    root->left = insert(root->left, node);
    if (root->priority > root->left->priority) {
      rotate_right(root);
    } else {
      root->Update();
    }
  } else if (node->key > root->key) {
    root->right = insert(root->right, node);
    if (root->priority > root->right->priority) {
      rotate_left(root);
    } else {
      root->Update();
    }
  } else {
    root->count++;
    root->Update();
  }
  return root;
}

template<typename T>
void Treap<T>::Insert(T key) {
  TreapNode<T>* node;
  try {
    node = new TreapNode<T>(key);
    COUNT++;
  } catch (std::bad_alloc&) {
    return;
  }
  root_ = insert(root_, node);
}
*/

template<typename T>
TreapNode<T>* Treap<T>::insert(TreapNode<T>* & root, T key) {
  if (nullptr == root) {
    try {
      root = new TreapNode<T>(key);
      COUNT++;
    } catch (std::bad_alloc&) {
      return nullptr;
    }
  } else if (key < root->key) {
    root->left = insert(root->left, key);
    if (root->priority > root->left->priority) {
      rotate_right(root);
    } else {
      root->Update();
    }
  } else if (key > root->key) {
    root->right = insert(root->right, key);
    if (root->priority > root->right->priority) {
      rotate_left(root);
    } else {
      root->Update();
    }
  } else {
    root->count++;
    root->Update();
  }
  return root;
}

template<typename T>
void Treap<T>::Insert(T key) {
  root_ = insert(root_, key);
}

template<typename T>
TreapNode<T>* Treap<T>::remove(TreapNode<T>* & root, TreapNode<T>* node) {
  if (nullptr == root || nullptr == node) {
    // return nullptr  // Wrong
    return root;
  }
  if (node->key < root->key) { // Target at left subtree
    root->left = remove(root->left, node);
    root->Update();
  } else if (node->key > root->key) {  // Target at right subtree
    root->right = remove(root->right, node);
    root->Update();
  } else {  // Target at root
    if ( (root->left != nullptr) && (root->right != nullptr) ) { // Two children
      if (root->left->priority < root->right->priority) {
        rotate_right(root);
        root->right = remove(root->right, node);
        root->Update();
      } else {
        rotate_left(root);
        root->left = remove(root->left, node);
        root->Update();
      }
    } else {  // One children or none
      TreapNode<T>* tmp = root;
      root = (root->left != nullptr) ? root->left : root->right;
      delete tmp;
      tmp = nullptr;
    }
  }
  return root;
}

template<typename T>
void Treap<T>::Remove(T key) {
  TreapNode<T>* node = Search(key);
  root_ = remove(root_, node);
}

#endif  // TREAP_H_
