/* BinarySearchTree.h */

#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include "binarytree.h"

template<typename T>
class BSTree : public BinaryTree<T> {
 public:
  explicit BSTree(BTNode<T>* p = nullptr) : BinaryTree<T>(p) {  }
  BTNode<T>* FindRec(const T& data) const;
  BTNode<T>* Find(const T&) const;
  BTNode<T>* FindMin() const;
  BTNode<T>* FindMax() const;
  BTNode<T>* Predecessor(BTNode<T>* p) const;
  BTNode<T>* Successor(BTNode<T>* p) const;
  virtual BTNode<T>* InsertRec(const T& data);
  virtual BTNode<T>* Insert(const T& data);
  virtual BTNode<T>* DeleteRec(const T& data);
  virtual BTNode<T>* Delete(const T& data);

 private:
  BTNode<T>* _FindRec(const T& data, BTNode<T>* p) const;
  BTNode<T>* _Find(const T& data, BTNode<T>* p) const;
  BTNode<T>* _FindMin(BTNode<T>* p) const;
  BTNode<T>* _FindMax(BTNode<T>* p) const;
  virtual BTNode<T>* _InsertRec(const T& data, BTNode<T>* & p);
  virtual BTNode<T>* _DeleteRec(const T& data, BTNode<T>* & p);
};


template<typename T>
BTNode<T>* BSTree<T>::FindRec(const T& data) const {
  // return _FindRec(data, m_root);  // Error
  return _FindRec(data, this->m_root);
}

template<typename T>
BTNode<T>* BSTree<T>::Find(const T& data) const {
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
BTNode<T>* BSTree<T>::InsertRec(const T& data) {
  return _InsertRec(data, this->m_root);
}

// Return the new inserted node
template<typename T>
BTNode<T>* BSTree<T>::Insert(const T& data) {
  BTNode<T>* p = nullptr;

  if (this->m_root == nullptr) {
    try {
      p = new BTNode<T>;
      p->data = data;
      this->m_root = p;
      return p;
    } catch (std::bad_alloc&) {
      return nullptr;
    }
  }

  p = this->m_root;
  while (p != nullptr) {
    if (data > p->data) {
      if (p->rchild == nullptr) {
        p->rchild = new BTNode<T>;
        p->rchild->data = data;
        return p->rchild;
      }
      p = p->rchild;
    } else {
      if (p->lchild == nullptr) {
        p->lchild = new BTNode<T>;
        p->lchild->data = data;
        return p->lchild;
      }
      p = p->lchild;
    }
  }
  
  return p;
}

template<typename T>
BTNode<T>* BSTree<T>::DeleteRec(const T& data) {
  return _DeleteRec(data, this->m_root);
}

// Return the deleted node
template<typename T>
BTNode<T>* BSTree<T>::Delete(const T& data) {
  BTNode<T>* p = this->m_root;  // p point to the target node to be delete.
  BTNode<T>* pp = nullptr;  // pp point to the parent of p.
  while (p != nullptr && p->data != data) {
    pp = p;
    if (data > p->data) {
      p = p->rchild;
    } else {
      p = p->lchild;
    }
  }
  if (p == nullptr) {  // Not found target data
    return p;
  }

  // Transfer the target node with 2 children to a target node with 0 or 1 child
  if (p->lchild != nullptr && p->rchild != nullptr) {
      // Use the minimum node of right subtree to replace the target node
      // Can also use the maximum node of the left subtree to replace the target ndoe
      BTNode<T>* minP = p->rchild;  // minP point the minimum node of the right subtree.
      BTNode<T>* minPP = p;  // minPP point to the parent of minP.
      while (minP->lchild != nullptr) {
        minPP = minP;
        minP = minP->lchild;
      }
      p->data = minP->data;  // Replace target node data with the minP node
      p = minP;  // minP is now the node to be delete with 0 or 1 child.
      pp = minPP;
  }

  // Target node with only 0 or 1 child
  // Find the child of the target ndoe
  BTNode<T>* child = nullptr;
  if (p->lchild != nullptr) {
    child = p->lchild;
  } else if (p->rchild != nullptr) {
    child = p->rchild;
  }

  if (pp == nullptr) {
    this->m_root = child;
  } else if (pp->lchild == p) {
    pp->lchild = child;
  } else {
    pp->rchild = child;
  }

  return p;
}

template<typename T>
BTNode<T>* BSTree<T>::_FindRec(const T& data, BTNode<T>* p) const {
  if (nullptr == p || data == p->data) {
    return p;
  }

  if (data < p->data) {
    return _FindRec(data, p->lchild); 
  } else {
    return _FindRec(data, p->rchild);
  }
}

template<typename T>
BTNode<T>* BSTree<T>::_Find(const T& data, BTNode<T>* p) const {
  while ((p != nullptr) && (data != p->data)) {
    if (data < p->data) {
      p = p->lchild;
    } else {
      p = p->rchild;
    }
  }
  return p;
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
BTNode<T>* BSTree<T>::Predecessor(BTNode<T>* p) const {
  if (p->lchild != nullptr) {
    return _FindMax(p->lchild);
  }
  BTNode<T>* father = this->Parent(p);
  while ((father != nullptr) && (p == father->lchild)) {
    p = father;
    father = this->Parent(father);
  } 
  return father;
}

template<typename T>
BTNode<T>* BSTree<T>::Successor(BTNode<T>* p) const {
  if (p->rchild != nullptr) {
    return _FindMin(p->rchild);
  }
  BTNode<T>* father = this->Parent(p);
  while ((father != nullptr) && (p == father->rchild)) {
    p = father;
    father = this->Parent(father);
  }
  return father;
}



/* Return the new p if p == nullptr
 * Return p if p != nullptr
 */
template<typename T>
BTNode<T>* BSTree<T>::_InsertRec(const T& data, BTNode<T>* & p) {  // By reference
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
    _InsertRec(data, p->lchild);
  } else if (data > p->data) {
    _InsertRec(data, p->rchild);
  }
  /* Else data is in the tree already, we'll do nothing. */
  return p;
}

/* Return p if p->data != data,
 * Return p if p->data == data and p has two children
 * Return lchild or rchild if p->data == data and p has one child
 * Return nullptr if no target data
 */
template<typename T>
BTNode<T>* BSTree<T>::_DeleteRec(const T& data, BTNode<T>* & p) {
  assert(p);

  if (data < p->data) {
    p->lchild = _DeleteRec(data, p->lchild);
  } else if (data > p->data) {
    p->rchild = _DeleteRec(data, p->rchild);
  } else if (p->lchild && p->rchild) {  // Found target node with 2 children
    BTNode<T>* pTmp = _FindMin(p->rchild);  // Replace with the successor node
    p->data = pTmp->data;
    p->rchild = _DeleteRec(p->data, p->rchild);
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
