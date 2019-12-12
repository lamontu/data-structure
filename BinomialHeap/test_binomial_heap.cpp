#include "binomial_heap.h"

static int a[] = {12, 7, 25, 15, 28, 33, 41};
static int b[] = {18, 35, 20, 42, 9, 31, 23, 6, 48, 11, 24, 52, 13};
static int alen = sizeof(a) / sizeof(a[0]);
static int blen = sizeof(b) / sizeof(b[0]);

static void Create(BinomialHeap<int>* & heap, int arr[], int len) {
  cout << "## Add elements into binomial heap:" << endl;
  for (int i = 0; i < len; ++i) {
    cout << arr[i] << ", ";
    heap->Insert(arr[i]);
  }
  cout << endl;
  cout << "### Information of binomial heap:" << endl;
  heap->Print();
}

static void TestInsert() {
  // BinomialHeap<int>* hb;  // Segmentation fault: 11
  BinomialHeap<int>* hb = new BinomialHeap<int>();
  Create(hb, b, blen);
}

static void TestUnion() {
  BinomialHeap<int>* ha = new BinomialHeap<int>();
  Create(ha, a, alen);
  BinomialHeap<int>* hb = new BinomialHeap<int>();
  Create(hb, b, blen);

  cout << "## Merge binomial heap ha and hb ..." << endl;
  ha->Combine(hb);
  cout << "### Information of merged binomial heap:" << endl;
  ha->Print();
}

static void TestRemove() {
  BinomialHeap<int>* hb = new BinomialHeap<int>();
  Create(hb, b, blen);

  cout << "## Remove 20 ..." << endl;
  hb->Remove(20);
  cout << "### Information of binomial heap after remove 20:" << endl;
  hb->Print();
}

static void TestIncrease() {
  BinomialHeap<int>* hb = new BinomialHeap<int>();
  Create(hb, b, blen);

  cout << "## Update 6 as 60 ..." << endl;
  hb->Update(6, 60);
  hb->Print();
}

static void TestDecrease() {
  BinomialHeap<int>* hb = new BinomialHeap<int>();
  Create(hb, b, blen);

  cout << "## Update 20 as 2 ..." << endl;
  hb->Update(20, 2);
  hb->Print();
}

int main() {
  // TestInsert();
  // TestUnion();
  // TestRemove();
  // TestIncrease();
  TestDecrease();
  return 0;
}
