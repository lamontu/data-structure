/* test_methods.cpp
 * Test operations of class BinaryTree
 */

#include <iostream>
#include "binarytree.h"

using namespace std;

void visit(const int& a) {
  cout << a << ", ";
}

typedef void(* Funtype)(const int&);
Funtype pfun = visit;

int main(int argc, char* argv[]) {
  cout << "================================" << endl;

  cout << "# Create a BinaryTree object from arrays ------" << endl;
  int LevelOrder[] = {1, 2, 3, 4, 5, 6, 7};
  int PreOrder[] = {1, 2, 4, 5, 3, 6, 7};
  int InOrder[] = {4, 2, 5, 1, 6, 3, 7};  
/*
  cout << "## Create a tree using a PreOrderTraverse array "
       << "and an InOrderTraverse array:" << endl;
  BinaryTree<int> bt;
  bt.Create2(PreOrder, InOrder, 7);
*/
  cout << "## Create a tree from a level order traverse result:" << endl;
  BinaryTree<int> bt;
  bt.Create1(LevelOrder, 7, 100);
 
  bt.IsEmpty() ? cout << "Empty \n" : cout << "Not empty \n";
  cout << "Root data: " << bt.Root()->data << endl;
  cout << "Nodes count: " << bt.NodesCount() << endl;
  cout << "Leaf count: " << bt.LeafCount() << endl;
  cout << "Depth: " << bt.Depth() << endl;
  cout << "### Level order traverse:" << endl;
  bt.LevelOrderTraverse(pfun);  cout << endl;
  cout << "### Travserse without using recursion:" << endl;
  bt.PreOrderTraverse(pfun);  cout << endl;
  bt.InOrderTraverse(pfun);  cout << endl;
  bt.PostOrderTraverse(pfun);  cout << endl;
  cout << "### Traverse using recursion:" << endl;
  bt.PreOrderTraverseRec(pfun);  cout << endl;
  bt.InOrderTraverseRec(pfun);  cout << endl;
  bt.PostOrderTraverseRec(pfun);  cout << endl;

  BTNode<int>* father = bt.Parent(bt.Root());
  if (father == nullptr) {
    cout << "Parent of root: nullptr" << endl;
  }
 

  cout << "LeftChild: " << bt.LeftChild()->data << endl;
  cout << "RightChild: " << bt.RightChild()->data << endl;

  BTNode<int>* p3 = bt.Locate(3);
  cout << "p3: " << p3->data << endl;
  BTNode<int>* p3_parent = bt.Parent(p3);
  cout << "p3 parent: " << p3_parent->data << endl;
  BTNode<int>* p3_lsibling = bt.LeftSibling(p3);
  cout << "p3 left sibling: " << p3_lsibling->data << endl;
/* Assertion failed
  BTNode<int>* p3_rsibling = bt.RightSibling(p3);
  cout << "p3 right sibling: " << p3_rsibling->data << endl;
 */
  
  cout << "### Detach left child:" << endl;
  bt.DetachLeft();
  bt.LeftChild() ? cout << "Has LeftChild\n" : cout << "No LeftChild\n";

  cout << "### Set left child:" << endl;
  BTNode<int>* p20 = new BTNode<int>(20, nullptr, nullptr);
  bt.SetLeft(p20);
  cout << "LeftChild: " << bt.LeftChild()->data << endl;
  cout << "Nodes count: " << bt.NodesCount() << endl;
  cout << "Leaf count: " << bt.LeafCount() << endl;
  cout << "Depth: " << bt.Depth() << endl;

  cout << "## Set right child:" << endl;
  BTNode<int>* p30 = new BTNode<int>(30, nullptr, nullptr);
  bt.SetRight(p30);
  cout << "RightChild: " << bt.RightChild()->data << endl;
  cout << "Nodes count: " << bt.NodesCount() << endl;
  cout << "Leaf count: " << bt.LeafCount() << endl;
  cout << "Depth: " << bt.Depth() << endl;

  cout << "## Detach right child:" << endl;
  bt.DetachRight();
  bt.RightChild() ? cout << "Has RightChild\n" : cout << "No RightChild\n";
  cout << "Nodes count: " << bt.NodesCount() << endl;
  cout << "Leaf count: " << bt.LeafCount() << endl;
  cout << "Depth: " << bt.Depth() << endl;

  cout << "================================" << endl;
  return 0;
}
