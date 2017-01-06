/* splaytree.h */

#ifndef __SPLAY_TREE_H__
#define __SPLAY_TREE_H__

#include <iostream> 
#include <iomanip>

using namespace std;

template<typename T>
class SplayTreeNode {
 public:
  T key;
  SplayTreeNode<T>* left;
  SplayTreeNode<T>* right;

  SplayTreeNode() : left(nullptr), right(nullptr) {  }
  SplayTreeNode(T value, SplayTreeNode* l, SplayTreeNode* r)
    : key(value), left(l), right(r) {  }
};

template<typename T>
class SplayTree {
 private:
  SplayTreeNode<T>* m_root;

 public:
  SplayTree();
  ~SplayTree();
  void destroy();
  void print();
  void splay(T key);
  void insert(T key);
  void remove(T key);

  T minimum() const;
  T maximum() const;
  SplayTreeNode<T>* searchRec(T key) const;
  SplayTreeNode<T>* search(T key) const;

  typedef void(*funtype)(const T&);
  void preOrder(funtype Visit) const;
  void inOrder(funtype Visit) const;
  void postOrder(funtype Visit) const;

 private:
  void destroy(SplayTreeNode<T>* & tree);
  void print(SplayTreeNode<T>* tree, T key, int direction);
  SplayTreeNode<T>* splay(T key, SplayTreeNode<T>* tree);
  SplayTreeNode<T>* insert(SplayTreeNode<T>* pnode, SplayTreeNode<T>* & tree);
  SplayTreeNode<T>* remove(T key, SplayTreeNode<T>* & tree);

  SplayTreeNode<T>* minimum(SplayTreeNode<T>* tree) const;
  SplayTreeNode<T>* maximum(SplayTreeNode<T>* tree) const;
  SplayTreeNode<T>* searchRec(T key, SplayTreeNode<T>* tree) const;
  SplayTreeNode<T>* search(T key, SplayTreeNode<T>* tree) const;
  void preOrder(funtype Visit, SplayTreeNode<T>* tree) const;
  void inOrder(funtype Visit, SplayTreeNode<T>* tree) const;
  void postOrder(funtype Visit, SplayTreeNode<T>* tree) const;
};

template<typename T>
SplayTree<T>::SplayTree() : m_root(nullptr) {  
  cout << "Inside Constructor" << endl;
}

template<typename T>
SplayTree<T>::~SplayTree() {
  cout << "Inside Destructor" << endl;
  destroy(m_root);
}

