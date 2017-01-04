/* binarytree.h */

#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__

#include <iostream>
#include <cassert>
#include <new>
#include <stack>
#include <queue>

using namespace std;

template<typename T>
struct BTNode {
  T data;
  BTNode<T>* lchild;
  BTNode<T>* rchild;
  BTNode(T data=T(), BTNode<T>* lchild=nullptr, BTNode<T>* rchild=nullptr)
    : data(data), lchild(lchild), rchild(rchild) {  }
};

template<typename T>
class BinaryTree {
 public:
  BinaryTree(BTNode<T>* init_root=nullptr);
  BinaryTree(const BinaryTree<T>& rhs);
  BinaryTree<T>& operator=(const BinaryTree<T>& rhs);
  ~BinaryTree();

  void Create1(T ch[], int n, const T& endChar);
  void Create2(T ch1[], T ch2[], int n);
  void Clear();
  bool IsEmpty() const;

  /* select, update, attach, detach */

  BTNode<T>* Root() const;
  BTNode<T>* LeftChild() const;
  BTNode<T>* RightChild() const;
  BTNode<T>* Locate(const T& e) const;
  BTNode<T>* Parent(const BTNode<T>* pnode) const;
  BTNode<T>* LeftSibling(const BTNode<T>* pnode) const;
  BTNode<T>* RightSibling(const BTNode<T>* pnode) const;
  void SetLeft(BTNode<T>* pnode);
  void SetRight(BTNode<T>* pnode);
  bool AttachLeft(BTNode<T>* p);
  bool AttachRight(BTNode<T>* p);
  BTNode<T>* DetachLeft();
  BTNode<T>* DetachRight();

  unsigned int NodesCount() const;
  unsigned int LeafCount() const;
  unsigned int Depth() const;

  typedef void(* funtype)(const T&);
  void PreOrderTraverseRec(funtype Visit) const;
  void InOrderTraverseRec(funtype Visit) const;
  void PostOrderTraverseRec(funtype Visit) const;
  void PreOrderTraverse(funtype Visit) const;
  void InOrderTraverse(funtype Visit) const;
  void PostOrderTraverse(funtype Visit) const;
  void LevelOrderTraverse(funtype Visit) const;

 protected:
  BTNode<T>* m_root;

 private:
  BTNode<T>* _Copy(BTNode<T>* pnode);
  void _Create1(BTNode<T>*& tree, T ch[], int n, const T& c, int i);
  void _Create2(BTNode<T>*& tree, T ch1[], T ch2[], int low, int high, int& k);
  void _Destroy(BTNode<T>*& tree);
  
  void _NodesCount(const BTNode<T>* pnode, unsigned int& unCount) const;
  void _LeafCount(const BTNode<T>* pnode, unsigned int& unCount) const;
  void _Depth(const BTNode<T>* pnode, unsigned int& unCount) const;

  BTNode<T>* _Locate(BTNode<T>* pnode, const T& elem) const;
  BTNode<T>* _Parent(BTNode<T>* proot, const BTNode<T>* pnode) const;

  void PreOrderTraverseRec(const BTNode<T>* p, funtype Visit) const;
  void InOrderTraverseRec(const BTNode<T>* p, funtype Visit) const;
  void PostOrderTraverseRec(const BTNode<T>* p, funtype Visit) const;
  void PreOrderTraverse(BTNode<T>* p, funtype Visit) const;
  void InOrderTraverse(BTNode<T>* p, funtype Visit) const;
  void PostOrderTraverse(BTNode<T>* p, funtype Visit) const;
  void LevelOrderTraverse(BTNode<T>* p, funtype Visit) const;
};


template<typename T>
BinaryTree<T>::BinaryTree(BTNode<T>* init_root) : m_root(init_root) {
  cout << "Constructor started." << endl;
  cout << "Constructor finished." << endl;
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& rhs) : m_root(nullptr) {
  cout << "Copy constructor started." << endl;
  m_root = _Copy(rhs.m_root);
  cout << "Copy constructor finished." << endl;
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& rhs) {
  cout << "Copy assignment started." << endl;
  if (&rhs == this) return *this;
  _Destroy(m_root);
  m_root = _Copy(rhs.m_root);
  cout << "Copy assignment finished." << endl;
  return *this;
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
  cout << "Destructor started." << endl;
  _Destroy(m_root);
  cout << "Destructor finished." << endl;
}

