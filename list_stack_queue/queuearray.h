/* queuearray.h
 * Use array to create circular queue
 */

#ifndef __QUEUEARRAY_H__
#define __QUEUEARRAY_H__

#include <cassert>
#include <new>

const int MinQueueSize = 5;
const int MaxQueueSize = 500;

template<typename T>
class QueueArray {
 private:
  int capacity;
  int front;
  int rear;
  int size;
  T* array;
  int Succession(int pos);  // Implemet circular queue using circular array
 public:
  QueueArray(int maxsize=MaxQueueSize);
  QueueArray(const QueueArray<T>& other);
  QueueArray<T>& operator=(const QueueArray<T>& other);
  ~QueueArray();
  bool IsEmpty() const;
  bool IsFull() const;
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
inline int QueueArray<T>::Succession(int pos) {
  if (++pos == capacity) {
    pos = 0;
  }
  return pos;
}

template<typename T>
inline QueueArray<T>::QueueArray(int maxsize)
  : capacity(maxsize), front(0), rear(-1), size(0), array(nullptr) {
  assert(capacity >= MinQueueSize);
  try {
    array = new T[capacity];
  } catch (std::bad_alloc&) {  }
}

template<typename T>
inline QueueArray<T>::QueueArray(const QueueArray<T>& other)
  : capacity(other.capacity), front(other.front), rear(other.rear),
    size(other.size), array(nullptr) {
  if (capacity > 0) {
    try {
      array = new T[capacity];
    } catch (std::bad_alloc&) {  }

    for (int i = 0; i < capacity; ++i) {
      array[i] = other.array[i];
    }
  }
}

template<typename T>
inline QueueArray<T>& QueueArray<T>::operator=(const QueueArray<T>& other) {
  if (this == &other) return *this;
  if (array != nullptr) delete [] array;

  capacity = other.capacity;
  size = other.size;
  front = other.front;
  rear = other.rear;

  if (capacity > 0) {
    try {
      array = new T[capacity];
    } catch (std::bad_alloc&) {  }

    for (int i = 0; i < capacity; ++i) {
      array[i] = other.array[i];
    }
  }
  return *this;
}

template<typename T>
inline QueueArray<T>::~QueueArray() {
  if (array) {
    delete [] array;
  }
}

template<typename T>
inline bool QueueArray<T>::IsEmpty() const {
  return 0 == size;
}

template<typename T>
inline bool QueueArray<T>::IsFull() const {
  return capacity == size;
}

template<typename T>
inline int QueueArray<T>::GetCount() const {
  return size;
}

template<typename T>
inline void QueueArray<T>::MakeEmpty() {
  front = 1;
  rear = 0;
  size = 0;
}

template<typename T>
inline bool QueueArray<T>::EnQueue(const T& data) {
  if (IsFull()) {
    return false;
  } else {
    ++size;
    rear = Succession(rear);
    array[rear] = data;
    return true;
  }
}

template<typename T>
inline T QueueArray<T>::DeQueue() {
  assert(0 != size);

  T data = array[front];
  --size;
  front = Succession(front);
  return data;
}

template<typename T>
inline T& QueueArray<T>::GetFront() {
  assert(0 != size);
  return array[front];
}

template<typename T>
inline T QueueArray<T>::GetFront() const {
  assert(0 != size);
  return array[front];
}

template<typename T>
inline T& QueueArray<T>::GetRear() {
  assert(0 != size);
  return array[rear];
}

template<typename T>
inline T QueueArray<T>::GetRear() const {
  assert(0 != size);
  return array[rear];
}

#endif  // __QUEUEARRAY_H__
