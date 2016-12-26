#include <iostream>

using namespace std;

struct ListNode {
  int data;
  ListNode* next;
};

typedef ListNode* LinkList;

/* List L contains head node followed by first data node.
 * The next member in the last data node is a pointer pointing to the head node.
 * List name L is a pointer pointing to the last node pointer.
 * The last node is the head node if there is no data node.
 */
void InitList(LinkList* L) {
  *L = (LinkList)malloc(sizeof(ListNode));  // malloc for head node
  if (*L == nullptr) {
    exit(0);
  }
  (*L)->next = *L;
  cout << "List was initialized." << endl;
}

void ClearList(LinkList* L) {
  LinkList p, q;
  *L = (*L)->next;  // L is pointing to head node pointer. 
  p = (*L)->next;  // p is pointing to the first data node.
  while (p != *L) {
    q = p->next;
    free(p);
    p = q;
  }
  (*L)->next = *L;
  cout << "List is clear." << endl; 
}

void DestroyList(LinkList* L) {
  ClearList(L);
  free(*L);  // *L is a pointer pointing to the head node.
  *L = nullptr;
  cout << "List is destroyed." << endl;
}

bool ListEmpty(LinkList L) {
  return L->next == L;
}

int ListLength(LinkList L) {  // L is the last node pointer
  LinkList p = L->next->next;  // p is pointing to the first data node.
  int j = 0;
  while (p != L->next) {  // while p is not head node pointer
    ++j;
    p = p->next;
  }
  return j;
}

void GetElem(LinkList L, int loc, int* pvalue ) {
  LinkList p = L->next;  // p is pointing to head node.
  int j = 0;
  if ( loc < 1 || loc > ListLength(L)) {  // if loc is invalid
    cout << "Invalid location" << endl;
    exit(0);
  }
  while (j < loc) {
    ++j;
    p = p->next; 
  }
  *pvalue = p->data;
}

int LocateElem(LinkList L, int value) {
  LinkList p = L->next->next;  // p is pointing to the first data node. 
  int j = 0;
  while (p != L->next) {  // while p is not head node pointer
    ++j;
    if (p->data == value) {
      return j;   
    }
    p = p->next; 
  }
  return -1;
}

bool PriorElem(LinkList L, int cur_data, int* pri_data) {
  LinkList p = L->next->next;
  LinkList q;
  while (p != L->next) {
    q = p->next;
    if (q != L->next && q->data == cur_data) {
      *pri_data = p->data;
      return true;
    }
    p = q; 
  }
  return false;
}

bool NextElem(LinkList L, int cur_data, int* nex_data) {
  LinkList p = L->next->next;
  LinkList q;
  while (p != L->next) {
    q = p->next;
    if (q != L->next && p->data == cur_data) {
      *nex_data = q->data;
      return true;
    }
    p = q;
  }
  return false;
}

void ListInsert(LinkList* L, int loc, int value) {
  LinkList p = (*L)->next;  // p is pointing to the head node.
  LinkList q, s;
  int j = 0;
  if (loc < 1 || loc > ListLength(*L) + 1) {
    cout << "Invalid location" << endl;
    exit(0);
  }
  while (j < loc - 1) {
    ++j;
    p = p->next;
  }
  q = p->next;  // q is pointing to the node at location loc.  
  s = (LinkList)malloc(sizeof(ListNode));
  if (s == nullptr) {
    exit(0);
  }
  s->data = value;
  s->next = q;
  p->next = s;
  if (p == *L) {
    *L = s;
  }
}

void ListDelete(LinkList* L, int loc, int* pvalue) {
  LinkList p = (*L)->next;
  LinkList q;
  int j = 0;
  if (loc < 1 || loc > ListLength(*L)) {
    cout << "Invalid location" << endl;
    exit(0);
  }
  while (j < loc - 1) {
    ++j;
    p = p->next; 
  }
  q = p->next;
  *pvalue = q->data;
  p->next = q->next;
  if (q == *L) {
    *L = p;
  }
  free(q);
}

void TravelList(LinkList L) {
  LinkList p = L->next->next;
  int j = 0;
  while (p != L->next) {
    ++j;
    cout <<"#" << j << " node: " << p->data << endl;
    p = p->next;
  }
}

int main(int argc, char* argv[]) {
  LinkList lst;
  InitList(&lst);  // This call is necessary, or segmentation fault: 11

  if (ListEmpty(lst)) {
    cout << "List is empty." << endl;
  }

  for (int i = 1; i < 10; ++i) {
    ListInsert(&lst, i, i * 10);
  }

  cout << "List length is " << ListLength(lst) << "." << endl;

  TravelList(lst);

  int val = 0;
  GetElem(lst, 3, &val);
  cout << val << endl;

  int loc = LocateElem(lst, 40);
  cout << loc << endl;

  int prior = 0;
  PriorElem(lst, 60, &prior);
  cout << prior << endl;

  int next = 0;
  NextElem(lst, 60, &next);
  cout << next << endl;

  int deldata = 0;
  ListDelete(&lst, 8, &deldata);
  cout << "Deleted data is " << deldata << "." << endl;
  cout << "After delete a node:" << endl;
  TravelList(lst);

  ListInsert(&lst, 8, 88);
  cout << "After insert a node:" << endl;
  TravelList(lst);

  // GetElem(lst, 0, &val);

  DestroyList(&lst);

  return 0;
}
