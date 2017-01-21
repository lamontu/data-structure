/* rmq.cpp
 * Range Minimum/Maximum Query
 */

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 10000;

int dmax[MAXN][20];
int dmin[MAXN][20];

void InitMax(int d[], int n) {
  for (int i = 1; i <= n; ++i) {
    dmax[i][0] = d[i];
  }
  int k = (int)(log((double)(right-left+1)) / log(2.0));
  for (int j = 1; (1 << j) <= n; ++j) {
    for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
      dmax[i][j] = max(dmax[i][j-1], dmax[i+(1<<(j-1))][j-1]);
    }
  }
}

void InitMin(int d[], int n) {
  for (int i = 1; i <= n; ++i) {
    dmin[i][0] = d[i];
  }
  for (int j = 1; (1 << j) <= n; ++j) {
    for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
      dmin[i][j] = min(dmin[i][j-1], dmin[i+(1<<(j-1))][j-1]);
    }
  }
}

int GetMax(int left, int right) {
  /*
  int k = 0;
  while ((1 << (k + 1)) <= right - left + 1) {
    k++;
  }
  */
  int k = (int)(log((double)(right-left+1)) / log(2.0));
  return max(dmax[left][k], dmax[right-(1<<k)+1][k]);
}

int GetMin(int left, int right) {
  int k = 0;
  while ((1 << (k + 1)) <= right - left + 1) {
    k++;
  }
  return min(dmin[left][k], dmin[right-(1<<k)+1][k]);
}


int main(int argc, char* argv[]) {
  const int M = 1000;
  const int L = 16;
  int* arr = new int[L+1];
  srand(1);
  arr[0] = -1;
  for (int i = 1; i <= L; ++i) {
    arr[i] = rand() % M;
  }
  for (int i = 0; i <= L; ++i) {
    cout << arr[i] << ", ";
  }
  cout << endl;

  InitMax(arr, L);
  InitMin(arr, L);

  for (int i = 0; i <= L; ++i) {
    cout << dmax[i][0] << ", ";
  }
  cout << endl;
  cout << GetMax(1, 12) << endl;
  cout << GetMin(1, 12) << endl;

  return 0;
}
