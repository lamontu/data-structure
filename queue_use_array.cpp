// queue using array

#include <iostream>
#include <cassert>

using namespace std;

 
class Queue {
 private:
  int* data;
  int head, tail, length, count;

 public:
  Queue(int length_input) {
    data = new int[length_input];
    length = length_input;
    head = 0;
    tail = -1;
    count = 0;
  }

  ~Queue() {
    delete[] data;
  }

  bool push(int element) {
    if (count < length) {
      tail = (tail + 1) % length;
      data[tail] = element;
      count++;
      return true;
    } else {
      return false;
    }
  }

  void pop() {
    assert(head <= tail);
    head++;
  }

  int front() {
    assert(head <= tail);
    return data[head];
  }

  int back() {
    assert(head <= tail);
    return data[tail];
  }

  void output() {
    for (int i = head, c = 0;
         i != tail + 1 && c < count;
         i = (i + 1) % length, ++c) {
      cout << data[i] << ", ";
    }
    cout << endl;
  }

  int getLength() {
    return length;
  }

  int getCount() {
    return count;
  }
};


int main(int argc, char* argv[]) {
  Queue queue(10);
  for (int i = 1; i <= 10; ++i) {
    queue.push(i);
  }
  cout << queue.getLength() << endl;
  cout << queue.getCount() << endl;
  queue.output();
  return 0;
}


