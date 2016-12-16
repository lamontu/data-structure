// queue with two stacks

#include <stack>
#include <iostream>

using namespace std;


class Queue {
 private:
  stack<int> s1, s2;

 public:
  Queue() { cout << "Constructor is called." << endl; }

  void push(int val) {
    s1.push(val);
  }

  void pop() {
    if (s2.empty()) {
      while (!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
      }
    }
    s2.pop();
  }

  int size() {
    return s1.size() + s2.size();
  }

  bool empty() {
    return size() == 0;
  }

  int front() {
    if (s2.empty()) {
      while (!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
      }
    }
    return s2.top();
  }

  int back() {
    if (s1.empty()) {
      while (!s2.empty()) {
        s1.push(s2.top());
        s2.pop();
      }
    }
    return s1.top();
  }

  ~Queue() {
    while (!s1.empty()) {
      s1.pop();
    }
    while (!s2.empty()) {
      s2.pop();
    }
    cout << "Destructor is called." << endl;
  }

  void output() {
    while (!(this->empty())) {
      cout << this->front() << ", ";
      this->pop();
    }
    cout << endl;
  }
};


int main(int argc, char* argv[]) {

  Queue queue = Queue();
  for (int i = 1; i <= 10; ++i) {
    queue.push(i);
  }
  cout << queue.size() << endl;
  queue.output();
  cout << queue.size() << endl;
  return 0;
}


