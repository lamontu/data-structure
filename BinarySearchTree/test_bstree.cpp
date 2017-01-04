/* test_bstree.cpp */

#include "bstree.h"
#include <iostream>

using namespace std;

void visit(const int& a) {
  cout << a << ", ";
}

typedef void(*Funtype)(const int&);
Funtype pfun = visit;

int main(int argc, char* argv[]) {
  cout << "================================" << endl;

  BSTree<int> bst(nullptr);
  int LevelOrder[] = {12, 6, 18, 3, 10, 15, 21};
  bst.Create1(LevelOrder, 7, 100);
  bst.IsEmpty() ? cout << "Empty \n" : cout << "Not empty \n";
  cout << "Root data: " << bst.Root()->data << endl;
  cout << "Nodes count: " << bst.NodesCount() << endl;
  cout << "Leaf count: " << bst.LeafCount() << endl;
  cout << "Depth: " << bst.Depth() << endl;
  cout << "### Level order traverse:" << endl;
  bst.LevelOrderTraverse(pfun);  cout << endl;
  cout << "### In Order Traverse:" << endl;
  bst.InOrderTraverse(pfun);  cout << endl;

  BTNode<int>* bmin = bst.FindMin();
  cout << "minimum data: " << bmin->data << endl;
  BTNode<int>* bmax = bst.FindMax();
  cout << "maximum data: " << bmax->data << endl;

  BTNode<int>* p10 = bst.Find(10);
  cout << "p10: " << p10->data << endl;
  BTNode<int>* suc10 = bst.Successor(p10);
  cout << "suc10: " << suc10->data << endl;

  BTNode<int>* p15 = bst.Find(15);
  cout << "p15: " << p15->data << endl;
  BTNode<int>* pre15 = bst.Predecessor(p15);
  cout << "pre15: " << pre15->data << endl;

  BTNode<int>* p2 = bst.Insert(2);
  cout << "Insert p2: " << p2->data << endl;
  BTNode<int>* bmin2 = bst.FindMin();
  cout << "New minimum data: " << bmin2->data << endl;

  BTNode<int>* p6 = bst.Find(6);
  cout << "p6: " << p6->data << endl;
  BTNode<int>* p6_parent = bst.Parent(p6);
  cout << "p6_parent: " << p6_parent->data << endl;
  BTNode<int>* p6_rsibling = bst.RightSibling(p6);
  cout << "p6 right sibling: " << p6_rsibling->data << endl;

  BTNode<int>* pnode = bst.DetachLeft();
  BSTree<int> bst6(pnode);
  BTNode<int>* p6min = bst6.FindMin();
  cout << "minimum data of bst6: " << p6min->data << endl;
  bst6.Insert(7);
  bst6.Insert(8);
  cout << "Root data: " << bst6.Root()->data << endl;
  cout << "Nodes count: " << bst6.NodesCount() << endl;
  cout << "Leaf count: " << bst6.LeafCount() << endl;
  cout << "Depth: " << bst6.Depth() << endl;
  bst6.Delete(6);
  cout << "Root data: " << bst6.Root()->data << endl;
  cout << "Nodes count: " << bst6.NodesCount() << endl;
  cout << "Leaf count: " << bst6.LeafCount() << endl;
  cout << "Depth: " << bst6.Depth() << endl;
  cout << "Level order traverse:" << endl;
  bst6.LevelOrderTraverse(pfun);  cout << endl;
  bst6.InOrderTraverse(pfun);  cout << endl;

  cout << "================================" << endl;
  return 0;
}
