/* rmq2.cpp */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cmath>

using std::max;
using std::min;
using std::cout;
using std::endl;
using std::setw;

const int MAXN = 10000;
const int LOGMAXN = 20;
int index_min[MAXN][LOGMAXN];
int index_max[MAXN][LOGMAXN];

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

int GetMin(int arr[], int left, int right) {
  if (left > right) {
    cout << "Invalid interval!" << endl;
    exit(1);
  }
  int k = (int)((log((double)(right-left+1))) / log(2.0));
  return min(arr[index_min[left][k]], arr[index_min[right-(1<<k)+1][k]]);
}

void InitIndexMax(int arr[], int len) {
  int i, j;
  for (i = 0; i < len; ++i) {
    index_max[i][0] = i;
  }
  for (j = 1; (1 << j) <= len; ++j) {
    for (i = 0; i + (1 << j) - 1 < len; ++i) {
      if (arr[index_max[i][j-1]] > arr[index_max[i+(1<<(j-1))][j-1]]) {
        index_max[i][j] = index_max[i][j-1];
      } else {
        index_max[i][j] = index_max[i+(1<<(j-1))][j-1];
      }
    }
  }
}

int GetMaxIndex(int arr[], int left, int right) {
  int res;
  if (left > right) {
    cout << "Invalid interval!" << endl;
    exit(1);
  }
  int k = (int)((log((double)(right-left+1))) / log(2.0));
  if (arr[index_max[left][k]] > arr[index_max[right-(1<<k)+1][k]]) {
    res = index_max[left][k];
  } else {
    res = index_max[right-(1<<k)+1][k];
  }
  return res;
}

int GetMax(int arr[], int left, int right) {
  if (left > right) {
    cout << "Invalid interval!" << endl;
    exit(1);
  }
  int k = (int)((log((double)(right-left+1))) / log(2.0));
  return max(arr[index_max[left][k]], arr[index_max[right-(1<<k)+1][k]]);
}

int main(int argc, char* argv[]) {
  const int M = 1000;
  const int L = 16;
  int* arr = new int[L];
  int i, j;
  srand(0);
  int a = 0;

  cout << "Index:" << endl;
  for (i = 0; i < L; ++i) {
    cout << setw(4) << i;
  }
  cout << endl;

  cout << "Array arr:" << endl;
  for (i = 0; i < L; ++i) {
    a = rand() % M;
    cout << setw(4) << a;
    arr[i] = a;
  }
  cout << endl;

/*
  InitIndexMin(arr, L);

  cout << "Get index of minimum:" << endl;
  for (i = 0; i < L; ++i) {
    cout << setw(i * 4) << "";
    for (j = i; j < L; ++j) {
      cout << setw(4) << GetMinIndex(arr, i, j);
    }
    cout << endl;
  }

  cout << "Get minimum:" << endl;
  for (i = 0; i < L; ++i) {
    cout << setw(i * 4) << "";
    for (j = i; j < L; ++j) {
      cout << setw(4) << GetMin(arr, i, j);
    }
    cout << endl;
  }
 */

  InitIndexMax(arr, L);

  cout << "Get index of maximum:" << endl;
  for (i = 0; i < L; ++i) {
    cout << setw(i * 4) << "";
    for (j = i; j < L; ++j) {
      cout << setw(4) << GetMaxIndex(arr, i, j);
    }
    cout << endl;
  }

  cout << "Get maximum:" << endl;
  for (i = 0; i < L; ++i) {
    cout << setw(i * 4) << "";
    for (j = i; j < L; ++j) {
      cout << setw(4) << GetMax(arr, i, j);
    }
    cout << endl;
  }

  return 0;
}
