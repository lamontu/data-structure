#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int _val=0) : val(_val), next(nullptr) {  }
};

typedef ListNode* pNode;

/*
pNode newNode(int data) {
  pNode nd = (pNode)malloc(sizeof(ListNode));
  nd->val = data;
  nd->next = nullptr;
  return nd;
}
 */

// traverse
pNode copyList_traversal(pNode head) {
  pNode current = head;
  pNode newList = nullptr, tail = nullptr;
  while (current != nullptr) {
    if (newList == nullptr) {
      newList =  new ListNode(current->val);
      tail = newList;
    } else {
      tail->next = new ListNode(current->val);
      tail = tail->next;
    }
    current = current->next;
  }
  return newList;
}

// recursion
pNode copyList_recursive(pNode head) {
  if (head == nullptr) {
    return nullptr;
  } else {
    pNode newList = new ListNode(head->val);
    newList->next = copyList_recursive(head->next);
    return newList; 
  }
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
  /*
   * pNode head = new ListNode(); 
   * head->val = 0;
   * head->next = nullptr;
   */
  pNode head = new ListNode();

  pNode ptr = head;
  for (int i = 2; i < 10; i += 2) {
    /*
     * pNode tmp = new ListNode();
     * tmp->val = i;
     * tmp->next = nullptr;
     */
    pNode tmp = new ListNode(i);

    ptr->next = tmp;
    ptr = ptr->next;
  }
  return head;
}

int main(int argc, char* argv[]) {
  pNode head = createList();

  if (copyList_traversal(head)) {
    cout << "copyList_traversal finished" << endl; 
    printList(head);
  } else {
    cout << "copyList_traversal failed" << endl;
  }

  if (copyList_recursive(head)) {
    cout << "copyList_recursive finished" << endl; 
    printList(head);
  } else {
    cout << "copyList_recursive failed" << endl;
  }
  
  return 0;
}
