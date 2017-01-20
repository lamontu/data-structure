/* test_treap.cpp */

#include "treap.h"
#include <iostream>
#include <algorithm>
#include <vector>

void Visit(const int& a) {
  cout << a << ", ";
}

typedef void(*FuncType)(const int&);
FuncType pfun = Visit;

using namespace std;

int main(int argc, char* argv[]) {
  const int M = 100;
  const int K = 15;
  Treap<int> tree;
  srand(0);
  int a = 0;
  vector<int> vec;
  cout << "## Add elements int treap:" << endl;
  for (int i = 0; i < K; ++i) {
    a = rand() % M;
    vec.push_back(a);
    cout << a << ", ";
    tree.Insert(a);
  }
  cout << endl;
  cout << "## Sort the elements:" << endl;
  sort(vec.begin(), vec.end());
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    cout << *it << ", ";
  }
  cout << endl;

  cout << "## Count: " << COUNT << endl;
  cout << "## Height: " << tree.Height() << endl;

  TreapNode<int>* root = tree.Root();
  cout << "### Root element is: " << root->key << endl;
  cout << "### Root count is: " << root->count << endl;
  cout << "### Root size is: " << root->size << endl;
  cout << "### Root priority is: " << root->priority << endl;

  cout << "## InOrder Traverse:" << endl;
  tree.InOrderTraverse(pfun);  cout << endl;

  cout << "## Test Search():" << endl;
  (tree.Search(23) != nullptr) ? cout << "Has 23\n" : cout << "No 23\n";
  (tree.Search(13) != nullptr) ? cout << "Has 13\n" : cout << "No 13\n";

  cout << "## Test RankMin():" << endl;
  cout << "23 rank at: " << tree.RankMin(23) << endl;
  cout << "13 rank at: " << tree.RankMin(13) << endl;

  cout << "## Test MinKth():" << endl;
  int min_kth = tree.MinKth(4);
  cout << "min_kth: " << min_kth << endl;

  cout << "## Test MaxKth():" << endl;
  int max_kth = tree.MaxKth(4);
  cout << "max_kth: " << max_kth << endl;

  cout << "## Remove element 23 ..." << endl;
  tree.Remove(23);
  tree.InOrderTraverse(pfun);  cout << endl;
  cout << "## Remove element 13 ..." << endl;
  tree.Remove(13);
  tree.InOrderTraverse(pfun);  cout << endl;
  return 0;
}
