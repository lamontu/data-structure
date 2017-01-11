/* bucket_sort2.cpp */

#include <iostream>
#include <iomanip>

using namespace std;

const int NARRAY = 8;
const int NBUCKET = 5;
const int INTERVAL = 10;

struct BucketNode {
  int data;
  BucketNode* next;
};

void bucket_sort(int arr[]);
BucketNode* insertion_sort(BucketNode* list);
void print(int arr[]);
void printBuckets(BucketNode* list);
int getBucketIndex(int value);

void bucket_sort(int arr[]) {
  int i, j;
  BucketNode** buckets;
  buckets = (BucketNode**)malloc(sizeof(BucketNode*) * NBUCKET);
  // Initialize buckets
  for (i = 0; i < NBUCKET; ++i) {
    buckets[i] = nullptr;
  }
  // Put items into buckets
  for (i = 0; i < NARRAY; ++i) {
    BucketNode* current;
    int pos = getBucketIndex(arr[i]);
    current = (BucketNode*)malloc(sizeof(BucketNode));
    current->data = arr[i];
    current->next = buckets[pos];
    buckets[pos] = current;
  }
  // Check what's in each bucket
  for (i = 0; i < NBUCKET; ++i) {
    cout << "Bucket[" << i << "] : ";
    printBuckets(buckets[i]);
    cout << endl;
  }
  // Sort buckets using insertion sorting
  for (i = 0; i <NBUCKET; ++i) {
    buckets[i] = insertion_sort(buckets[i]);
  }
  // Check what's in each buckets
  cout << "----------------------------------------" << endl;
  cout << "Buckets after sorted:" << endl;
  for (i = 0; i < NBUCKET; ++i) {
    cout << "Bucket[" << i << "] : ";
    printBuckets(buckets[i]);
    cout << endl;
  }
  // Put items back to original array
  for (j = 0, i = 0; i < NBUCKET; ++i) {
    BucketNode* pnode;
    pnode = buckets[i];
    while (pnode) {
      arr[j++] = pnode->data;
      pnode = pnode->next;
    }
  }
  // Free memory
  for (i = 0; i < NBUCKET; ++i) {
    BucketNode* pnode;
    pnode = buckets[i];
    while (pnode) {
      BucketNode* temp = pnode;
      pnode = pnode->next;
      free(temp);
    }
  }
  free(buckets);
  return;
}

BucketNode* insertion_sort(BucketNode* list) {
  BucketNode *k, *res_list;
  if (nullptr == list || nullptr == list->next) return list;
  res_list = list;
  k = list->next;
  res_list->next = nullptr;
  while (k != nullptr) {
    BucketNode* ptr;
    // Check if insert before first node
    if (res_list->data > k->data) {
      BucketNode* temp;
      temp = k;
      k = k->next;
      temp->next = res_list;
      res_list = temp;
      continue;
    }
    // Find insertion position in res_list
    for (ptr = res_list; ptr->next != nullptr; ptr = ptr->next) {
      if (ptr->next->data > k->data) break;
    }
    if (ptr->next != nullptr) {
      BucketNode* temp;
      temp = k;
      k = k->next;
      temp->next = ptr->next;
      ptr->next = temp;
      continue;
    } else {
      ptr->next = k;
      k = k->next;
      ptr->next->next = nullptr;
      continue;
    }
  }
  return res_list;
}

int getBucketIndex(int value) {
  return value / INTERVAL;
}

void print(int arr[]) {
  for (int i = 0; i < NARRAY; ++i) {
    cout << setw(3) << arr[i];
  }
  cout << endl;
}

void printBuckets(BucketNode* list) {
  BucketNode* cur = list;
  while (cur) {
    cout << setw(3) << cur->data;
    cur = cur->next;
  }
}

int main(int argc, char* argv[]) {
  int array[NARRAY] = {29, 25, 3, 49, 9, 37, 21, 43};
  cout << "Initial array:" << endl;
  print(array);
  bucket_sort(array);
  cout << "--------------------------------" << endl;
  cout << "Sorted array:" << endl;
  print(array);
  return 0;
}
