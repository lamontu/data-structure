/* dlist.h
 * No dummy node, all node is data node.
 */

#include <iostream>
#include <cassert>
#include <new>

template<typename T>
class Node {
 public:
  T data;
  Node<T>* prior;
  Node<T>* next;
  Node() : data(T()), prior(nullptr), next(nullptr) {  }
  Node(const T& init_data) : data(init_data), prior(nullptr), next(nullptr) {  }
};

template<typename T>
class DList {
 protected:
  int m_nCount;
  Node<T>* m_pNodeHead;
  Node<T>* m_pNodeTail;
 public:
  DList();
  DList(const T& inti_data);
  DList(const DList<T>& other);  
  DList<T>& operator=(const DList<T>& other);
  ~DList();
  void Invert();
  bool IsEmpty() const;
  int GetCount() const;
  int InsertBefore(const int pos, const T data);
  int InsertAfter(const int pos, const T data);
  int AddHead(const T data);
  int AddTail(const T data);
  void RemoveAt(const int pos);
  void RemoveHead();
  void RemoveTail();
  void RemoveAll();
  void SetAt(const int pos, T data);
  T& GetAt(const int pos);
  T GetAt(const int pos) const;
  T& GetTail();
  T GetTail() const;
  T& GetHead();
  T GetHead() const;
  int Find(const T data) const;
  int FindCircle() const;
  int FindCross(DList& testlist);
  T& GetPrev(int& pos);
  T& GetNext(int& pos);
};

template<typename T>
inline DList<T>::DList()
  : m_nCount(0), m_pNodeHead(nullptr), m_pNodeTail(nullptr) {  }

template<typename T>
inline DList<T>::DList(const T& init_data)
  : m_nCount(0), m_pNodeHead(nullptr), m_pNodeTail(nullptr) {
  AddHead(init_data);
}

template<typename T>
inline DList<T>::DList(const DList<T>& other)
  : m_nCount(0), m_pNodeHead(nullptr), m_pNodeTail(nullptr) {
  if (other.m_nCount > 0) {
    for (int i = 1; i <= other.m_nCount; ++i) {
      AddTail(other.GetAt(i));
    }
  }  
}

template<typename T>
inline DList<T>& DList<T>::operator=(const DList<T>& other) {
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
inline DList<T>::~DList() {
  RemoveAll();
}

template<typename T>
inline void DList<T>::Invert() {
  if (m_nCount <= 1) return;
  Node<T> *curNod, *preNod, *nexNod;
  curNod = m_pNodeHead;
  preNod = curNod->prior;
  for (int i = 1; i <= m_nCount; ++i) {
    nexNod = curNod->next;
    curNod->prior = nexNod;
    curNod->next = preNod;
    preNod = curNod;
    curNod = nexNod;
  }
  m_pNodeTail = m_pNodeHead;
  m_pNodeHead = preNod;
  return;
}

template<typename T>
inline bool DList<T>::IsEmpty() const {
  return 0 == m_nCount;
}

template<typename T>
inline int DList<T>::GetCount() const {
  return m_nCount;
} 

/* Return the position of the new node if success.
 * Return 0 if fail.
 */
template<typename T>
inline int DList<T>::InsertBefore(const int pos, const T data) {
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
    pNewNode->prior = nullptr;
    pNewNode->next = nullptr;
    m_pNodeHead = pNewNode;
    m_pNodeTail = pNewNode;
    nRetPos = 1;
    ++m_nCount;    
    return nRetPos;
  }

  assert(1 <= pos && pos <= m_nCount);

  if (1 == pos) {
    pNewNode->prior = nullptr;
    pNewNode->next = m_pNodeHead;
    m_pNodeHead->prior = pNewNode;
    m_pNodeHead = pNewNode;
    nRetPos = 1;
    ++m_nCount;
    return nRetPos;
  }

   pTmpNode = m_pNodeHead;
   for (int i = 1; i < pos; ++i) {
     pTmpNode = pTmpNode->next;
   }
   pNewNode->next = pTmpNode;
   pNewNode->prior = pTmpNode->prior;
   pTmpNode->prior->next = pNewNode;
   pTmpNode->prior = pNewNode;
   nRetPos = pos;
   ++m_nCount;
   return nRetPos;
}

/* Return the position of the new node if success.
 * Return 0 if fail.
 */
