#include <iostream>

using namespace std;

class Heap {
 private:
  int* data;
  int size;
 public:
  Heap(int length_input) {
    data = new int[length_input];
    size = 0;
  }
  ~Heap() {
    delete [] data;
  }
  void push(int value) {
    data[size] = value;
    int current = size;
    int father = (current - 1) / 2;
    while (data[current] > data[father]) {
      swap(data[current], data[father]);
      current = father;
      father = (current - 1) / 2;
    }
    size++;
  }
  void output() {
    for (int i = 0; i < size; ++i) {
      cout << data[i] << ", ";
    }
    cout << endl;
  }
  int top() {
    return data[0];
  }
  void update(int pos, int n) {
    int lchild = 2 * pos + 1, rchild = 2 * pos + 2;
    int max_value = pos;
    if (lchild < n && data[lchild] > data[max_value]) {
      max_value = lchild;
    }
    if (rchild < n && data[rchild] > data[max_value]) {
      max_value = rchild;
    }
    if (max_value != pos) {
      swap(data[pos], data[max_value]);
      update(max_value, n);
    }
  }
  void pop() {
    swap(data[0], data[size - 1]);
    size--;
    update(0, size);
  }
  void heap_sort() {
    for (int i = size - 1; i >= 1; --i) {
      swap(data[i], data[0]);
      update(0, i);
    }
  }
};

int main() {
  int arr[] = {12, 9, 30, 24, 30, 4, 55, 64, 22, 37};
  int len = sizeof(arr) / sizeof(arr[0]);
  Heap heap(100);
  for (int i = 0; i < 10; ++i) {
    heap.push(arr[i]);
  }
  heap.output();
  cout << heap.top() << endl;
  heap.heap_sort();
  heap.output();

  return 0;
}
