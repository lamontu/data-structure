/* BinarySearchTree.h */

#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include "binarytree.h"

template<typename T>
class BSTree : public BinaryTree<T> {
 public:
  BSTree(BTNode<T>* p=nullptr) : BinaryTree<T>(p) {  }
  BTNode<T>* Find(const T& data) const;
  BTNode<T>* FindMin() const;
  BTNode<T>* FindMax() const;
  virtual BTNode<T>* Insert(const T& data); 
  virtual BTNode<T>* Delete(const T& data); 

 private:
  BTNode<T>* _Find(const T& data, BTNode<T>* p) const;
  BTNode<T>* _FindMin(BTNode<T>* p) const;
  BTNode<T>* _FindMax(BTNode<T>* p) const;
  virtual BTNode<T>* _Insert(const T& data, BTNode<T>* & p);
  virtual BTNode<T>* _Delete(const T& data, BTNode<T>* p);
};


template<typename T>
BTNode<T>* BSTree<T>::Find(const T& data) const {
  // return _Find(data, m_root);  // Error
  return _Find(data, this->m_root);
}

template<typename T>
BTNode<T>* BSTree<T>::FindMin() const {
  return _FindMin(this->m_root);
}

template<typename T>
BTNode<T>* BSTree<T>::FindMax() const {
  return _FindMax(this->m_root);
}

template<typename T>
BTNode<T>* BSTree<T>::Insert(const T& data) {
  return _Insert(data, this->m_root);
}

template<typename T>
BTNode<T>* BSTree<T>::Delete(const T& data) {
  return _Delete(data, this->m_root);
}

template<typename T>
BTNode<T>* BSTree<T>::_Find(const T& data, BTNode<T>* p) const {
  if (nullptr == p) return nullptr;
  if (data < p->data) {
    return _Find(data, p->lchild); 
  } else if (data > p->data) {
    return _Find(data, p->rchild);
  } else {
    return p;
  }
}

template<typename T>
BTNode<T>* BSTree<T>::_FindMin(BTNode<T>* p) const {
  if (nullptr == p) {
    return nullptr;
  } else if (nullptr == p->lchild) {
    return p;
  } else {
    return _FindMin(p->lchild);
  }
}

template<typename T>
BTNode<T>* BSTree<T>::_FindMax(BTNode<T>* p) const {
  if (nullptr == p) {
    return nullptr;
  } else if (nullptr == p->rchild) {
    return p;
  } else {
    return _FindMax(p->rchild);
  }
}

template<typename T>
BTNode<T>* BSTree<T>::_Insert(const T& data, BTNode<T>* & p) {  // By reference
  if (nullptr == p) {  // Stop condition
    try {
      p = new BTNode<T>;
    } catch (std::bad_alloc&) {
      return nullptr;
    }
    p->data = data;
    p->lchild = nullptr;
    p->rchild = nullptr;
    if (nullptr == this->m_root) {
      this->m_root = p;
    }
  } else if (data < p->data) {
    _Insert(data, p->lchild);
  } else if (data > p->data) {
    _Insert(data, p->rchild);
  }
  return p;
}

template<typename T>
BTNode<T>* BSTree<T>::_Delete(const T& data, BTNode<T>* p) {
  if (nullptr == p) {
    return nullptr;
  } else if (data < p->data) {
    p->lchild = _Delete(data, p->lchild);
  } else if (data > p->data) {
    p->rchild = _Delete(data, p->rchild);
  } else if (p->lchild && p->rchild) {  // Found target node with 2 children
    BTNode<T>* pTmp = _FindMin(p->rchild);  // Replace with the successor node
    p->data = pTmp->data;
    p->rchild = _Delete(p->data, p->rchild);
  } else {  // Found target node with one or zero child
    BTNode<T>* pTmp = p;
    if (nullptr == p->lchild) {
      p = p->rchild;
    } else if (nullptr == p->rchild) {
      p = p->lchild;
    }
    if (pTmp == this->m_root) {
      this->m_root = p;
    }
    delete pTmp;
    pTmp = nullptr;
  }
  return p;
}

#endif  // __BINARY_SEARCH_TREE_H__
