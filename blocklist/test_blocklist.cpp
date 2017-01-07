/* test_blocklist.cpp */

#include "blocklist.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  cout << "================================" << endl;
  Block<char> bk(nullptr, nullptr);
  char array[] = "This is a test string for BlockList.";
  int len = strlen(array);

  BlockList<char>* plst = new BlockList<char>;
  plst->insert(array, len);
  plst->get(len);
  delete plst;
  cout << "--------------------------------" << endl;

  BlockList<char> lst; 
  lst.insert(array, len); 
  lst.get(11);
  lst.moveKth(11);
  lst.get(8);
  lst.Prev();
  lst.get(8);
  lst.Next();
  lst.get(8);
  lst.erase(4);
  lst.get(8);
 
  cout << "================================" << endl;
  return 0;
}
