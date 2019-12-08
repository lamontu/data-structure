#include <iostream>
#include "dlist.h"

using namespace std;

int main() {
  DList<int> lst;
  if (lst.IsEmpty()) {
    cout << "List is empty." << endl;
  }
  lst.InsertBefore(1, 10);
  cout << lst.GetAt(1) << endl;
  lst.InsertAfter(1, 20);
  cout << lst.GetAt(2) << endl;
  cout << lst.GetCount() << endl;

  lst.AddHead(0);
  cout << lst.GetAt(1) << endl;
  lst.AddTail(30);
  cout << lst.GetAt(4) << endl;
  lst.RemoveHead();
  cout << lst.GetHead() << endl;
  lst.RemoveTail();
  cout << lst.GetTail() << endl;

  lst.InsertAfter(2, 300);
  cout << lst.GetAt(3) << endl;

  cout << lst.Find(400) << endl;
  cout << lst.Find(300) << endl;

  cout << lst.GetTail() << endl;
  lst.Invert();
  cout << lst.GetTail() << endl;

  cout << "## convert DList<int> to const DList<int>:" << endl;
  const DList<int> lst2 = (const DList<int>)lst;
  cout << "## test GetAt():" << endl;
  Node<int> node1 = lst.GetAt(1);
  cout << node1.data << endl;
  cout << "## test GetAt() const:" << endl;
  Node<int> node2 = lst2.GetAt(1);
  cout << node2.data << endl;

  return 0;
}
