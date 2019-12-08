#include <iostream>
#include <cassert>
#include <map>

using std::map;
using std::cout;
using std::endl;

struct ListNode {
  ListNode* next;
  int val;
  int padding;
  ListNode(int _val=0) : next(nullptr), val(_val), padding(0) {  }
};

typedef ListNode* pNode;

// no circle in list
bool intersect(pNode head1, pNode head2) {
  assert(head1!= nullptr && head2 != nullptr);
  while (head1->next != nullptr) {
    head1 = head1->next;
  }
  while (head2->next != nullptr) {
    head2 = head2->next;
  }
  if (head1 == head2) {
    return true;
  }
  return false;
}

// use map
bool hasLoop_1(pNode head) {
  map<pNode, int> m;
  pNode current = head;
  while (current != nullptr) {
    if (m.find(current) == m.end()) {
      m[current] = 1;
      current = current->next;
    } else {
      return true;
    }
  }
  return false;
}

// use a fast pointer, a slow pointer
bool hasLoop_2(pNode head, pNode& loopNode) {
  pNode fast = head, slow = head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {
      loopNode = fast;
      return true;
    }
  }
  return false;
}

/*
 * list length: L,
 * loop length: r,
 * slow step by 1, fast step by 2, when slow encounter fast,
 * slow go through s steps, fast go through 2s steps,
       delta = nr = 2s - s = s
 * from head to entrance of loop: a,
 * from entrance of loop to encounter pointer: x
       s = a + x = (n - 1)r + r = (n - 1)r + L - a
       a =  (n - 1)r + (L - a -x)
 * from encounter pointer to entrance of loop: (L - a - x)
 */
pNode findLoopPoint(pNode head) {
  pNode fast = head, slow = head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {  // has loop, fast now at the intersection pointer
      break;
    }
  }
  if (fast == nullptr || fast->next == nullptr) {
    return nullptr;
  }
  slow = head;  // slow at head, fast at the intersection pointer
  while (slow != fast) {
    slow = slow->next;
    fast = fast->next;
  }
  return slow;
}

bool detect(pNode head1, pNode head2) {
  pNode loopNode1, loopNode2;

  bool hasLoop1 = hasLoop_2(head1, loopNode1);
  bool hasLoop2 = hasLoop_2(head2, loopNode2);

  if (hasLoop1 != hasLoop2) {
    cout << "one cycle, one not" << endl;
    return false;
  } else if (!hasLoop1 && !hasLoop2) {  //  neither has loop
    return intersect(head1, head2);
  } else {
    cout << "two cycle" << endl;
    pNode ptr = loopNode1->next;
    while (ptr != loopNode1) {
      if (ptr == loopNode2) {
        return true;
      }
      ptr = ptr->next;
    }
    return loopNode1 == loopNode2;
  }
}

bool printList(pNode head) {
  map<pNode, int> m;
  pNode ptr = head;
  if (ptr == nullptr) return false;
  while (ptr!= nullptr) {
    if (m.find(ptr) == m.end()) {
      m[ptr] = 1;
      cout << ptr->val << ", ";
      ptr = ptr->next;
    } else {
      break;
    }
  }
  cout << endl;
  return true;
}

pNode createList() {
  pNode head = new ListNode();
  pNode ptr = head;
  pNode pInter = nullptr;  // loop entrance node
  for (int i = 2; i < 10; i += 2) {
    pNode tmp = new ListNode(i);
    ptr->next = tmp;
    ptr = ptr->next;
    if (i == 8) pInter = tmp;
  }
  for (int j = 10; j >8; --j) {
    pNode tmp = new ListNode(j);
    ptr->next = tmp;
    ptr = ptr->next;
  }
  ptr->next = pInter;

  return head;
}

int main() {
  pNode lst = createList();
  printList(lst);

  if (hasLoop_1(lst)) {
    cout << "has loop" << endl;
  } else {
    cout << "no loop" << endl;
  }

  pNode pInter = findLoopPoint(lst);
  cout << pInter->val << endl;

  return 0;
}
