
/* Total nodes number: n
   Leaf nodes number: n0
   Nodes number with degree 2: n2
   n = n0 + n1 + n2 = n0 + n2,
   total node num = children num + root num = (1 * n1 + 2 * n2) + 1 = n
   n0 = n2 + 1
   The degree of a node shall be 0 or 2, not 1
   n = 2 * n0 - 1
 */

#include <algorithm>
#include <iostream>
#include <climits>

using std::min;
using std::max;
using std::cout;
using std::endl;

const int MAXNUM = 1000;

struct SegTreeNode {
  int val;  // minimum value of an interval
  int add_mark;
} SegTree[MAXNUM];

void build(int root, int arr[], int istart, int iend) {
  SegTree[root].add_mark = 0;
  if (istart == iend) {
    SegTree[root].val = arr[istart];
  } else {
    int mid = (istart + iend) / 2;
    build(root*2+1, arr, istart, mid);  // Build left subtree
    build(root*2+2, arr, mid+1, iend);  // Build right subtree
    // Update node value based on its left subtree and right subtree
    SegTree[root].val = min(SegTree[root*2+1].val, SegTree[root*2+2].val);
  }
}

// Update left subtree and right subtree
void pushdown(int root) {
  if (SegTree[root].add_mark != 0) {
    // Set add_mark of the left and right subtree
    SegTree[root*2+1].add_mark += SegTree[root].add_mark;
    SegTree[root*2+2].add_mark += SegTree[root].add_mark;
    // Set val of the left and right subtree
    SegTree[root*2+1].val += SegTree[root].add_mark;
    SegTree[root*2+2].val += SegTree[root].add_mark;
    // Clear the add_mark of current node
    SegTree[root].add_mark = 0;
  }
}

int query(int root, int nstart, int nend, int qstart, int qend) {
  // No intersection between quired interval and current node interval
  if (qstart > nend || qend < nstart) {
    return INT_MAX;
  }
  // Quired interval covers the current node interval
  if (qstart <= nstart && qend >= nend) {
    return SegTree[root].val;
  }

  pushdown(root);  // push down the add_mark
  int mid = (nstart + nend) / 2;
  return min(query(root*2+1, nstart, mid, qstart, qend),
             query(root*2+2, mid+1, nend, qstart, qend));
}

void update_one(int root, int nstart, int nend, int index, int increment) {
  if (nstart == nend) {
    if (index == nstart) {
      SegTree[root].val += increment;
      return;
    }
  }
  int mid = (nstart + nend) / 2;
  if (index <= mid) {
    update_one(root*2+1, nstart, mid, index, increment);
  } else {
    update_one(root*2+2, mid+1, nend, index, increment);
  }
  SegTree[root].val = min(SegTree[root*2+1].val, SegTree[root*2+2].val);
}

void update(int root, int nstart, int nend,
            int ustart, int uend, int increment) {
  // No intersection between target interval and current node interval
  if (ustart > nend || uend < nstart) return;

  /* Target interval covers the current node interval
   * Update and stop at this layer
   */
  if (ustart <=nstart && uend >= nend) {
    SegTree[root].add_mark += increment;
    SegTree[root].val += increment;
    return;  // It is necessary.
  }

  pushdown(root);
  int mid = (nstart + nend) / 2;
  update(root*2+1, nstart, mid, ustart, uend, increment);
  update(root*2+2, mid+1, nend, ustart, uend, increment);
  SegTree[root].val = min(SegTree[root*2+1].val, SegTree[root*2+2].val);
}


int main(int argc, char* argv[]) {
  cout << "========================================" << endl;

  /*
   array = {2, 5, 1, 4, 9, 3}
   SegTree[0].val = 1, SegTree[1].val = 1, SegTree[2].val = 3

                 [0,5]                  index = 0
                  1
               /     \
           [0,2]      [3,5]      index*2+1    index*2+2
            1          3
         /   \        /  \
     [0,1]   [2]   [3,4]  [5]
      2       1     4      3
     /  \          /  \
  [0]   [1]       [3] [4]
   2     5         4   9

   */

  int arr[] = {2, 5, 1, 4, 9, 3};
  int SegLenth = 9;
  int len = sizeof(arr) / sizeof(arr[0]);
  cout << "arr: ";
  for (int i = 0; i < len; ++i) {
    cout << arr[i] << ", ";
  }
  cout << endl;
  build(0, arr, 0, 5);
  for (int i = 0; i < 4 * len; ++i) {
    cout << SegTree[i].val << ", ";
  }
  cout << endl;
  int q1, q2, q3, q4;

  q1 = query(0, 0, 5, 0, 2);
  cout << "minimum in [0 2]: " << q1 << endl;
  q2 = query(0, 0, 5, 3, 5);
  cout << "minimum in [3, 5]: " << q2 << endl;
  q3 = query(0, 0, 5, 1, 4);
  cout << "minimum in [1, 4]: " << q3 << endl;
  q4 = query(0, 0, 5, 6, 7);
  cout << "minimum in [6, 7]: " << q4 << endl;

/*
  cout << "update one node: " << endl;
  update_one(0, 0, 5, 2, 6);
  q1 = query(0, 0, 5, 0, 2);
  cout << "minimum in [0 2]: " << q1 << endl;
  q2 = query(0, 0, 5, 3, 5);
  cout << "minimum in [3, 5]: " << q2 << endl;
  q3 = query(0, 0, 5, 1, 4);
  cout << "minimum in [1, 4]: " << q3 << endl;
  q4 = query(0, 0, 5, 6, 7);
  cout << "minimum in [6, 7]: " << q4 << endl;
 */
  cout << "update [2, 4] add 2:" << endl;
  update(0, 0, 5, 2, 4, 2);
  q1 = query(0, 0, 5, 0, 2);
  cout << "minimum in [0 2]: " << q1 << endl;
  q2 = query(0, 0, 5, 3, 5);
  cout << "minimum in [3, 5]: " << q2 << endl;
  q3 = query(0, 0, 5, 1, 4);
  cout << "minimum in [1, 4]: " << q3 << endl;
  q4 = query(0, 0, 5, 6, 7);
  cout << "minimum in [6, 7]: " << q4 << endl;

  cout << "========================================" << endl;
  return 0;
}