template<typename T>
void BinaryTree<T>::Create1(T ch[], int n, const T& c) {
  int i = 0;
  _Create1(m_root, ch, n, c, i);
}

template<typename T>
void BinaryTree<T>::Create2(T ch1[], T ch2[], int n) {
  int i = 0;
  _Create2(m_root, ch1, ch2, 0, n - 1, i);
}

template<typename T>
void BinaryTree<T>::Clear() {
  _Destroy(m_root);
}

template<typename T>
bool BinaryTree<T>::IsEmpty() const {
  return nullptr == m_root;
}

template<typename T>
BTNode<T>* BinaryTree<T>::Root() const {
  return m_root;
}

template<typename T>
BTNode<T>* BinaryTree<T>::LeftChild() const {
  assert(m_root);
  return m_root->lchild;
}

template<typename T>
BTNode<T>* BinaryTree<T>::RightChild() const {
  assert(m_root);
  return m_root->rchild;
}

template<typename T>
BTNode<T>* BinaryTree<T>::Locate(const T& elem) const {
  return _Locate(m_root, elem);
}

template<typename T>
BTNode<T>* BinaryTree<T>::Parent(const BTNode<T>* pnode) const {
  return _Parent(m_root, pnode);
}

template<typename T>
BTNode<T>* BinaryTree<T>::LeftSibling(const BTNode<T>* pnode) const {
  assert(pnode);
  BTNode<T>* father;
  father = Parent(pnode);
  if (father != nullptr) {
    assert(father->lchild != pnode);
    if (father->rchild == pnode) {
      return father->lchild;
    }
  }
  return nullptr;
}

template<typename T>
BTNode<T>* BinaryTree<T>::RightSibling(const BTNode<T>* pnode) const {
  assert(pnode);
  BTNode<T>* father;
  father = Parent(pnode);
  if (father != nullptr) { 
    assert(father->rchild != pnode);
    if (father->lchild == pnode) {
      return father->rchild;
    }
  }
  return nullptr;
}

template<typename T>
void BinaryTree<T>::SetLeft(BTNode<T>* pnode) {
  if (nullptr == m_root) return;
  BTNode<T>* old_left = LeftChild();
  _Destroy(old_left);
  m_root->lchild = pnode; 
}

template<typename T>
void BinaryTree<T>::SetRight(BTNode<T>* pnode) {
  if (nullptr == m_root) return;
  BTNode<T>* old_right = RightChild();
  _Destroy(old_right);
  m_root->rchild = pnode; 
}

template<typename T>
bool BinaryTree<T>::AttachLeft(BTNode<T>* pnode) {
  if (pnode == this->Root() || IsEmpty() || LeftChild()) return false;
  m_root->lchild = pnode;
  pnode = nullptr;  // Forbid access to the tree below the root node
  return true;
}

template<typename T>
bool BinaryTree<T>::AttachRight(BTNode<T>* pnode) {
  if (pnode == this->Root() || IsEmpty() || RightChild()) return false;
  m_root->rchild = pnode;
  pnode = nullptr;
  return true;
}

template<typename T>
BTNode<T>* BinaryTree<T>::DetachLeft() {
  assert(m_root);
  BTNode<T>* left = LeftChild();
  m_root->lchild = nullptr;
  return left;
}

template<typename T>
BTNode<T>* BinaryTree<T>::DetachRight() {
  assert(m_root);
  BTNode<T>* right = RightChild();
  m_root->rchild = nullptr;
  return right;
}


template<typename T>
unsigned int BinaryTree<T>::NodesCount() const {
  unsigned int unCount;
  _NodesCount(m_root, unCount);
  return unCount;
}

template<typename T>
unsigned int BinaryTree<T>::LeafCount() const {
  unsigned int unCount = 0;
  _LeafCount(m_root, unCount);
  return unCount; 
}

template<typename T>
unsigned int BinaryTree<T>::Depth() const {
  unsigned int unCount;
  _Depth(m_root, unCount);
  return unCount;
}

/* Traverse using recursion */

template<typename T>
void BinaryTree<T>::PreOrderTraverseRec(funtype Visit) const {
  PreOrderTraverseRec(m_root, Visit);
}

template<typename T>
void BinaryTree<T>::InOrderTraverseRec(funtype Visit) const {
  InOrderTraverseRec(m_root, Visit);
}

template<typename T>
void BinaryTree<T>::PostOrderTraverseRec(funtype Visit) const {
  PostOrderTraverseRec(m_root, Visit);
}

