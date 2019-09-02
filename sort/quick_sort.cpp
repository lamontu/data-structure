/* quick_sort.cpp */

#include <iostream>
#include <algorithm>

using namespace std;

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

void quick_sort_recurse(int* arr, int low, int high) {
    if (low >= high) {
        return;
    }
    int index = partition(arr, low, high);
    quick_sort_recurse(arr, low, index - 1);
    quick_sort_recurse(arr, index + 1, high);
}

void quick_sort(int* arr, int length) {
    quick_sort_recurse(arr, 0, length - 1);
}

void print(int* arr, int length) {
  for (int i = 0; i < length; ++i) {
    cout << arr[i] << ", ";
  }
  cout << endl;
}

int main(int argc, char* argv[]) {
  const int M = 100;
  const int length = 10;
  int* arr1 = new int[length];
  srand(0);
  for (int i = 0; i < length; ++i) {
    int rand_num = rand() % M;
    arr1[i] = rand_num;
  }
  print(arr1, length);

  quick_sort(arr1, length);
  print(arr1, length);
  delete [] arr1;

  return 0;
}

