/* rmq.cpp
 * Range Minimum/Maximum Query
 */

#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 10000;
const int LOGMAXN = 20;

int dmax[MAXN][LOGMAXN];
int dmin[MAXN][LOGMAXN];

void InitMax(int d[], int n) {
  for (int i = 0; i < n; ++i) {
    dmax[i][0] = d[i];
  }
  for (int j = 1; (1 << j) <= n; ++j) {
    for (int i = 0; i + (1 << j) - 1 < n; ++i) {
      dmax[i][j] = max(dmax[i][j-1], dmax[i+(1<<(j-1))][j-1]);
    }
  }
}

void InitMin(int d[], int n) {
  for (int i = 0; i < n; ++i) {
    dmin[i][0] = d[i];
  }
  for (int j = 1; (1 << j) <= n; ++j) {
    for (int i = 0; i + (1 << j) - 1 < n; ++i) {
      dmin[i][j] = min(dmin[i][j-1], dmin[i+(1<<(j-1))][j-1]);
    }
  }
}

int GetMax(int left, int right) {
  if (left > right) {
    cout << "Invalid interval!" << endl;
    exit(1);
  }
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
  if (left > right) {
    cout << "Invalid interval!" << endl;
    exit(1);
  }
  int k = 0;
  while ((1 << (k + 1)) <= right - left + 1) {
    k++;
  }
  return min(dmin[left][k], dmin[right-(1<<k)+1][k]);
}


int main(int argc, char* argv[]) {
  const int M = 1000;
  const int L = 16;
  int* arr = new int[L];
  srand(0);
  int a = 0;
  for (int i = 0; i < L; ++i) {
    a = rand() % M;
    arr[i] = a;
  }
  cout << endl;

  InitMax(arr, L);
  InitMin(arr, L);

  for (int i = 0; i < L; ++i) {
    cout << setw(4) << dmax[i][0];
  }
  cout << endl;
  cout << GetMax(3, 12) << endl;
  cout << GetMin(3, 12) << endl;

  int i, j;
  for (i = 0; i < L; ++i) {
    cout << setw(i * 4) << "";
    for (j = i; j < L; ++j) {
      cout << setw(4) << GetMin(i, j);
    }
    cout << endl;
  }

  return 0;
}
