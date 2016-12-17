// stack

#include <iostream>

using namespace std;


class Stack {
 private:
  int* m_data;
  int m_capacity;
  int m_size;

  void resize(int new_capacity) {
    if (new_capacity <= m_capacity) {
      return;
    }
    int* new_data = new int[new_capacity];
    for (int i = 0; i < m_size; ++i) {
      new_data[i] = m_data[i];
    }
    delete[] m_data;
    m_data = new_data;
    m_capacity = new_capacity;
  }

 public:
  Stack(int capacity=1) {
    m_capacity = capacity;
    m_size = 0;
    m_data = new int[m_capacity];
  }

  void push(int val) {
    if (m_size + 1 >= m_capacity) {
      resize(2 * m_capacity);
    }
    m_data[m_size++] = val;
  }

  void pop() {
    if (m_size > 0) {
      --m_size;
    }
  }

  int top() {
    return m_data[m_size - 1];
  }

  int size() {
    return m_size;
  }

  bool empty() {
    return m_size == 0;
  }

  ~Stack() {
    delete m_data;
  }

  int capacity() {
    return m_capacity;
  }

  void output() {
    for (int i = 0; i < m_size; ++i) {
      cout << m_data[i] << ", ";
    }
    cout << endl;
  }
};


int main(int argc, char* argv[]) {
  Stack st1 = Stack();
  // Stack st1 = Stack;  // Error
  Stack st2;
  Stack* pst1 = new Stack();
  Stack* pst2 = new Stack;
  cout << st1.capacity() << endl;
  cout << st2.capacity() << endl;

  Stack stack = Stack(10);
  for (int i = 1; i <= 10; ++i) {
    stack.push(i);
  }  
  cout << stack.size() << endl;
  cout << stack.capacity() << endl;
  stack.output();

  return 0;
}


