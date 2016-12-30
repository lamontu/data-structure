/* Test queue created by singly linked list */

#include <iostream>
#include "queuelist.h"

using namespace std;

int main(int argc, char* argv[]) {
  QueueList<int> q;  
  q.IsEmpty() ? cout << "Empty \n" : cout << "Not empty \n";
  q.EnQueue(10);
  q.EnQueue(20);
  q.EnQueue(30);
  q.IsEmpty() ? cout << "Empty \n" : cout << "Not empty \n";
  cout << "Count: " << q.GetCount() << endl;
  cout << "Front: " << q.GetFront() << endl;
  cout << "Rear: " << q.GetRear() << endl;

  cout << "## Test copy contructor:" << endl;
  QueueList<int> q2(q);
  cout << "Count: " << q2.GetCount() << endl;
  cout << "Front: " << q2.GetFront() << endl;
  cout << "Rear: " << q2.GetRear() << endl;
  q2.DeQueue();
  cout << "Count: " << q2.GetCount() << endl;
  cout << "Front: " << q2.GetFront() << endl;
  cout << "Rear: " << q2.GetRear() << endl;
  
  cout << "## Test copy assignment:" << endl;
  QueueList<int> q3(5);
  q3 = q;
  cout << "Count: " << q3.GetCount() << endl;
  cout << "Front: " << q3.GetFront() << endl;
  cout << "Rear: " << q3.GetRear() << endl;

  cout << "## Test MakeEmpty:" << endl;
  q3.MakeEmpty();
  q3.IsEmpty() ? cout << "Empty \n" : cout << "Not empty \n";
   
  return 0;
}