/* Traverse without using recursion */

template<typename T>
void BinaryTree<T>::PreOrderTraverse(funtype Visit) const {
  PreOrderTraverse(m_root, Visit);
}

template<typename T>
void BinaryTree<T>::InOrderTraverse(funtype Visit) const {
  InOrderTraverse(m_root, Visit);
}

template<typename T>
void BinaryTree<T>::PostOrderTraverse(funtype Visit) const {
  PostOrderTraverse(m_root, Visit);
}

template<typename T>
void BinaryTree<T>::LevelOrderTraverse(funtype Visit) const {
  LevelOrderTraverse(m_root, Visit);
}


/* Private Member functions */

template<typename T>
BTNode<T>* BinaryTree<T>::_Copy(BTNode<T>* pnode) {
  cout << "  _Copy begin" << endl;
  if (pnode) {
    BTNode<T>* pNewNode;
    try {
      pNewNode = new BTNode<T>;
    } catch(std::bad_alloc&) {
      return nullptr; 
    }
    pNewNode->data = pnode->data;
    pNewNode->lchild = _Copy(pnode->lchild);
    pNewNode->rchild = _Copy(pnode->rchild);
    cout << "  _Copy end" << endl;
    return pNewNode;
  }
  cout << "  _Copy end" << endl;
  return nullptr;
/*
  if (nullptr == pnode) return nullptr;
  BTNode<T>* pNewNode;
  pNewNode = new BTNode<T>;
  pNewNode->data = pnode->data;
  pNewNode->lchild = _Copy(pnode->lchild); 
  pNewNode->rchild = _Copy(pnode->rchild); 
  return pNewNode;
*/
}

template<typename T>
void BinaryTree<T>::_Destroy(BTNode<T>*& tree) {
  cout << "  _Destroy begin" << endl;
  if (tree != nullptr) {
    _Destroy(tree->lchild);
    _Destroy(tree->rchild);
    delete tree;
    tree = nullptr;  // This is necessary.
  }
  cout << "  _Destroy end" << endl;
}

// Create from LevelOrderTraverse
template<typename T>
void BinaryTree<T>::_Create1(BTNode<T>* & tree,
                             T ch[], int n, const T& c, int i) {
  if (i >= n || i < 0) return;
  if (ch[i] == c) {
    tree = nullptr;
  } else {
    tree = new BTNode<T>;
    tree->data = ch[i];
    _Create1(tree->lchild, ch, n, c, 2 * i + 1);
    _Create1(tree->rchild, ch, n, c, 2 * i + 2);
  }
}

// Create from PreOrderTraverse and InOrderTraverse
template<typename T>
void BinaryTree<T>::_Create2(BTNode<T>*& tree, T ch1[], T ch2[],
                             int low, int high, int& k) {
  int i;
  if (low > high) {
    tree = nullptr;
  } else {
    tree = new BTNode<T>;
    tree->data = ch1[k];
    for (i = low; i <= high && ch2[i] != ch1[k]; ++i);
    if (ch2[i] == ch1[k]) {
      ++k;
      _Create2(tree->lchild, ch1, ch2, low, i - 1, k);
      _Create2(tree->rchild, ch1, ch2, i + 1, high, k);
    }
  }
}

template<typename T>
BTNode<T>* BinaryTree<T>::_Locate(BTNode<T>* pnode,
                                  const T& elem) const {
  if (nullptr == pnode || pnode->data == elem) return pnode;
  BTNode<T>* q;
  q = _Locate(pnode->lchild, elem);
  if (q) {
    return q;
  }
  q = _Locate(pnode->rchild, elem);
  return q;
}

template<typename T>
BTNode<T>* BinaryTree<T>::_Parent(BTNode<T>* root,
                                  const BTNode<T>* pnode) const {
  if (root == nullptr || root == pnode) {
    return nullptr; 
  }
  if (root->lchild == pnode || root->rchild == pnode) {
    return root;
  }
  BTNode<T>* q;
  q = _Parent(root->lchild, pnode);
  if (q) {
    return q;
  }
  q = _Parent(root->rchild, pnode);
  if (q) {
    return q;
  }
  return nullptr;
}

