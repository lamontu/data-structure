#include "skew_heap.h"

static void Visit(const int& a) {
  cout << a << ", ";
}

typedef void(* FuncType)(const int&);
static FuncType func = Visit;

int main() {
  cout << "================================" << endl;
  int i;
  int a[] = {10, 40, 24, 30, 36, 20, 12, 16};
  int b[] = {17, 13, 11, 15, 19, 21, 23};
  int len_a = sizeof(a) / sizeof(a[0]);
  int len_b = sizeof(b) / sizeof(b[0]);
  SkewHeap<int>* ha = new SkewHeap<int>();
  SkewHeap<int>* hb = new SkewHeap<int>();

  cout << "## Add elements to SkewHeap ha:" << endl;
  for (i = 0; i < len_a; ++i) {
    cout << a[i] << ", ";
    ha->Insert(a[i]);
  }
  cout << endl;
  cout << "### Information of SkewHeap ha:" << endl;
  ha->Print();

  cout << "### Pre Order Traverse:" << endl;
  ha->PreOrderTraverse(func);  cout << endl;
  cout << "### In Order Traverse:" << endl;
  ha->InOrderTraverse(func);  cout << endl;
  cout << "### Post Order Traverse:" << endl;
  ha->PostOrderTraverse(func);  cout << endl;
  cout << "--------------------------------" << endl;

  cout << "## Add elements to SkewHeap hb:" << endl;
  for (i = 0; i < len_b; ++i) {
    cout << b[i] << ", ";
    hb->Insert(b[i]);
  }
  cout << endl;
  cout << "### Information of SkewHeap hb:" << endl;
  hb->Print();
  cout << "--------------------------------" << endl;

  cout << "## Merge ha and hb ..." << endl;
  ha->Merge(hb);
  cout << "## Information of merged SkewHeap:" << endl;
  ha->Print();

  ha->Destroy();

  cout << "================================" << endl;
  return 0;
}
