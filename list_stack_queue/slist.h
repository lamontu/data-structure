/* slist.h
 * No dummy node, all node is data node.
 */

#include <iostream>
#include <cassert>
#include <new>

template<typename T>
class Node {
 public:
  T data;
  Node<T>* next;
  Node() : data(T()), next(nullptr) {  }
  Node(const T& init_data) : data(init_data), next(nullptr) {  } 
  Node(const T& init_data, Node<T>* p) : data(init_data), next(p) {  }
};

template<typename T>
class SList {
 protected:
  int m_nCount;
  Node<T>* m_pNodeHead;
 public:
  SList();
  SList(const T& init_data);
  SList(const SList<T>& other);
  SList<T>& operator=(const SList<T>& other);
  ~SList();
  void Invert();
  int IsEmpty() const;
  int GetCount() const;
  int AddHead(const T data);
  int AddTail(const T data);
  int InsertBefore(const int pos, const T data);
  int InsertAfter(const int pos, const T data);
  void RemoveAt(const int pos);
  void RemoveHead();
  void RemoveTail();
  void RemoveAll();
  T& GetTail();
  T GetTail() const;
  T& GetHead();
  T GetHead() const;
  T& GetAt(const int pos);
  T GetAt(const int pos) const;
  void SetAt(const int pos, T data);
  int Find(const T data) const;
  int FindCircle() const;
  int FindCross(SList& testlist);
};

template<typename T>
inline SList<T>::SList() : m_nCount(0), m_pNodeHead(nullptr) {  }

template<typename T>
inline SList<T>::SList(const T& init_data)
  : m_nCount(0), m_pNodeHead(nullptr) {
  AddHead(init_data);
}

template<typename T>
inline SList<T>::SList(const SList<T>& other)
  : m_nCount(0), m_pNodeHead(nullptr) {
  if (other.m_nCount > 0) {
    for (int i = 1; i <= other.m_nCount; ++i) {
      AddTail(other.GetAt(i));
    }
  }  
}

template<typename T>
inline SList<T>& SList<T>::operator=(const SList<T>& other) {
  if (this == &other) {
    return *this;
  }
  if (m_nCount > 0) {
    RemoveAll();
  }
  if (other.m_nCount > 0) {
    for (int i = 1; i <= other.m_nCount; ++i) {
      AddTail(other.GetAt(i));
    }
  } 
  return *this;
}

template<typename T>
inline SList<T>::~SList() {
  RemoveAll();
}

template<typename T>
inline void SList<T>::Invert() {
  if (m_nCount <= 1) return;
  Node<T> *curNod, *preNod, *nexNod;
  curNod = m_pNodeHead;
  preNod = nullptr;
  for (int i = 1; i <= m_nCount; ++i) {
    nexNod = curNod->next;
    curNod->next = preNod;
    preNod = curNod;
    curNod = nexNod;
  }
  m_pNodeHead = preNod;
  return;
}

template<typename T>
inline int SList<T>::IsEmpty() const {
  return 0 == m_nCount;
}

template<typename T>
inline int SList<T>::GetCount() const {
  return m_nCount;
} 

template<typename T>
inline int SList<T>::AddHead(const T data) {
  return InsertBefore(1, data);
}

template<typename T>
inline int SList<T>::AddTail(const T data) {
  return InsertAfter(GetCount(), data);
}

/* Return the position of the new node if success.
 * Return 0 if fail.
 */
template<typename T>
inline int SList<T>::InsertBefore(const int pos, const T data) {
  int nRetPos; 
  Node<T> *pTmpNode1, *pTmpNode2, *pNewNode;
  try {
    pNewNode = new Node<T>;
  } catch (std::bad_alloc&) {
    nRetPos = 0;
    return nRetPos;
  }
  pNewNode->data = data;

  if (nullptr == m_pNodeHead) {
    pNewNode->next = nullptr;
    m_pNodeHead = pNewNode;
    nRetPos = 1;
    ++m_nCount;
    return nRetPos;
  }

  assert(1 <= pos && pos <= m_nCount);

  if (1 == pos) {
    pNewNode->next = m_pNodeHead;
    m_pNodeHead = pNewNode;
    nRetPos = 1;
    ++m_nCount;
    return nRetPos;
  }

  pTmpNode1 = m_pNodeHead;
  for (int i = 1; i < pos; ++i) {
    pTmpNode2 = pTmpNode1;
    pTmpNode1 = pTmpNode1->next;
  }
  pNewNode->next = pTmpNode1;
  pTmpNode2->next = pNewNode;

  nRetPos = pos;
  ++m_nCount;
  return nRetPos;  
}

/* Return the position of the new node if success.
 * Return 0 if fail.
 */
template<typename T>
inline int SList<T>::InsertAfter(const int pos, const T data) {
  int nRetPos;
  Node<T> *pTmpNode, *pNewNode;
  try {
    pNewNode = new Node<T>;
  } catch (std::bad_alloc&) {
    nRetPos = 0;
    return nRetPos;
  }
  pNewNode->data = data;

  if (nullptr == m_pNodeHead) {
    pNewNode->next = nullptr;
    m_pNodeHead = pNewNode;
    nRetPos = 1;
    ++m_nCount;
    return nRetPos;
  }

  assert(1 <= pos && pos <= m_nCount);

  pTmpNode = m_pNodeHead;
  for (int i = 1; i < pos; ++i) {
    pTmpNode = pTmpNode->next;
  }
  pNewNode->next = pTmpNode->next;
  pTmpNode->next = pNewNode;
  nRetPos = pos + 1;
  ++m_nCount;
  return nRetPos;
}

