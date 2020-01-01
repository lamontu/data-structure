#include "blocklist.h"

int main() {
  cout << "================================" << endl;
  char array[] = "This is a test string for BlockList.";
  size_t length = strlen(array);

  BlockList<char>* plst = new BlockList<char>;
  plst->insert(array, length);
  plst->get(length);
  delete plst;
  cout << "--------------------------------" << endl;

  BlockList<char> lst;
  lst.insert(array, length);
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
