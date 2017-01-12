/* maxheap.h */

#ifndef __MAX_HEAP_H__
#define __MAX_HEAP_H__

#include <iostream>

using namespace std;

template<typename T>
class MaxHeap {
 private:
  T* mHeap;
  int mCapacity;
  int mSize;
 public:
  MaxHeap();
  MaxHeap(int capacity);
  ~MaxHeap();
  int getIndex(T data);
  bool insert(T data);
  bool remove(T data);
  void print();
 private:
  void filterdown(int start, int end);
  void filterup(int start);
};

template<typename T>
MaxHeap<T>::MaxHeap() {
  new (this)MaxHeap(30);
}

template<typename T>
MaxHeap<T>::MaxHeap(int capacity) {
  mSize = 0;
  mCapacity = capacity;
  mHeap = new T[mCapacity];
}

template<typename T>
MaxHeap<T>::~MaxHeap() {
  mSize = 0;
  mCapacity = 0;
  delete [] mHeap;
}

template<typename T>
int MaxHeap<T>::getIndex(T data) {
  for (int i = 0; i < mSize; ++i) {
    if (data == mHeap[i]) {
      return i;
    }
  }
  return -1;
}

template<typename T>
bool MaxHeap<T>::insert(T data) {
  if (mSize == mCapacity) return false;
  mHeap[mSize] = data;
  filterup(mSize);
  mSize++;
  return true;
}

template<typename T>
bool MaxHeap<T>::remove(T data) {
  int index;
  if (mSize == 0) return false;
  index = getIndex(data);
  if (index == -1) return false;
  mHeap[index] = mHeap[--mSize];
  filterdown(index, mSize - 1);
  return true;
}

template<typename T>
void MaxHeap<T>::print() {
  for (int i = 0; i < mSize; ++i) {
    cout << mHeap[i] << ", ";
  }
  cout << endl;
}

/* Parameter start is the index of the first element to be modified,
 * usually the index of the first element in array mHeap.
 * Parameter end is the the stop index of the modification,
 * usually the index of the last element in array mHeap.
 */ 
template<typename T>
void MaxHeap<T>::filterdown(int start, int end) {
  int cur = start;
  int child = 2 * cur + 1;
  T tmp = mHeap[cur];
  while (child <= end) {
    if (child < end && mHeap[child] < mHeap[child + 1]) {
      child++;
    }
    if (tmp >= mHeap[child]) {
      break;
    } else {
      mHeap[cur] = mHeap[child];
      cur = child;
      child = 2 * child + 1;
    }
  }
  mHeap[cur] = tmp;
}

/* Parameter start is the index of the first element to be modified,
 * usually the index of the last element in array mHeap. 
 */
template<typename T>
void MaxHeap<T>::filterup(int start) {
  int cur = start;
  int parent = (cur - 1) / 2;
  T tmp = mHeap[cur];
  while (cur > 0) {
    if (mHeap[parent] >= tmp) {
      break;
    } else {
      mHeap[cur] = mHeap[parent];
      cur = parent;
      parent = (parent - 1) / 2;
    }
  }
  mHeap[cur] = tmp;
}
  
#endif  // __MAX_HEAP_H__
