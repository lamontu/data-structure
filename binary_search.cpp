/* binary_search.cpp */
#include <iostream>

using namespace std;

// For sorted array without duplicated elements
int SimpleBinarySearch(int array[], int length, int value) {
  int left = 0, right = length - 1;
  while (left <= right) {
    int middle = left + ((right - left) >> 1);
    if (array[middle] == value) {
      return middle;
    } else if (array[middle] < value) {
      left = middle + 1;
    } else {
      right = middle - 1;
    }
  }
  return -1;
}

// first position x, array[x] == value
int firstEqual(int array[], int length, int value) {
  int left = 0, right = length - 1;
  while (left <= right) {
    int middle = left + ((right - left) >> 1);
    if (value <= array[middle]) {
      right = middle - 1;
    } else {
      left = middle + 1;
    }
  } 
  return (left < length && array[left] == value) ? left : -1;  // different from lower bound
}

// lower bound: first position x, array[x] >= value
int firstGreatOrEqual(int array[], int length, int value) {
  int left = 0, right = length - 1;
  while (left <= right) {
    int middle = left + ((right - left) >> 1);
    if (value <= array[middle]) {  // only difference with upper bound
      right = middle - 1;
    } else {
      left = middle + 1;
    }
  } 
  return left < length ? left : -1;
}

// upper bound: first position x, array[x] > value
int firstGreat(int array[], int length, int value) {
  int left = 0, right = length - 1;
  while (left <= right) {
    int middle = left + ((right - left) >> 1);
    if (value < array[middle]) {  // only difference with lower bound
      right = middle - 1;
    } else {
      left = middle + 1;
    }
  } 
  return left < length ? left : -1;
}

int main(int argc, char* argv[]) {
  int arr[] = {1, 1, 2, 4, 7, 9, 9};

  int loc = firstEqual(arr, 7, 9);
  cout << loc << endl;

  int loc1 = firstGreatOrEqual(arr, 7, 3);
  cout << loc1 << endl;

  int loc2 = firstGreat(arr, 7, 3);
  cout << loc2 << endl;

  return 0;
}
