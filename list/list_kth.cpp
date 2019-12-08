#include <iostream>

using std::cout;
using std::endl;

struct ListNode {
  ListNode* next;
  int val;
  int padding;
  ListNode(int _val=0) : next(nullptr), val(_val), padding(0) { }
};

typedef ListNode* pNode;

int length(pNode head) {
  pNode current = head;
  int count = 0;
  while (current != nullptr) {
    ++count;
    current = current->next;
  }
  return count;
}

pNode getKth_1(pNode head, int k) {
  int n = length(head);
  if (k > n) return nullptr;
  pNode current = head;
  for (int i = 0; i < n - k; ++i) {
    current = current->next;
  }
  return current;
}

pNode getKth_2(pNode head, int k) {
  pNode p1, p2;
  p1 = p2 = head;
  for (; k > 0 && p2 != nullptr; --k) {
    p2 = p2->next;
  }
  if (k > 0) return nullptr;
  while (p2 != nullptr) {
    p1 = p1->next;
    p2 = p2->next;
  }
  return p1;
}

bool printList(pNode head) {
  pNode ptr = head;
  if (ptr == nullptr) return false;
  while (ptr) {
    cout << ptr->val << ", ";
    ptr = ptr->next;
  }
  cout << endl;
  return true;
}

pNode createList() {
  pNode head = new ListNode();
  pNode ptr = head;
  for (int i = 2; i < 10; i += 2) {
    pNode tmp = new ListNode(i);
    ptr->next = tmp;
    ptr = ptr->next;
  }
  return head;
}

int main() {
  pNode head = createList();
  printList(head);

  pNode knd1 = getKth_1(head, 2);
  cout << knd1->val << endl;

  pNode knd2 = getKth_2(head, 3);
  cout << knd2->val << endl;
  return 0;
}
