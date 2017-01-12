/* heap_sort.cpp */

#include <iostream>

using namespace std;

void heap_adjust(int* array, int i, int length) {
  int child;
  int tmp;
  for (; 2 * i + 1 < length; i = child) {
    child = 2 * i + 1;
    if (child < length - 1 && array[child + 1] > array[child]) {
      ++child;
    }
    if (array[i] < array[child]) {
      tmp = array[i];
      array[i] = array[child];
      array[child] = tmp;
    } else {
      break;
    }
  }
}

void build_maxheap(int* arr, int length) {
  int i;
  for (i = length / 2 - 1; i >= 0; --i) {
    heap_adjust(arr, i, length);
  }
}

void heap_sort(int* arr, int length) {
  build_maxheap(arr, length);
  int i;
  for (i = length - 1; i > 0; --i) {
    arr[i] = arr[0] ^ arr[i];
    arr[0] = arr[0] ^ arr[i];
    arr[i] = arr[0] ^ arr[i];
    heap_adjust(arr, 0, i);
  }
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

  heap_sort(arr1, length);
  print(arr1, length);
  delete [] arr1;

  return 0;
}

