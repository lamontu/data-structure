/* test_avltree.cpp */

#include "avltree.h"
#include <iostream>

using namespace std;

void visit(const int& a) {
  cout << a << ", ";
}

typedef void(*Funtype)(const int&);
Funtype pfun = visit;

int main() {
  cout << "================================" << endl;

  AVLTree<int> tree;
  tree.insert(3); tree.insert(2); tree.insert(1);
  tree.insert(4); tree.insert(5); tree.insert(6); tree.insert(7);
  tree.insert(16); tree.insert(15); tree.insert(14); tree.insert(13);
  tree.insert(12); tree.insert(11); tree.insert(10);
  tree.insert(8); tree.insert(9);
  tree.print();  cout << endl;

  // tree.insert(4);  // Assertion failed 

  tree.preOrder(pfun);  cout << endl;
  tree.inOrder(pfun);  cout << endl;
  tree.postOrder(pfun);  cout << endl;
  cout << endl;

  cout << "Height: " << tree.height() << endl;
  cout << "Minimum: " << tree.minimum() << endl;
  cout << "Maximum: " << tree.maximum() << endl;
  cout << endl;
  
  tree.remove(8);
  tree.print();  cout << endl;

  // tree.remove(20);  // No effect

  cout << "Height: " << tree.height() << endl;
  cout << "Minimum: " << tree.minimum() << endl;
  cout << "Maximum: " << tree.maximum() << endl;
  cout << endl;
 
  tree.remove(7);
  tree.print();  cout << endl;
  cout << "================================" << endl;
  return 0;
}
