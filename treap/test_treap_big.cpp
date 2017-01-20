/* test_treap_big.cpp */

#include "treap.h"
#include <iostream>

void Visit(const int& a) {
  cout << a << ", ";
}

typedef void(*FuncType)(const int&);
FuncType pfun = Visit;

using namespace std;

int main(int argc, char* argv[]) {
  freopen("out.txt", "w", stdout);
  int const M = 10000;
  int const L = 500; 
  Treap<int> tree;
  srand(0);
  int a;
  cout << "## Add elements into treap:" << endl;
  for (int i = 0; i < L; ++i) {
    a = rand() % M;
    cout << a << ", ";
    tree.Insert(a);
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

  return 0;
}
