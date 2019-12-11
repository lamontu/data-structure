
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

const int MAXNUM = 100;

static struct SegTreeNode {
  int val;  // minimum value of an interval
  int add_mark;
} SegTree[MAXNUM];

static void pushup(int root) {
  SegTree[root].val = min(SegTree[root*2+1].val, SegTree[root*2+2].val);
}

// Update left subtree and right subtree
static void pushdown(int root) {
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

static void build(int root, int arr[], int istart, int iend) {
  SegTree[root].add_mark = 0;
  if (istart == iend) {
    SegTree[root].val = arr[istart];
  } else {
    int mid = (istart + iend) / 2;
    build(root*2+1, arr, istart, mid);  // Build left subtree
    build(root*2+2, arr, mid+1, iend);  // Build right subtree
    // Update node value based on its left subtree and right subtree
    pushup(root);
  }
}

static int query(int root, int nstart, int nend, int qstart, int qend) {
  // cout << "root=" << root << ", [" << nstart << "," << nend << "]" << endl;
  // No intersection between query interval and current node interval
  if (qstart > nend || qend < nstart) {
    return INT_MAX;
  }
  // Query interval covers the current node interval
  if (qstart <= nstart && qend >= nend) {
    return SegTree[root].val;
  }

  pushdown(root);  // push down the add_mark
  int mid = (nstart + nend) / 2;
  int lchild = query(root*2+1, nstart, mid, qstart, qend);
  int rchild = query(root*2+2, mid+1, nend, qstart, qend);
  // pushup(root);
  return min(lchild, rchild);
}

static void update_one(int root, int nstart, int nend, int index, int increment) {
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
  pushup(root);
}

static void update(int root, int nstart, int nend,
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
  pushup(root);
}

int main() {
  cout << "========================================" << endl;

  int arr[] = {2, 5, 1, 4, 9, 3, 6};
  int len = sizeof(arr) / sizeof(arr[0]);
  int arr_st = 0;
  int arr_ed = len - 1;
  cout << "arr: ";
  for (int i = 0; i < len; ++i) {
    cout << arr[i] << ", ";
  }
  cout << endl;
  build(0, arr, arr_st, arr_ed);
  for (int i = 0; i < 4 * len; ++i) {
    cout << SegTree[i].val << ", ";
  }
  cout << endl;
  int q1, q2, q3, q4;

  q1 = query(0, arr_st, arr_ed, 0, 2);
  cout << "minimum in [0 2]: " << q1 << endl;
  q2 = query(0, arr_st, arr_ed, 3, 5);
  cout << "minimum in [3, 5]: " << q2 << endl;
  q3 = query(0, arr_st, arr_ed, 1, 4);
  cout << "minimum in [1, 4]: " << q3 << endl;
  q4 = query(0, arr_st, arr_ed, 6, 7);
  cout << "minimum in [6, 7]: " << q4 << endl;

  cout << "update [4, 6] add 2:" << endl;
  update(0, arr_st, arr_ed, 4, 6, 2);
  q1 = query(0, arr_st, arr_ed, 4, 6);
  cout << "minimum in [4, 6]: " << q1 << endl;
  q2 = query(0, arr_st, arr_ed, 3, 5);
  cout << "minimum in [3, 5]: " << q2 << endl;
  q3 = query(0, arr_st, arr_ed, 1, 4);
  cout << "minimum in [1, 4]: " << q3 << endl;
  q4 = query(0, arr_st, arr_ed, 6, 7);
  cout << "minimum in [6, 7]: " << q4 << endl;

  cout << "========================================" << endl;
  return 0;
}
