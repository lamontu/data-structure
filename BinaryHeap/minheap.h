#ifndef MINHEAP_H_
#define MINHEAP_H_

#include <iostream>

using std::cerr;
using std::endl;

const int INITSIZE = 20;
const int EXTFACTOR = 2;

template<typename T>
class MinHeap {
 private:
  T* elements;
  int currentSize;
  int capacity;

  void filterDown(int hole);
  void filterUp(int hole);
  void handleOverflow();
  inline void handleUnderflow();

 public:
  explicit MinHeap(int maxSize =  INITSIZE);
  MinHeap(T* array, int length);
  MinHeap(const MinHeap<T>& other);
  MinHeap<T>& operator=(const MinHeap<T>& rhs);
  ~MinHeap();

  inline bool isEmpty() const;
  inline void makeEmpty();
  inline int size() const;

  inline void insert(const T& x);
  inline void findMin(T& x);
  inline void deleteMin();
  inline void deleteMin(T& minItem);
};

template<typename T>
MinHeap<T>::MinHeap(int maxSize) {
  capacity = maxSize;
  elements = new T[capacity + 1];
  if (nullptr == elements) {
    cerr << "Out of memory!" << endl;
  }
  currentSize = 0;
}

template<typename T>
MinHeap<T>::MinHeap(T* array, int length) {
  capacity = (INITSIZE > length) ? INITSIZE : length;
  elements = new T[capacity + 1];
  if (nullptr == elements) {
    cerr << "Out of memory!" << endl;
  }
  for (int i = 0; i < length; ++i) {
    elements[i + 1] = array[i];
  }
  currentSize = length;
  for (int i = currentSize / 2; i > 0; --i) {
    filterDown(i);
  }
}

template<typename T>
MinHeap<T>::MinHeap(const MinHeap<T>& other) {
  capacity = other.capacity;
  currentSize = other.currentSize;
  elements = new T[capacity + 1];
  if (nullptr == elements) {
    cerr << "Out of memory!" << endl;
  }
  for (size_t k = 1; k < currentSize; ++k) {
    elements[k] = other.elements[k];
  }
}

template<typename T>
MinHeap<T>& MinHeap<T>::operator=(const MinHeap<T>& rhs) {
  if (this == &rhs) {
    return *this;
  }

  delete [] elements;

  capacity = rhs.capacity;
  currentSize = rhs.currentSize;
  elements = new T[capacity + 1];
  if (nullptr == elements) {
    cerr << "Out of memory!" << endl;
  }
  for (size_t k = 1; k < currentSize; ++k) {
    elements[k] = rhs.elements[k];
  }

  return *this;
}

template<typename T>
MinHeap<T>::~MinHeap() {
  currentSize = 0;
  capacity = INITSIZE;
  delete [] elements;
}

template<typename T>
inline bool MinHeap<T>::isEmpty() const {
  return currentSize == 0;
}

template<typename T>
inline void MinHeap<T>::makeEmpty() {
  currentSize = 0;
}

template<typename T>
inline int MinHeap<T>::size() const {
  return currentSize;
}

// Insert item x, allowing duplicates.
template<typename T>
inline void MinHeap<T>::insert(const T& x) {
  if (currentSize == capacity) {
    handleOverflow();
  }
  elements[++currentSize] = x;
  filterUp(currentSize);
}

// Find the smallest item in the heap
template<typename T>
inline void MinHeap<T>::findMin(T& x) {
  if (!isEmpty()) {
    x = elements[1];
  } else {
    handleUnderflow();
  }
}

// Remove the minimum item
template<typename T>
inline void MinHeap<T>::deleteMin() {
  if (!isEmpty()) {
    elements[1] = elements[currentSize--];
    filterDown(1);
  } else {
    handleUnderflow();
  }
}

// Remove the minimum item and place it in minItem
template<typename T>
inline void MinHeap<T>::deleteMin(T& minItem) {
  if (!isEmpty()) {
    minItem = elements[1];
    elements[1] = elements[currentSize--];
    filterDown(1);
  } else {
    handleUnderflow();
  }
}

// Percolate down the heap, begin at "hole"
template<typename T>
void MinHeap<T>::filterDown(int hole) {
  int child;
  T tmp = elements[hole];
  for (; 2 * hole <= currentSize; hole = child) {
    child = 2 * hole;
    if (child != currentSize && elements[child + 1] < elements[child]) {
      child++;
    }
    if (elements[child] < tmp) {
      elements[hole] = elements[child];
    } else {
      break;
    }
  }
  elements[hole] = tmp;
}

// Percolate up the heap, begin at "hole"
template<typename T>
void MinHeap<T>::filterUp(int hole) {
  T tmp = elements[hole];
  for (; hole > 1 && tmp < elements[hole / 2]; hole /= 2) {
    elements[hole] = elements[hole / 2];
  }
  elements[hole] = tmp;
}

// If the capability of the heap exceeds the initial size, make it double.
template<typename T>
void MinHeap<T>::handleOverflow() {
  capacity = EXTFACTOR * capacity;
  T* newArray = new T[capacity + 1];
  if (nullptr == newArray) {
    cerr << "Out of memory!" << endl;
    exit(1);
  }
  for (int i = 1; i <= currentSize; ++i) {
    newArray[i] = elements[i];
  }
  delete [] elements;
  elements = newArray;
}

// Handle the error of get element from an empty heap
template<typename T>
inline void MinHeap<T>::handleUnderflow() {
  cerr << "The heap is empty!" << endl;
  exit(1);
}

#endif  // MINHEAP_H_
