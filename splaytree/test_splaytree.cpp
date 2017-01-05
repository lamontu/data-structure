/* test_splaytree.cpp */

#include "splaytree.h"
#include <iostream>

using namespace std;

void visit(const int& a) {
  cout << a << ", ";
}

typedef void(*Funtype)(const int&);
Funtype pfun = visit;

int main(int agrc, char* argv[]) {
  cout << "================================" << endl;

  int arr[] = {10, 50, 40, 30, 20, 60};
  SplayTree<int>* tree = new SplayTree<int>();
  cout << "# Add elements:" << endl;
  int ilen = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < ilen; ++i) {
    cout << arr[i] << ", ";
    tree->insert(arr[i]);
  }
  cout << endl;

  cout << "# preOrder traverse:" << endl;
  tree->preOrder(pfun);  cout << endl;
  cout << "# inOrder traverse:" << endl;
  tree->inOrder(pfun);  cout << endl;
  cout << "# postOrder traverse:" << endl;
  tree->postOrder(pfun);  cout << endl;

  cout << "Minimum: " << tree->minimum() << endl;
  cout << "Maximum: " << tree->maximum() << endl;
  
  tree->print();

  int a = 30;
  cout << "Splay node 30: " << endl;
  tree->splay(a);
  tree->print();

  //tree->destroy();
  delete tree;

  cout << "================================" << endl;
  return 0;
}
