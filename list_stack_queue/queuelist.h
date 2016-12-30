/* queuelist.h
 * Use singly linked list to create queue
 */

#ifndef __QUEUELIST_H__
#define __QUEUELIST_H__

#include "slist.h"

template<typename T>
class QueueList {
 private:
  SList<T> slist;
 public:
  // No need to define copy constructor
  QueueList();
  QueueList(const T& init_data);
  ~QueueList();
  bool IsEmpty() const;
  int GetCount() const;
  void MakeEmpty();
  bool EnQueue(const T& data);
  T DeQueue();
  T& GetFront();
  T GetFront() const;
  T& GetRear();
  T GetRear() const;
};

template<typename T>
inline QueueList<T>::QueueList() : slist() {  }

template<typename T>
inline QueueList<T>::QueueList(const T& init_data) : slist(init_data) {  }

template<typename T>
inline QueueList<T>::~QueueList() {  }

template<typename T>
inline bool QueueList<T>::IsEmpty() const {
  return slist.IsEmpty();
}

template<typename T>
inline int QueueList<T>::GetCount() const {
  return slist.GetCount();
}

template<typename T>
inline void QueueList<T>::MakeEmpty() {
  slist.RemoveAll();
}

template<typename T>
inline bool QueueList<T>::EnQueue(const T& data) {
  return slist.AddTail(data);
}

template<typename T>
inline T QueueList<T>::DeQueue() {
  T data = slist.GetHead();
  slist.RemoveHead();
  return data;
}

template<typename T>
inline T& QueueList<T>::GetFront() {
  return slist.GetHead();
}

template<typename T>
inline T QueueList<T>::GetFront() const {
  return slist.GetHead();
}

template<typename T>
inline T& QueueList<T>::GetRear() {
  return slist.GetTail();
}

template<typename T>
inline T QueueList<T>::GetRear() const {
  return slist.GetTail();
}

#endif  // __QUEUELIST_H__
