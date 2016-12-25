#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int _val=0) : val(_val), next(nullptr) {  } 
};

typedef ListNode* pNode;

// iteration
pNode reverse_iter_1(pNode head) {
  pNode current = head;
  pNode next = nullptr, result = nullptr;
  while (current != nullptr) {
    next = current->next;
    current->next = result;
    result = current;
    current = next;
  }
  return result; 
}

// iteration
void reverse_iter_2(pNode& head) {
  pNode current = head;
  pNode next = nullptr, result = nullptr;
  while (current != nullptr) {
    next = current->next;
    current->next = result;
    result = current;
    current = next;
  } 
  head = result;
}

// recursion
void reverse_recur(pNode& p) {
  if (!p) return;
  pNode rest = p->next;
  reverse_recur(rest);
  p->next->next = p;
  p->next = nullptr;
  p = rest;    
}

int main(int argc, char* argv[]) {
  return 0;
}