template<typename T>
inline int DList<T>::InsertAfter(const int pos, const T data) {
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
    pNewNode->prior = nullptr;
    pNewNode->next = nullptr;
    m_pNodeHead = pNewNode;
    m_pNodeTail = pNewNode;
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
  pNewNode->prior = pTmpNode;
  pTmpNode->next = pNewNode;
  if (nullptr == pNewNode->next) {
    m_pNodeTail = pNewNode;
  } else {
    pNewNode->next->prior = pNewNode;
  }
  nRetPos = pos + 1;
  ++m_nCount;
  return nRetPos;
}

template<typename T>
inline int DList<T>::AddHead(const T data) {
  return InsertBefore(1, data);
}

template<typename T>
inline int DList<T>::AddTail(const T data) {
  return InsertAfter(GetCount(), data);
}

template<typename T>
inline void DList<T>::RemoveAt(const int pos) {
  assert(1 <= pos && pos <= m_nCount);

  Node<T> *pTmpNode = m_pNodeHead;

  if (1 == pos) {
    m_pNodeHead = m_pNodeHead->next;
    if (m_pNodeHead) {
      m_pNodeHead->prior = nullptr;
    }
    delete pTmpNode;
    --m_nCount;
    if (0 == m_nCount) {
      m_pNodeTail = nullptr;
    }
    return;
  }

  for (int i = 1; i < pos; ++i) {
    pTmpNode = pTmpNode->next;
  }
  pTmpNode->prior->next = pTmpNode->next;
  if (pTmpNode->next) {
    pTmpNode->next->prior = pTmpNode->prior;
  } else {
    m_pNodeTail = pTmpNode->prior;
  }
  delete pTmpNode;
  --m_nCount; 
  return;
}

template<typename T>
inline void DList<T>::RemoveHead() {
  assert(0 != m_nCount);
  RemoveAt(1);
}

template<typename T>
inline void DList<T>::RemoveTail() {
  assert(0 != m_nCount);
  RemoveAt(m_nCount);
}

template<typename T>
inline void DList<T>::RemoveAll() {
  int nCount = m_nCount;
  Node<T>* pTmpNode;

  if (0 == nCount) return;

  for (int i = 0; i < nCount; ++i) {
    pTmpNode = m_pNodeHead->next;
    delete m_pNodeHead;
    m_pNodeHead = pTmpNode; 
  }
  m_pNodeTail = nullptr;
  m_nCount = 0;
}

template<typename T>
inline void DList<T>::SetAt(const int pos, T data) {
  assert(1 <= pos && pos <= m_nCount);
  Node<T>* pTmpNode = m_pNodeHead;
  for (int i = 1; i < pos; ++i) {
    pTmpNode = pTmpNode->next;
  } 
  pTmpNode->data = data;
}

template<typename T>
inline T& DList<T>::GetAt(const int pos) {
  assert(1 <= pos && pos <= m_nCount);
  Node<T>* pTmpNode = m_pNodeHead;
  for (int i = 1; i < pos; ++i) {
    pTmpNode = pTmpNode->next;
  }
  std::cout << "GetAt() is called." << std::endl;
  return pTmpNode->data;   
}

template<typename T>
inline T DList<T>::GetAt(const int pos) const {
  assert(1 <= pos && pos <= m_nCount);
  Node<T>* pTmpNode = m_pNodeHead;
  for (int i = 1; i < pos; ++i) {
    pTmpNode = pTmpNode->next;
  }
  std::cout << "GetAt() const is called." << std::endl;
  return pTmpNode->data;   
}

template<typename T>
inline T& DList<T>::GetTail() {
  assert(0 != m_nCount);
  return m_pNodeTail->data;
}

template<typename T>
inline T DList<T>::GetTail() const {
  assert(0 != m_nCount);
  return m_pNodeTail->data;
}

template<typename T>
inline T& DList<T>::GetHead() {
  assert(0 != m_nCount);
  return m_pNodeHead->data;
}

template<typename T>
inline T DList<T>::GetHead() const {
  assert(0 != m_nCount);
  return m_pNodeHead->data;
}

/* Return the position of the node that has the target data if success.
 * Return 0 if no node has the target data.
 */
template<typename T>
inline int DList<T>::Find(const T data) const {
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
