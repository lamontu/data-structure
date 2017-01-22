/* lca.cpp
 * Lowest Common Ancestor (LCA)
 */

#include <iostream>
#include <cmath>

using namespace std;

struct Node {
  int key;
  Node* left;
  Node* right;
};

Node* NewNode(int key) {
  Node* node = new Node;
  node->key = key;
  node->left = node->right = nullptr;
  return node;
}

/* Range minimum query */

const int MAXN = 10000;
const int LOGMAXN = 20;
int index_min[MAXN][LOGMAXN];

void InitIndexMin(int arr[], int len) {
  int i, j;
  for (i = 0; i < len; ++i) {
    index_min[i][0] = i;
  }
  for (j = 1; (1 << j) <= len; ++j) {
    for (i = 0; i + (1 << j) - 1 < len; ++i) {
      if (arr[index_min[i][j-1]] < arr[index_min[i+(1<<(j-1))][j-1]]) {
        index_min[i][j] = index_min[i][j-1];
      } else {
        index_min[i][j] = index_min[i+(1<<(j-1))][j-1];
      }
    }
  }
}

int GetMinIndex(int arr[], int left, int right) {
  int res;
  if (left > right) {
    cout << "Invalid interval!" << endl;
    exit(1);
  }
  int k = (int)((log((double)(right-left+1))) / log(2.0));
  if (arr[index_min[left][k]] < arr[index_min[right-(1<<k)+1][k]]) {
    res = index_min[left][k];
  } else {
    res = index_min[right-(1<<k)+1][k];
  }
  return res;
}

/* Lowest common ancestor */

const int V = 9;  // Number of nodes
int Euler[2*V-1];
int Level[2*V-1];
int Occurrence[V+1];  // If the key can not be used as index, use map.
int Index;

void EulerTour(Node* root, int level) {
  if (nullptr == root) return;

  Euler[Index] = root->key;
  Level[Index] = level;
  Index++;

  if (Occurrence[root->key] == -1) {
    Occurrence[root->key] = Index - 1;
  }

  if (root->left) {
    EulerTour(root->left, level + 1);
    Euler[Index] = root->key;
    Level[Index] = level;
    Index++;
  }
  if (root->right) {
    EulerTour(root->right, level + 1);
    Euler[Index] = root->key;
    Level[Index] = level;
    Index++;
  }
}

int FindLca(Node* root, int u, int v) {
  memset(Occurrence, -1, sizeof(int) * (V + 1));
  Index = 0;
  EulerTour(root, 0);

  if (Occurrence[u] > Occurrence[v]) {
    swap(u, v);
  }
  int query_start = Occurrence[u];
  int query_end = Occurrence[v];

  InitIndexMin(Level, 2*V-1);

  int pos = GetMinIndex(Level, query_start, query_end);

  return Euler[pos];
}

int main(int argc, char* argv[]) {
  Node* root = NewNode(1);
  root->left = NewNode(2);
  root->right = NewNode(3);
  root->left->left = NewNode(4);
  root->left->right = NewNode(5);
  root->right->left = NewNode(6);
  root->right->right = NewNode(7);
  root->left->right->left = NewNode(8);
  root->left->right->right = NewNode(9);

  int u = 4, v = 9;
  int ans = FindLca(root, u, v);
  cout << ans << endl;

  return 0;
}
