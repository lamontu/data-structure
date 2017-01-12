/* test_maxheap.cpp */

#include "maxheap.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
  int i, len = sizeof(a) / sizeof(a[0]);
  MaxHeap<int>* tree = new MaxHeap<int>();

  cout << "## Add element:" << endl;
  for (i = 0; i < len; ++i) {
    cout << a[i] << ", ";
    tree->insert(a[i]);
  }
  cout << endl;

  cout << "## Max heap:" << endl;
  tree->print();

  i = 85;
  cout << "## Insert new element: " << i << endl;
  tree->insert(i);
  cout << "Max heap:" << endl;
  tree->print();

  i = 90;
  cout << "## Remove an element: " << i << endl;
  tree->remove(i);
  cout << "Max heap:" << endl;
  tree->print();
  delete tree;
  return 0;
}
