/* test_spalytree2.cpp */

#include "splaytree2.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  cout << "================================" << endl;

  splay_tree<int>* ptree = new splay_tree<int>;
  int arr[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
  int len  = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < len; ++i) {
    ptree->insert(arr[i]);
  }
  ptree->empty() ? cout << "Empyt\n" : cout << "Not empyt\n";
  cout << "Size: " << ptree->size() << endl;
  ptree->print();  cout << endl;
  delete ptree;
  ptree = nullptr;
  cout << "--------------------------------" << endl;

  splay_tree<int> tree;
  tree.insert(10);
  tree.insert(10);
  tree.insert(20);
  tree.insert(60);
  tree.insert(50);
  tree.insert(30);
  tree.insert(40);
  tree.empty() ? cout << "Empyt\n" : cout << "Not empyt\n";
  cout << "Size: " << tree.size() << endl;
  tree.print();  cout << endl;
  tree.erase(10);
  tree.print();  cout << endl;
  
  cout << "================================" << endl;
  return 0;
}