template<typename T>
void BinaryTree<T>::_NodesCount(const BTNode<T>* pnode,
                                unsigned int& unCount) const {
  unsigned int unLeft, unRight;
  if (nullptr == pnode) {
    unCount = 0;
  } else if ((nullptr == pnode->lchild) && (nullptr == pnode->rchild)) {
    unCount = 1;
  } else {
    _NodesCount(pnode->lchild, unLeft);
    _NodesCount(pnode->rchild, unRight);
    unCount = 1 + unLeft + unRight;
  }
}

template<typename T>
void BinaryTree<T>::_LeafCount(const BTNode<T>* pnode,
                               unsigned int& unCount) const {
  if (pnode) {
    if ((nullptr == pnode->lchild) && (nullptr == pnode->rchild)) {
      ++unCount;
    }
    _LeafCount(pnode->lchild, unCount);
    _LeafCount(pnode->rchild, unCount);
  }
}

template<typename T>
void BinaryTree<T>::_Depth(const BTNode<T>* pnode,
                           unsigned int& unCount) const {
  unCount = 0;
  if (nullptr == pnode) return;
  unsigned int h1, h2;
  _Depth(pnode->lchild, h1);
  _Depth(pnode->rchild, h2);
  unCount = 1 + (h1 > h2 ? h1 : h2);
  return;
}

template<typename T>
void BinaryTree<T>::PreOrderTraverseRec(const BTNode<T>* pnode,
                                        funtype Visit) const {
  if (nullptr == pnode) return;
  Visit(pnode->data);
  PreOrderTraverseRec(pnode->lchild, Visit);
  PreOrderTraverseRec(pnode->rchild, Visit);
}

template<typename T>
void BinaryTree<T>::InOrderTraverseRec(const BTNode<T>* pnode,
                                        funtype Visit) const {
  if (nullptr == pnode) return;
  InOrderTraverseRec(pnode->lchild, Visit);
  Visit(pnode->data);
  InOrderTraverseRec(pnode->rchild, Visit);
}

template<typename T>
void BinaryTree<T>::PostOrderTraverseRec(const BTNode<T>* pnode,
                                        funtype Visit) const {
  if (nullptr == pnode) return;
  PostOrderTraverseRec(pnode->lchild, Visit);
  PostOrderTraverseRec(pnode->rchild, Visit);
  Visit(pnode->data);
}

template<typename T>
void BinaryTree<T>::PreOrderTraverse(BTNode<T>* pnode,
                                     funtype Visit) const {
  stack<BTNode<T>*> S;
  BTNode<T>* p = pnode; 
  while (p != nullptr || !S.empty()) {
    while (p != nullptr) {
      Visit(p->data);  // Position difference from InOrderTraverse
      S.push(p);
      p = p->lchild;
    }
    if (!S.empty()) {
      p = S.top();
      S.pop();
      p = p->rchild;
    }
  }
}

template<typename T>
void BinaryTree<T>::InOrderTraverse(BTNode<T>* pnode,
                                    funtype Visit) const {
  stack<BTNode<T>*> S;
  BTNode<T>* p = pnode;
  while (p != nullptr || !S.empty()) {
    while (p != nullptr) {
      S.push(p);
      p = p->lchild;
    }
    if (!S.empty()) {
      p = S.top();
      Visit(p->data);  // Position difference from PreOrderTraverse 
      S.pop();
      p = p->rchild;
    }
  }
}

template<typename T>
void BinaryTree<T>::PostOrderTraverse(BTNode<T>* pnode,
                                      funtype Visit) const {
  stack<BTNode<T>*> S;
  BTNode<T>* curr = pnode;
  BTNode<T>* prev = nullptr;
  while (curr != nullptr || !S.empty()) {
    while (curr != nullptr) {
      S.push(curr);
      curr = curr->lchild;
    }
    curr = S.top();
    if (curr->rchild == nullptr || curr->rchild == prev) {
      Visit(curr->data);
      prev = curr;
      S.pop();
      curr = nullptr;
    } else {
      curr = curr->rchild;
    }
  }
}

template<typename T>
void BinaryTree<T>::LevelOrderTraverse(BTNode<T>* pnode,
                                  funtype Visit) const {
  queue<BTNode<T>*> Q;
  if (pnode != nullptr) Q.push(pnode);
  while (!Q.empty()) {
    BTNode<T>* p;
    p = Q.front();
    Visit(p->data);
    Q.pop();
    if (p->lchild != nullptr) {
      Q.push(p->lchild);
    }
    if (p->rchild != nullptr) {
      Q.push(p->rchild);
    }
  }    
}

#endif  // __BINARYTREE_H__
