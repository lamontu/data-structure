#include <iostream>
#include "stackarray.h"

using namespace std;

int main(int argc, char* argv[]) {
  StackArray<int> stk(5);
  stk.IsEmpty() ? cout << "empty\n" : cout << "not empty\n";
  cout << "Count: " << stk.GetCount() << endl;
  stk.IsFull() ? cout << "full" : cout << "not full" << endl;

  stk.Push(0);
  stk.Push(1);
  stk.Push(2);
  stk.Push(3);
  stk.Push(4);
  stk.IsEmpty() ? cout << "empty\n" : cout << "not empty\n";
  stk.IsFull() ? cout << "full\n" : cout << "not full\n";
  cout << "Count: " << stk.GetCount() << endl;

  cout << "## push when stack is full:" << endl;
  stk.Push(5) ? cout << "push successfully\n" : cout << "push failed\n";

  cout << "## stk.Resize(10):" << endl;
  stk.Resize(10);
  stk.IsFull() ? cout << "full\n" : cout << "not full\n";

  stk.Push(5) ? cout << "push successfully\n" : cout << "push failed\n";
  cout << "Count: " << stk.GetCount() << endl;
  int topval = 100;
  stk.Top(&topval);
  cout << "Top: " << topval << endl;


  int popval = -100;
  stk.Pop(&popval);
  cout << "Pop out: " << popval << endl;
  cout << "Count: " << stk.GetCount() << endl;

  stk.Top(&topval);
  cout << "Top: " << topval << endl;

  cout << "## test copy constructor:" << endl;
  StackArray<int> stk2(stk);
  cout << "Count: " << stk2.GetCount() << endl;
  stk2.Push(5);
  cout << "Count: " << stk2.GetCount() << endl;
  stk2.Top(&topval);
  cout << "Top: " << topval << endl;

  cout << "## test copy assginment:" << endl;
  StackArray<int> stk3(6);
  stk3 = stk;
  stk3.IsFull() ? cout << "full\n" : cout << "not full\n";
  stk3.Top(&topval);
  cout << "Top: " << topval << endl;

  StackArray<int> stk4(10);
  stk4 = stk2;

  cout << "## test MakeEmpty():" << endl;
  stk4.MakeEmpty();
  stk4.IsEmpty() ? cout << "empty\n" : cout << "not empty\n";

  return 0;
}