template<typename T>
void SplayTree<T>::destroy(SplayTreeNode<T>* & tree) {
  cout << "  inside destroy" << endl;
  if (nullptr == tree) {
    return;
  }
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
void SplayTree<T>::destroy() {
  destroy(m_root);
}

template<typename T>
void SplayTree<T>::print(SplayTreeNode<T>* tree, T key, int direction) {
  if (tree != nullptr) {
    if (direction == 0) {
      cout << setw(2) << tree->key << " is root." << endl;
    } else {
      cout << setw(2) << tree->key << " is " << setw(2) << key << "'s " <<
        setw(12) << (direction == 1 ? "right child" : "left child") << endl;
    }
    print(tree->left, tree->key, -1);
    print(tree->right, tree->key, 1);
  }
}

template<typename T>
void SplayTree<T>::print() {
  if (m_root != nullptr) {
    print(m_root, m_root->key, 0);
  }
}

/* Top-down splay
 * If key node exists, rotate it as root.
 * If key node does not exist and key < root->key:
     If key's predecessor exists, rotate predecessor as root.
     If no key's predecessor, rotate the minimum as root.
 * If key node does not exist and key > root->key:
     If key's successor exists, rotate successor as root.
     If no key's successor, rotate the maximum as root.
 */
template<typename T>
SplayTreeNode<T>* SplayTree<T>::splay(T key, SplayTreeNode<T>* tree) {
  SplayTreeNode<T> N, *l, *r, *c;

  if (nullptr == tree) {
    return tree;
  }

  N.left = N.right = nullptr;
  l = r = &N;

  for (;;) {
    if (key < tree->key) {
      if (nullptr == tree->left) break;
      if (key < tree->left->key) {
        c = tree->left;
        tree->left = c->right;
        c->right = tree;
        tree = c;
        if (nullptr == tree->left) break;
      }
      r->left = tree;
      r = tree;
      tree = tree->left;
    } else if (key > tree->key) {
      if (nullptr == tree->right) break;
      if (key > tree->right->key) {
        c = tree->right;
        tree->right = c->left;
        c->left = tree;
        tree = c;
        if (nullptr == tree->right) break;
      }
      l->right = tree;
      l = tree;
      tree = tree->right;
    } else {
      break;
    }
  }
  l->right = tree->left;
  r->left = tree->right;
  tree->left = N.right;
  tree->right = N.left;

  return tree;
}

template<typename T>
void SplayTree<T>::splay(T key) {
  m_root = splay(key, m_root);
}

template<typename T>
SplayTreeNode<T>* SplayTree<T>::insert(SplayTreeNode<T>* pnode,
                                       SplayTreeNode<T>* & tree) {
  SplayTreeNode<T>* y = nullptr;
  SplayTreeNode<T>* x = tree;

  while (x != nullptr) {
    y = x;
    if (pnode->key < x->key) {
      x = x->left;
    } else if (pnode->key > x->key) {
      x = x->right;
    } else {
      cout << "Can not insert a duplicated node." << endl;
      delete pnode;
      return tree;
    }
  }
  if (nullptr == y) {
    tree = pnode;
  } else if (pnode->key < y->key) {
    y->left = pnode;
  } else {
    y->right = pnode;
  }
  return tree;
}

template<typename T>
void SplayTree<T>::insert(T key) {
  SplayTreeNode<T>* pnode = nullptr;
  try {
    pnode = new SplayTreeNode<T>(key, nullptr, nullptr);
  } catch (std::bad_alloc&) {
    return;
  }
  m_root = insert(pnode, m_root);
  m_root = splay(key, m_root);
}

template<typename T>
SplayTreeNode<T>* SplayTree<T>::remove(T key, SplayTreeNode<T>* &tree) {
  SplayTreeNode<T>* x;
  if (nullptr == tree) {
    return nullptr;
  }
  if (search(key, tree) == nullptr) {
    return tree;
  }

  tree = splay(key, tree);
  if (tree->left != nullptr) {
    x = splay(key, tree->left);
    x->right = tree->right;
  } else {
    x = tree->right;
  }
  delete tree;
  tree = nullptr;
  return x;
}

template<typename T>
void SplayTree<T>::remove(T key) {
  m_root = remove(key, m_root);
}

template<typename T>
SplayTreeNode<T>* SplayTree<T>::minimum(SplayTreeNode<T>* tree) const {
  if (nullptr == tree) {
    return nullptr;
  }
  while (tree->left != nullptr) {
    tree = tree->left;
  }
  return tree;
}

template<typename T>
T SplayTree<T>::minimum() const {
  SplayTreeNode<T>* p = minimum(m_root);
  if (p != nullptr) {
    return p->key;
  }
  return T();
}

template<typename T>
SplayTreeNode<T>* SplayTree<T>::maximum(SplayTreeNode<T>* tree) const {
  if (nullptr == tree) {
    return nullptr;
  }
  while (tree->right != nullptr) {
    tree = tree->right;
  }
  return tree;
}

template<typename T>
T SplayTree<T>::maximum() const {
  SplayTreeNode<T>* p = maximum(m_root);
  if (p != nullptr) {
    return p->key;
  }
  return T();
}

template<typename T>
SplayTreeNode<T>* SplayTree<T>::searchRec(T key, SplayTreeNode<T>* tree) const {
  if (nullptr == tree || key == tree->key) {
    return tree;
  }
  if (key < tree->key) {
    return searchRec(key, tree->left);
  } else {
    return searchRec(key, tree->right);
  }
}

template<typename T>
SplayTreeNode<T>* SplayTree<T>::searchRec(T key) const {
  return searchRec(key, m_root);
}

template<typename T>
SplayTreeNode<T>* SplayTree<T>::search(T key, SplayTreeNode<T>* tree) const {
  while ( (tree != nullptr) && (key != tree->key) ) {
    if (key < tree->key) {
      tree = tree->left;
    } else {
      tree = tree->right;
    }
  }
  return tree;
}

template<typename T>
SplayTreeNode<T>* SplayTree<T>::search(T key) const {
  return search(key, m_root);
}

template<typename T>
void SplayTree<T>::preOrder(funtype Visit, SplayTreeNode<T>* tree) const {
  if (tree != nullptr) {
    Visit(tree->key);
    preOrder(Visit, tree->left);
    preOrder(Visit, tree->right);
  }
}

template<typename T>
void SplayTree<T>::preOrder(funtype Visit) const {
  preOrder(Visit, m_root);
}

template<typename T>
void SplayTree<T>::inOrder(funtype Visit, SplayTreeNode<T>* tree) const {
  if (tree != nullptr) {
    inOrder(Visit, tree->left);
    Visit(tree->key);
    inOrder(Visit, tree->right);
  }
}

template<typename T>
void SplayTree<T>::inOrder(funtype Visit) const {
  inOrder(Visit, m_root);
}

template<typename T>
void SplayTree<T>::postOrder(funtype Visit, SplayTreeNode<T>* tree) const {
  if (tree != nullptr) {
    postOrder(Visit, tree->left);
    postOrder(Visit, tree->right);
    Visit(tree->key);
  }
}

template<typename T>
void SplayTree<T>::postOrder(funtype Visit) const {
  postOrder(Visit, m_root);
}

#endif  // __SPLAY_TREE_H__
