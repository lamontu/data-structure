/* bucket_sort.cpp */

#include <iostream>
#include <cmath>

using namespace std;

const int N = 10;
double input[N+1] = {-1, 0.08, 0.17, 0.39, 0.26, 0.72,
                         0.94, 0.21, 0.12, 0.23, 0.68};

struct BucketNode {
  double data;
  BucketNode* next;
};

typedef BucketNode* BucketList;

BucketList bucket_array[N];

// Result of bucket sorting
void print(BucketList bucket_array[]) {
  for (int i = 0; i < N; ++i) {
    BucketNode* pb = bucket_array[i];
    while (pb) {
      cout << pb->data << ", ";
      pb = pb->next;
    }
    cout << endl;
  }
  cout << endl;
}

void init_bucket(BucketList bucket_array[]) {
  for (int i = 0; i < N; ++i) {
    bucket_array[i] = nullptr;
  }
}

bool insertBucketWithSorting(BucketList& bucket, double data) {
  BucketNode* pnode = new BucketNode;
  if (nullptr == pnode) return false;
  pnode->data = data;
  if (nullptr == bucket || pnode->data < bucket->data) {
    pnode->next = bucket;
    bucket = pnode;
    return true;
  }

  BucketNode* p = bucket;
  BucketNode* q = bucket->next;
  while (q) {
    if (pnode->data < q->data) {
      pnode->next = q;
      p->next = pnode;
      break;
    }
    p = q;
    q = q->next;
  }
  if (nullptr == q) {
    p->next = pnode;
    pnode->next = nullptr;
  }
  return true;
}

void destroy_bucket(BucketList bucket_array[]) {
  for (int i = 0; i < N; ++i) {
    while (bucket_array[i] != nullptr) {
      BucketNode* pnode = bucket_array[i];
      bucket_array[i] = bucket_array[i]->next;
      delete pnode;
      pnode = nullptr;
    }
  }
}

void bucket_sort(double input[], BucketList bucket_array[], int n) {
  for (int i = 1; i <= n; ++i) {
    int index = (int)floor(input[i] * n);
    insertBucketWithSorting(bucket_array[index], input[i]);
  }
}

int main(int argc, char* argv[]) {
  init_bucket(bucket_array);
  bucket_sort(input, bucket_array, N);
  print(bucket_array);
  destroy_bucket(bucket_array);

  return 0;
}
