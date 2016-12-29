#include <iostream>
#include "stacklist.h"

using namespace std;

int main(int argc, char* argv[]) {
  StackList<int> stk;
  stk.IsEmpty() ? cout << "Empty\n" : cout << "Not empty\n";

  stk.Push(0);
  stk.Push(1);
  stk.Push(2);
  stk.IsEmpty() ? cout << "Empty\n" : cout << "Not empty\n";
  cout << "Count: " << stk.GetCount() << endl;
  
  int topval = 100;
  stk.Top(&topval);
  cout << "Top: " << topval << endl;

  int popval = -100;
  stk.Pop(&popval);
  cout << "Pop out: " << popval << endl;

  stk.MakeEmpty();
  stk.IsEmpty() ? cout << "Empty\n" : cout << "Not empty\n";

  return 0;
}
