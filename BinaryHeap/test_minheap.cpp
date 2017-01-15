/* test_minheap.cpp */

#include "minheap.h"
#include <iostream>

int main(int argc, char* argv[]) {
  MinHeap<int> h;
  int x, a[100];
  int rand_num;
  const int M = 100;
  const int length = 25;

  cout << "## Insert element into heap one by one:" << endl;
  srand(0);
  for (int i = 1; i <= length; ++i) {
    rand_num = rand() % M;
    h.insert(rand_num);
  }
  cout << "### heap h:" << endl;
  while (!h.isEmpty()) {
    h.findMin(x);
    cout << "  " << x << "\t";
    h.deleteMin();
  }
  cout << endl;

  cout << "## Construct a heap using an array:" << endl;
  srand(0);
  for (int i = 0; i < 40; ++i) {
    a[i] = rand() % M;
    cout << "  " << a[i] << "\t";
  }
  cout << endl;
  MinHeap<int> hh(a, 40);
  cout << "### heap hh:" << endl;
  while (!hh.isEmpty()) {
    hh.deleteMin(x);
    cout << "  " << x << "\t";
  }
  cout << endl;

  for (int i = 1; i <= 5; ++i) {
    rand_num = rand() % M;
    h.insert(rand_num);
  }
  cout << "Size of heap h: " << h.size() << endl;
  h.makeEmpty();
  h.deleteMin();

  return 0;
}
