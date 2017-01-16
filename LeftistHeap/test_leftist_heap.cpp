/* test_leftist_heap.cpp */

#include "leftist_heap.h"
#include <iostream>

void Visit(const int& a) {
  cout << a << ", ";
}

typedef void(* FuncType)(const int&);
FuncType func = Visit;

int main(int argc, char* argv[]) {
  cout << "================================" << endl;
  int i;
  int a[] = {10, 40, 24, 30, 36, 20, 12, 16};
  int b[] = {17, 13, 11, 15, 19, 21, 23};
  int len_a = sizeof(a) / sizeof(a[0]);
  int len_b = sizeof(b) / sizeof(b[0]);
  LeftistHeap<int>* ha = new LeftistHeap<int>();
  LeftistHeap<int>* hb = new LeftistHeap<int>();

  cout << "## Add elements to LeftistHeap ha:" << endl;
  for (i = 0; i < len_a; ++i) {
    cout << a[i] << ", ";
    ha->Insert(a[i]);
  }
  cout << endl;
  cout << "### Information of LeftistHeap ha:" << endl;
  ha->Print();

  cout << "### Pre Order Traverse:" << endl;
  ha->PreOrderTraverse(func);  cout << endl;
  cout << "### In Order Traverse:" << endl;
  ha->InOrderTraverse(func);  cout << endl;
  cout << "### Post Order Traverse:" << endl;
  ha->PostOrderTraverse(func);  cout << endl;
  cout << "--------------------------------" << endl;

  cout << "## Add elements to LeftistHeap hb:" << endl;
  for (i = 0; i < len_b; ++i) {
    cout << b[i] << ", ";
    hb->Insert(b[i]);
  }
  cout << endl;
  cout << "### Information of LeftistHeap hb:" << endl;
  hb->Print();
  cout << "--------------------------------" << endl;

  cout << "## Merge ha and hb ..." << endl;
  ha->Merge(hb);
  cout << "## Information of merged LeftistHeap:" << endl;
  ha->Print();

  ha->Destroy();
  //hb->Destroy();  // Error, LeftistHeap hb has been destroyed after merge.

  cout << "================================" << endl;
  return 0;
}
