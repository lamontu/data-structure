/* stacklist.h
 * Use single list to create stack
 */

#ifndef __STACKLIST_H__
#define __STACKLIST_H__

#include <cassert>
#include "slist.h"

template<typename T>
class StackList {
 private:
  SList<T> slist;
 public:
  StackList();
  StackList(const T& init_data);
  ~StackList();
  bool IsEmpty() const;
  void MakeEmpty();  // Equivalent to DisposeStack() in stackarray.h
  int GetCount() const;
  bool Push(T data);
  bool Pop(T *pdata=nullptr);
  bool Top(T *pdata) const;
};

template<typename T>
inline StackList<T>::StackList() : slist() {  }

template<typename T>
inline StackList<T>::StackList(const T& init_data) : slist(init_data) {  }

template<typename T>
inline StackList<T>::~StackList() {  }

template<typename T>
inline bool StackList<T>::IsEmpty() const {
  return slist.IsEmpty();
}

template<typename T>
inline void StackList<T>::MakeEmpty() {
  slist.RemoveAll();
}

template<typename T>
inline int StackList<T>::GetCount() const {
  return slist.GetCount();
}

template<typename T>
inline bool StackList<T>::Push(T data) {
  return slist.AddHead(data);
}

template<typename T>
inline bool StackList<T>::Pop(T* pdata) {
  if (IsEmpty()) return false;
  if (pdata) Top(pdata);
  slist.RemoveHead();
  return true;  
}

template<typename T>
inline bool StackList<T>::Top(T* pdata) const {
  assert(pdata);
  if (IsEmpty()) return false;
  *pdata = slist.GetHead();
  return true; 
}

#endif  // __STACKLIST_H__