template<typename T>
inline void SList<T>::RemoveAt(const int pos) {
  assert(1 <= pos && pos <= m_nCount);

  Node<T> *pTmpNode1, *pTmpNode2;
  pTmpNode1 = m_pNodeHead;

  if (1 == pos) {
    m_pNodeHead = m_pNodeHead->next;
    delete pTmpNode1;
    --m_nCount;
    return;
  }

  for (int i = 1; i < pos; ++i) {
    pTmpNode2 = pTmpNode1;
    pTmpNode1 = pTmpNode1->next;
  }
  pTmpNode2->next = pTmpNode1->next;
  delete pTmpNode1;
  --m_nCount; 
}

template<typename T>
inline void SList<T>::RemoveHead() {
  assert(0 != m_nCount);
  RemoveAt(1);
}

template<typename T>
inline void SList<T>::RemoveTail() {
  assert(0 != m_nCount);
  RemoveAt(m_nCount);
}

template<typename T>
inline void SList<T>::RemoveAll() {
  int nCount = m_nCount;
  Node<T>* pTmpNode;

  if (0 == nCount) return;

  for (int i = 0; i < nCount; ++i) {
    pTmpNode = m_pNodeHead->next;
    delete m_pNodeHead;
    m_pNodeHead = pTmpNode; 
  }
  // m_pNodeHead = nullptr;
  m_nCount = 0;
} 

template<typename T>
inline T& SList<T>::GetTail() {
  assert(0 != m_nCount);
  int nCount = m_nCount;
  Node<T>* pTmpNode = m_pNodeHead;

  for (int i = 1; i < nCount; ++i) {
    pTmpNode = pTmpNode->next;
  }
  return pTmpNode->data;
}

template<typename T>
inline T SList<T>::GetTail() const {
  assert(0 != m_nCount);
  int nCount = m_nCount;
  Node<T>* pTmpNode = m_pNodeHead;

  for (int i = 1; i < nCount; ++i) {
    pTmpNode = pTmpNode->next;
  }
  return pTmpNode->data;
}

template<typename T>
inline T& SList<T>::GetHead() {
  assert(0 != m_nCount);
  return m_pNodeHead->data;
}

template<typename T>
inline T SList<T>::GetHead() const {
  assert(0 != m_nCount);
  return m_pNodeHead->data;
}

template<typename T>
inline T& SList<T>::GetAt(const int pos) {
  assert(1 <= pos && pos <= m_nCount);
  Node<T>* pTmpNode = m_pNodeHead;
  for (int i = 1; i < pos; ++i) {
    pTmpNode = pTmpNode->next;
  }
  std::cout << "GetAt() is called." << std::endl;
  return pTmpNode->data;   
}

template<typename T>
inline T SList<T>::GetAt(const int pos) const {
  assert(1 <= pos && pos <= m_nCount);
  Node<T>* pTmpNode = m_pNodeHead;
  for (int i = 1; i < pos; ++i) {
    pTmpNode = pTmpNode->next;
  }
  std::cout << "GetAt() const is called." << std::endl;
  return pTmpNode->data;   
}

template<typename T>
inline void SList<T>::SetAt(const int pos, T data) {
  assert(1 <= pos && pos <= m_nCount);
  Node<T>* pTmpNode = m_pNodeHead;
  for (int i = 1; i < pos; ++i) {
    pTmpNode = pTmpNode->next;
  } 
  pTmpNode->data = data;
}

/* Return the position of the node that has the target data if success.
 * Return 0 if no node has the target data.
 */
template<typename T>
inline int SList<T>::Find(const T data) const {
  int i;
  int nCount = m_nCount;
  Node<T>* pTmpNode = m_pNodeHead;
  for (i = 0; i < nCount; ++i) {
    if (data == pTmpNode->data) {
      return i + 1;
    }
    pTmpNode = pTmpNode->next;
  }
  return 0;
}

template<typename T>
inline int SList<T>::FindCircle() const {
  if (0 == m_nCount) return 0;
  Node<T> *p1 = m_pNodeHead, *p2 = m_pNodeHead;
 
  do {
    if (p1 != nullptr && p2 != nullptr && p2->next != nullptr) {
      p1 = p1->next;
      p2 = p2->next->next;
    } else {
      return 0;
    }
  } while (p1 != p2);
  p1 = m_pNodeHead;
  for (int i = 1; i < m_nCount; ++i) {
    p1 = p1->next;
    p2 = p2->next;
  }
  p1 = m_pNodeHead;
  int i;
  for (i = 1; i <= m_nCount; ++i) {
    if (p2 == p1) break;
    p1 = p1->next;
  }
  return i;
}

// Neither list has circle.
template<typename T>
inline int SList<T>::FindCross(SList<T>& test_list) {
  if (0 == m_nCount || 0 == test_list.m_nCount) return 0;
  if (FindCircle() || test_list.FindCircle()) return 0;

  // link the test_list at the tail of this list  
  Node<T>* pTail = m_pNodeHead;
  for (int i = 1; i < m_nCount; ++i) {
    pTail = pTail->next;
  }
  pTail->next = test_list.m_pNodeHead;
  m_nCount += test_list.m_nCount;

  int cross = FindCircle();
  pTail->next = nullptr;
  m_nCount -= test_list.m_nCount;
  return cross;  
}
