/* test_fibonacci_heap.cpp */

#include "fibonacci_heap.h"
#include <iostream>

int a[] = {12, 7, 25, 15, 28, 33, 41, -1};
int b[] = {18, 35, 20, 42, 9, 31, 23, 6, 48, 11, 24, 52, 13, -1};
int alen = sizeof(a) / sizeof(a[0]);
int blen = sizeof(b) / sizeof(b[0]);

void create(FibHeap<int>* & heap, int* arr, int len) {
  cout << "## Add elements into fibonacci heap:" << endl;
  for (int i = 0; i < len; ++i) {
    cout << arr[i] << ", ";
    heap->Insert(arr[i]);
  }
  cout << endl;
  cout << "### Information of fibonacci heap:" << endl;
  heap->Print();
  cout << "## Delete the minimum node ..." << endl;
  heap->RemoveMin();
  heap->Print();
}

void TestBasic() {
  FibHeap<int>* hb = new FibHeap<int>();
  create(hb, b, blen);

  hb->Contains(20) ? cout << "Contains 20\n" : cout << "No 20\n" << endl;
  hb->Contains(22) ? cout << "Contains 22\n" : cout << "No 22\n" << endl;
}

void TestInsert() {
  FibHeap<int>* ha = new FibHeap<int>();
  create(ha, a, alen);

  cout << "## Insert 50:" << endl;
  ha->Insert(50);
  ha->Print();
}

void TestUnion() {
  FibHeap<int>* ha = new FibHeap<int>();
  FibHeap<int>* hb = new FibHeap<int>();
  create(ha, a, alen);
  create(hb, b, blen);

  cout << "## Merge fibonacci heap hb into ha:" << endl;
  ha->Combine(hb);
  ha->Print();
}

void TestRemoveMin() {
  FibHeap<int>* ha = new FibHeap<int>();
  FibHeap<int>* hb = new FibHeap<int>();
  create(ha, a, alen);
  create(hb, b, blen);

  cout << "## Merge fibonacci heap hb into ha:" << endl;
  ha->Combine(hb);
  ha->Print();

  cout << "## Remove the minimum node ..." << endl;
  ha->RemoveMin();
  ha->Print();
}

void TestDecrease() {
  FibHeap<int>* hb = new FibHeap<int>();
  create(hb, b, blen);

  cout << "## 20 decrease to 2:" << endl;
  hb->Update(20, 2);
  hb->Print();
}

void TestIncrease() {
  FibHeap<int>* hb = new FibHeap<int>();
  create(hb, b, blen);

  cout << "## 20 increase to 60:" << endl;
  hb->Update(20, 60);
  hb->Print();
}

int main(int argc, char* argv[]) {
  // TestBasic();
  // TestInsert();
  // TestUnion();
  // TestRemoveMin();
  // TestDecrease();
  TestIncrease();

  return 0;
}
