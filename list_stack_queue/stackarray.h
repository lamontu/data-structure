/* stackarray.h
 * Use array to create stack
 */

#ifndef __STACKARRAY_H__
#define __STACKARRAY_H__

#include <cassert>
#include <new>

const int EmptyTOS = -1;
const int MinStackSize = 5;
const int MaxStackSize = 500;

template<typename T>
class StackArray {
 private:
  int capacity;
  int tos;  // Top of stack for now
  T* array;
  void DisposeStack();
 public:
  StackArray(int maxsize=MaxStackSize);
  StackArray(const StackArray<T>& other);
  StackArray<T>& operator=(const StackArray<T>& othr);
  ~StackArray();
  bool IsEmpty() const;
  void MakeEmpty();
  int GetCount() const;
  bool IsFull();
  bool Resize(int newmaxsize);
  bool Push(const T& data);
  bool Pop(T* data=nullptr);
  bool Top(T* data) const;
};

template<typename T>
inline void StackArray<T>::DisposeStack() {
  capacity = 0;
  tos = EmptyTOS;
  if (array) {
    delete [] array;
  }
}

template<typename T>
inline StackArray<T>::StackArray(int maxsize)
  : capacity(maxsize), tos(EmptyTOS), array(nullptr) {

  assert(capacity >= MinStackSize);

  try {
    array = new T[capacity];
  } catch (std::bad_alloc&) {  }
}

template<typename T>
inline StackArray<T>::StackArray(const StackArray<T>& other)
  : capacity(other.capacity), tos(other.tos), array(nullptr) {
  try {
    array = new T[capacity];
  } catch (std::bad_alloc&) {  }

  if (0 <= tos && tos < capacity) {
    for (int i = 0; i <= tos; ++i) {
      array[i] = other.array[i];
    }
  }
}

template<typename T>
inline StackArray<T>& StackArray<T>::operator=(const StackArray<T>& other) {
  if (this == &other) {
    return *this;
  }

  capacity = other.capacity;
  tos = other.tos;
  delete [] array;
  array = new T[capacity];  // This is necessary.
  if (0 <= tos && tos < capacity) {
    for (int i = 0; i <= tos; ++i) {
      array[i] = other.array[i];
    }
  }
  return *this;
}

template<typename T>
inline StackArray<T>::~StackArray() {
  DisposeStack();
}

template<typename T>
inline bool StackArray<T>::IsEmpty() const {
  return EmptyTOS == tos;
}

template<typename T>
inline void StackArray<T>::MakeEmpty() {
  tos = EmptyTOS;
}

template<typename T>
inline int StackArray<T>::GetCount() const {
  return tos + 1;
}

template<typename T>
inline bool StackArray<T>::IsFull() {
  return tos >= capacity - 1;
}

template<typename T>
inline bool StackArray<T>::Resize(int newmaxsize) {
  T* newarray;
  try {
    newarray = new T[newmaxsize];
  } catch (std::bad_alloc&) {
    return false;
  }
  if (0 <= tos && tos < capacity) {
    for (int i = 0; i <= tos; ++i) {
      newarray[i] = array[i];
    }
  }

  int n = tos;
  DisposeStack();
  this->array = newarray;
  tos = n;
  capacity = newmaxsize;
  return true;
}

template<typename T>
inline bool StackArray<T>::Push(const T& data) {
  if (IsFull()) {
    return false;
  } else {
    array[++tos] = data;
    return true;
  }
}

template<typename T>
// inline bool StackArray<T>::Pop(T* pdata=nullptr) {  // Error
inline bool StackArray<T>::Pop(T* pdata) {
  if (IsEmpty()) {
    return false;
  } else {
    if (pdata) {
      *pdata = array[tos];
    }
    --tos;
    return true;
  }
}

template<typename T>
inline bool StackArray<T>::Top(T* pdata) const {
  if (IsEmpty()) {
    return false;
  } else {
    *pdata = array[tos];
    return true;
  }
}

#endif  // __STACKARRAY_H__
