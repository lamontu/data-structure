/* avltree.h */ 

#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

template<typename T>
class AVLTreeNode {
 public:
  T key;
  int height;
  AVLTreeNode* left;
  AVLTreeNode* right;

  AVLTreeNode(T value, AVLTreeNode* l, AVLTreeNode* r)
    : key(value), height(0), left(l), right(r) {  } 
};

template<typename T>
class AVLTree {
 private:
  AVLTreeNode<T>* m_root;

 public:
  AVLTree();
  ~AVLTree();
  void destroy();
  void print();
  void insert(T key);
  void remove(T key);

  int height();
  T minimum() const;
  T maximum() const;
  AVLTreeNode<T>* searchRec(T key) const;
  AVLTreeNode<T>* search(T key) const;

  typedef void(*funtype)(const T&);
  void preOrder(funtype Visit) const;
  void inOrder(funtype Visit) const;
  void postOrder(funtype Visit) const;
  
 private:
  void destroy(AVLTreeNode<T>* & tree);
  void print(AVLTreeNode<T>* tree, T key, int direction);

  AVLTreeNode<T>* insert(T key, AVLTreeNode<T>* & tree);
  AVLTreeNode<T>* remove(AVLTreeNode<T>* pnode, AVLTreeNode<T>* & tree);

  int height(AVLTreeNode<T>* tree);
  AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree) const;
  AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree) const;

  AVLTreeNode<T>* searchRec(T key, AVLTreeNode<T>* tree) const;
  AVLTreeNode<T>* search(T key, AVLTreeNode<T>* tree) const;

  void preOrder(funtype Visit, AVLTreeNode<T>* tree) const;
  void inOrder(funtype Visit, AVLTreeNode<T>* tree) const;
  void postOrder(funtype Visit, AVLTreeNode<T>* tree) const;

  int max(int a, int b);
  AVLTreeNode<T>* Rotate_LL(AVLTreeNode<T>* k2);
  AVLTreeNode<T>* Rotate_RR(AVLTreeNode<T>* k1);
  AVLTreeNode<T>* Rotate_LR(AVLTreeNode<T>* k3);
  AVLTreeNode<T>* Rotate_RL(AVLTreeNode<T>* k1);

};

template<typename T>
AVLTree<T>::AVLTree() : m_root(nullptr) {  }

template<typename T>
AVLTree<T>::~AVLTree() {
  destroy(m_root);
}

template<typename T>
void AVLTree<T>::destroy(AVLTreeNode<T>* & tree) {
  if (nullptr == tree) return;

  if (tree->left != nullptr) {
    destroy(tree->left);
  } 
  if (tree->right != nullptr) {
    destroy(tree->right);
  }
  delete tree;
  tree = nullptr;
}

template<typename T>
void AVLTree<T>::destroy() {
  destroy(m_root);
}

template<typename T>
void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction) {
  if (tree != nullptr) {
    if (direction == 0) {
      cout << setw(2) << tree->key << " is root." << endl;
    } else {
      cout << setw(2) << tree->key << " is " << setw(2) << key << "'s "
           << setw(12) << (direction == 1 ? "right child" : "left child")
           << endl;
    }
    print(tree->left, tree->key, -1);
    print(tree->right, tree->key, 1);
  }
}

template<typename T>
void AVLTree<T>::print() {
  if (m_root != nullptr) {
    print(m_root, m_root->key, 0);
  }
}

// Return the root pointer of the modified AVLTree 
template<typename T>
AVLTreeNode<T>* AVLTree<T>::insert(T key, AVLTreeNode<T>* & tree) {
  if (nullptr == tree) {
    try {
      tree = new AVLTreeNode<T>(key, nullptr, nullptr);
    } catch (std::bad_alloc&) {
      return nullptr;
    }
  } else if (key < tree->key) {  // Insert into left subtree
    tree->left = insert(key, tree->left);
    if (height(tree->left) - height(tree->right) == 2) {
      if (key < tree->left->key) {
        tree = Rotate_LL(tree);
      } else {
        tree = Rotate_LR(tree);
      }
    }
  } else if (key > tree->key) {  // Insert into right subtree
    tree->right = insert(key, tree->right);
    if (height(tree->right) - height(tree->left) == 2) {
      if (key > tree->right->key) {
        tree = Rotate_RR(tree);
      } else {
        tree = Rotate_RL(tree);
      }
    }
  } else {
    assert(tree->key != key); 
  }
  tree->height = max(height(tree->left), height(tree->right)) + 1;
  return tree;
}

template<typename T>
void AVLTree<T>::insert(T key) {
  m_root = insert(key, m_root);
}

