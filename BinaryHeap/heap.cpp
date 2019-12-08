#include <iostream>

using std::cout;
using std::endl;
using std::swap;

class Heap {
 private:
  int* m_data;
  size_t m_size;

 public:
  explicit Heap(size_t length_input) {
    m_data = new int[length_input];
    m_size = 0;
  }

  Heap(int* arr, size_t length) {
    m_data = new int[length];
    for (size_t k = 0; k < length; ++k) {
      m_data[k] = arr[k];
    }
    m_size = length;

    heapify();
  }

  Heap(const Heap& other) {
    m_size = other.m_size;
    m_data = new int[m_size];
    for (size_t k = 0; k < m_size; ++k) {
      m_data[k] = other.m_data[k];
    }
  }

  Heap& operator=(const Heap& rhs) {
    if (this == &rhs) {
      return *this;
    }

    delete [] m_data;

    m_size = rhs.m_size;
    m_data = new int[m_size];
    for (size_t k = 0; k < m_size; ++k) {
      m_data[k] = rhs.m_data[k];
    }

    return *this;
  }

  ~Heap() {
    delete [] m_data;
  }

  // Build a heap from an existing array
  void heapify() {
    // Heapify from the last non-leaf node to the root
    for (long k = m_size / 2 - 1; k >= 0; --k) {
      sink(k, m_size);
    }
  }

  // start: the last index for bottom-up filter
  void swim(size_t start) {
    if (start == 0) {
      return;
    }
    size_t father = (start - 1) / 2;
    while (start > 0 && m_data[start] > m_data[father]) {
      swap(m_data[start], m_data[father]);
      start = father;
      father = (start - 1) / 2;
    }
  }

  // Push value to create a max heap
  void push(int value) {
    m_data[m_size++] = value;
    swim(m_size - 1);
  }

  void sink(size_t start, size_t size) {
    if (start == size - 1) {
      return;
    }

    size_t child = 2 * start + 1;
    while (child < size) {
      if (child < size - 1 && m_data[child] < m_data[child+1]) {
        child++;
      }
      if (m_data[start] > m_data[child]) {
        break;
      }
      swap(m_data[start], m_data[child]);
      start = child;
      child = 2 * start + 1;
    }
  }

  void pop() {
    swap(m_data[0], m_data[m_size - 1]);
    m_size--;
    sink(0, m_size);
  }

  void output() {
    for (size_t k = 0; k < m_size; ++k) {
      cout << m_data[k] << ", ";
    }
    cout << endl;
  }

  int top() {
    return m_data[0];
  }

  // Sort the value in the max heap
  void heap_sort() {
    heapify();
    for (long n = m_size - 1; n >= 0; --n) {
      // Move the maximum value m_data[0] the end,
      // then m_data[n] ~ m_data[m_size-1] is sorted.
      swap(m_data[n], m_data[0]);
      // Heapify the heap m_data[0] ~ m_data[n-1]
      sink(0, n);
    }
  }
};

int main() {
  int arr[] = {12, 9, 30, 24, 30, 4, 55, 64, 22, 37};
  Heap heap(100);
  for (int k = 0; k < 10; ++k) {
    heap.push(arr[k]);
  }
  heap.output();

  heap.pop();
  heap.output();

  heap.heap_sort();
  heap.output();

  cout <<  "========" << endl;
  Heap heap2(arr, 10);
  heap2.output();
  cout << heap2.top() << endl;
  heap2.heap_sort();
  heap2.output();

  return 0;
}
