/* selection_sort.cpp */

#include <iostream>

using namespace std;

void selection_sort(int* arr, int n) {
  if (nullptr == arr || 0 == n) return;

  int i, j;
  int min;
  for (i = 0; i < n - 1; ++i) {
    min = i;
    for (j = i + 1; j < n; ++j) {
      if (arr[min] > arr[j]) {
        min = j;
      }
    }
    if (min == i) continue;
    arr[min] = arr[min] ^ arr[i];
    arr[i] = arr[min] ^ arr[i];
    arr[min] = arr[min] ^ arr[i];
  }
}

void print(int* arr, int length) {
  for (int i = 0; i < length; ++i) {
    cout << arr[i] << ", ";
  }
  cout << endl;
}

int main(int argc, char* argv[]) {
  const int length = 10;
  const int M = 100;
  int* arr1 = new int[length];
  srand(0);
  for (int i = 0; i < length; ++i) {
    int rand_num = rand() % 100;
    arr1[i] = rand_num;
  }
  print(arr1, length);

  selection_sort(arr1, length);
  print(arr1, length);
  delete [] arr1;

  return 0;
}