// Return the root pointer of the modified AVLTree
template<typename T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* pnode,
                                   AVLTreeNode<T>* & tree) {
  if (nullptr == tree || nullptr == pnode) {
    return nullptr;
  }
  if (pnode->key < tree->key) {  // Target at left subtree
    tree->left =  remove(pnode, tree->left);
    if (height(tree->right) - height(tree->left) == 2) {
      AVLTreeNode<T>* r = tree->right;
      if (height(r->left) > height(r->right)) {
        tree = Rotate_RL(tree);
      } else {
        tree = Rotate_RR(tree);
      }
    }
  } else if (pnode->key > tree->key) {  // Target at right subtree
    tree->right = remove(pnode, tree->right);
    if (height(tree->left) - height(tree->right) == 2) {
      AVLTreeNode<T>* l = tree->left;
      if (height(l->right) > height(l->left)) {
        tree = Rotate_LR(tree);
      } else {
        tree = Rotate_LL(tree);
      }
    }
  } else {  // Target at root
    if ( (tree->left != nullptr) && ((tree->right) != nullptr) ) {//Two children
      if (height(tree->left) > height(tree->right)) {
        AVLTreeNode<T>* max = maximum(tree->left);
        tree->key = max->key;
        tree->left = remove(max, tree->left);
      } else {
        AVLTreeNode<T>* min = minimum(tree->right);
        tree->key = min->key;
        tree->right = remove(min, tree->right);
      } 
    } else {  // One children or none
      AVLTreeNode<T>* tmp = tree;
      tree = (tree->left != nullptr) ? tree->left : tree->right; 
      delete tmp;
      tmp = nullptr;
    }
  }
  return tree;
} 

template<typename T>
void AVLTree<T>::remove(T key) {
  AVLTreeNode<T>* pnode = search(key, m_root);
  if (pnode != nullptr) {
    m_root = remove(pnode, m_root);
  } 
}

template<typename T>
int AVLTree<T>::height(AVLTreeNode<T>* tree) {
  if (tree != nullptr) {
    return tree->height;
  }
  return 0;
}

template<typename T>
int AVLTree<T>::height() {
  return height(m_root);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree) const {
  if (nullptr == tree) return nullptr;

  while (tree->left != nullptr) {
    tree = tree->left;
  }
  return tree;
}

template<typename T>
T AVLTree<T>::minimum() const {
  AVLTreeNode<T>* p = minimum(m_root);
  if (p != nullptr) {
    return p->key;
  }
  return T();  // Not sure
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree) const {
  if (nullptr == tree) return nullptr;

  while (tree->right != nullptr) {
    tree = tree->right;
  }
  return tree;
}

template<typename T>
T AVLTree<T>::maximum() const {
  AVLTreeNode<T>* p = maximum(m_root);
  if (p != nullptr) {
    return p->key;
  }
  return T();
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::searchRec(T key, AVLTreeNode<T>* tree) const {
  if (nullptr == tree || tree->key == key) return tree;

  if (key < tree->key) {
    return searchRec(tree->left, key); 
  } else {
    return searchRec(tree->right, key);
  } 
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::searchRec(T key) const {
  return searchRec(key, m_root);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::search(T key, AVLTreeNode<T>* tree) const {
  while ( (tree != nullptr) && (tree->key != key) ) {
    if (key < tree->key) {
      tree = tree->left;
    } else {
      tree = tree->right;
    }
  }
  return tree;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::search(T key) const {
  return search(key, m_root);
}

template<typename T>
void AVLTree<T>::preOrder(funtype Visit, AVLTreeNode<T>* tree) const {
  if (tree != nullptr) {
    Visit(tree->key);
    preOrder(Visit, tree->left);
    preOrder(Visit, tree->right);
  }
}

template<typename T>
void AVLTree<T>::preOrder(funtype Visit) const {
  preOrder(Visit, m_root);
}

template<typename T>
void AVLTree<T>::inOrder(funtype Visit, AVLTreeNode<T>* tree) const {
  if (tree != nullptr) {
    inOrder(Visit, tree->left);
    Visit(tree->key);
    inOrder(Visit, tree->right);
  }
}

template<typename T>
void AVLTree<T>::inOrder(funtype Visit) const {
  inOrder(Visit, m_root);
}

template<typename T>
void AVLTree<T>::postOrder(funtype Visit, AVLTreeNode<T>* tree) const {
  if (tree != nullptr) {
    postOrder(Visit, tree->left);
    postOrder(Visit, tree->right);
    Visit(tree->key);
  }
}

template<typename T>
void AVLTree<T>::postOrder(funtype Visit) const {
  postOrder(Visit, m_root);
}


template<typename T>
int AVLTree<T>::max(int a, int b) {
  return a > b ? a : b;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::Rotate_LL(AVLTreeNode<T>* k2) {
  AVLTreeNode<T>* k1;
  k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;

  k2->height = max(height(k2->left), height(k2->right)) + 1;
  k1->height = max(height(k1->left), k2->height) + 1;

  return k1;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::Rotate_RR(AVLTreeNode<T>* k1) {
  AVLTreeNode<T>* k2;
  k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;

  k1->height = max(height(k1->left), height(k1->right)) + 1;
  k2->height = max(height(k2->right), k1->height) + 1;

  return k2;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::Rotate_LR(AVLTreeNode<T>* k3) {
  k3->left = Rotate_RR(k3->left);
  return Rotate_LL(k3);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::Rotate_RL(AVLTreeNode<T>* k1) {
  k1->right = Rotate_LL(k1->right);
  return Rotate_RR(k1);
}

#endif  // __AVL_TREE_H__
