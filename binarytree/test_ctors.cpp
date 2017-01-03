/* test_ctor.cpp 
 * Test contructor, copy constructor, copy assignment, and destrcutor
 */

#include <iostream>
#include "binarytree.h"

using namespace std;

int main(int argc, char* argv[]) {
  cout << "================================" << endl;

/* Test creating an object #1: OK 
  BTNode<int>* na;
  BinaryTree<int> tree(na);
  (nullptr == na) ? cout << "nullptr == na\n" : cout << "nullptr != na\n";
  tree.IsEmpty() ? cout << "Empty \n" : cout << "Not empty \n";
  // tree.Clear();  // It's OK, but not necessary.
*/

/* Test creating an object #2: OK
  BTNode<int>* nb = new BTNode<int>;
  BinaryTree<int> tree(nb);
  tree.IsEmpty() ? cout << "Empty \n" : cout << "Not empty \n";
  cout << "Root data: " << tree.Root()->data << endl;
  // tree.Clear();  // It's OK, but not necessary.
*/

/* Test creating an object #3: OK
  BTNode<int>* nc = new BTNode<int>{10, nullptr, nullptr};
  // BinaryTree<int> tree(nc);  // Equivalent to below
  BinaryTree<int> tree = nc;
  tree.IsEmpty() ? cout << "Empty \n" : cout << "Not empty \n";
  cout << "Root data: " << tree.Root()->data << endl;
*/

/* Test creating an object #4:
 * Runtime Error:  pointer being freed was not allocated
  BTNode<int>* nc = new BTNode<int>{10, nullptr, nullptr};
  BinaryTree<int> tree1(nc);
  BinaryTree<int> tree2 = nc;
  cout << "Root data: " << tree1.Root()->data << endl;
  cout << "Root data: " << tree2.Root()->data << endl;
*/

/* Test creating a pointer to an object #1: OK
  BTNode<int>* na;
  BinaryTree<int>* ptree = new BinaryTree<int>(na);
  // ptree->Clear();  // Equivalent to below
  delete ptree;
*/

/* Test creating a pointer to an object #2: OK
  BTNode<int>* nb = new BTNode<int>;
  BinaryTree<int>* ptree = new BinaryTree<int>(nb);
  ptree->IsEmpty() ? cout << "Empty \n" : cout << "Not empty \n";
  cout << "Root data: " << ptree->Root()->data << endl;
  // ptree->Clear();  // Equivalent to below
  delete ptree;
*/

/* Test creating a pointer to an object #3: OK
  BTNode<char>* nb = new BTNode<char>;
  BinaryTree<char> tree(nb);
  tree.IsEmpty() ? cout << "Empty \n" : cout << "Not empty \n";
  cout << "Root data: " << tree.Root()->data << endl;
*/

/* ## No runtime error  
  BTNode<int>* na;  // na == nullptr
  BinaryTree<int>* ptree = new BinaryTree<int>(na);
  BinaryTree<int> tree(na);
  //delete ptree;
*/

/* ## Runtime Error: Segmentation fault: 11
  BTNode<int>* nb = new BTNode<int>;
  BinaryTree<int>* ptree = new BinaryTree<int>(nb);
  BinaryTree<int> tree(nb);
  delete ptree;
*/

/* Test copy constuctor #1: OK
  BTNode<int>* na; 
  BinaryTree<int>* ptree = new BinaryTree<int>(na);
  BinaryTree<int> tree(*ptree);
  delete ptree;
*/

/* Test copy constructor #2: OK
  BTNode<int>* nb = new BTNode<int>;
  BinaryTree<int>* ptree = new BinaryTree<int>(nb);
  BinaryTree<int> tree(*ptree);
  delete ptree;
*/

/* Test copy assignment #1: OK
  BTNode<int>* na;
  BinaryTree<int>* ptree = new BinaryTree<int>(na);
  BinaryTree<int> tree;
  tree = *ptree;
  delete ptree;
*/

/* Test copy assignment #2: OK
  BTNode<int>* nb = new BTNode<int>;
  BinaryTree<int>* ptree = new BinaryTree<int>(nb);
  BinaryTree<int> tree;
  tree = *ptree;
  delete ptree;
*/  

  cout << "================================" << endl;
  return 0;
}
