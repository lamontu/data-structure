/* test_binomial_heap.cpp */

#include "binomial_heap.h"
#include <iostream>

using namespace std;

int a[] = {12, 7, 25, 15, 28, 33, 41};
int b[] = {18, 35, 20, 42, 9, 31, 23, 6, 48, 11, 24, 52, 13};
int alen = sizeof(a) / sizeof(a[0]);
int blen = sizeof(b) / sizeof(b[0]);

void Create(BinomialHeap<int>* & heap, int arr[], int len) {
  cout << "## Add elements into binomial heap:" << endl;
  for (int i = 0; i < len; ++i) {
    cout << arr[i] << ", ";
    heap->Insert(arr[i]);
  }
  cout << endl;
  cout << "### Information of binomial heap:" << endl;
  heap->Print();
}

void TestInsert() {
  // BinomialHeap<int>* hb;  // Segmentation fault: 11
  BinomialHeap<int>* hb = new BinomialHeap<int>();
  Create(hb, b, blen);
}

void TestUnion() {
  BinomialHeap<int>* ha = new BinomialHeap<int>();
  Create(ha, a, alen);
  BinomialHeap<int>* hb = new BinomialHeap<int>();
  Create(hb, b, blen);

  cout << "## Merge binomial heap ha and hb ..." << endl;
  ha->Combine(hb);
  cout << "### Information of merged binomial heap:" << endl;
  ha->Print();
}

void TestRemove() {
  BinomialHeap<int>* hb = new BinomialHeap<int>();
  Create(hb, b, blen);

  cout << "## Remove 20 ..." << endl;
  hb->Remove(20);
  cout << "### Information of binomial heap after remove 20:" << endl;
  hb->Print();
}

void TestIncrease() {
  BinomialHeap<int>* hb = new BinomialHeap<int>();
  Create(hb, b, blen);

  cout << "## Update 6 as 60 ..." << endl;
  hb->Update(6, 60);
  hb->Print();
}

void TestDecrease() {
  BinomialHeap<int>* hb = new BinomialHeap<int>();
  Create(hb, b, blen);

  cout << "## Update 20 as 2 ..." << endl;
  hb->Update(20, 2);
  hb->Print();
}

int main(int argc, char* argv[]) {
  // TestInsert();
  // TestUnion(); 
  // TestRemove();
  // TestIncrease();
  TestDecrease();
  return 0;
}
