/* binary_search.cpp */
#include <iostream>

using std::cout;
using std::endl;

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

// Return first position x, array[x] == value
int bsearchFirstEqual(int array[], int length, int value) {
    int low = 0, high = length - 1;
    while (low <= high) {
        int middle = low + ((high - low) >> 1);
        if (array[middle] > value) {
            high = middle - 1;
        } else if (array[middle] < value) {
            low = middle + 1;
        } else {
            if ((middle == 0) || array[middle - 1] != value) {
                return middle;
            } else {
                high = middle - 1;
            }
        }
    }
    return -1;
}

// Return last position x, array[x] == value
int bsearchLastEqual(int array[], int length, int value) {
    int low = 0, high = length - 1;
    while (low <= high) {
        int middle = low + ((high - low) >> 1);
        if (array[middle] > value) {
            high = middle - 1;
        } else if (array[middle] < value) {
            low = middle + 1;
        } else {
            if ((middle == length - 1) || array[middle + 1] != value) {
                return middle;
            } else {
                low = middle + 1;
            }
        }
    }
    return -1;
}

// Return first  position x, array[x] >= value
int bsearchFirstGreaterEqual(int array[], int length, int value) {
    int low = 0, high = length - 1;
    while (low <= high) {
        int middle = low + ((high - low) >> 1);
        if (array[middle] >= value) {
            if ((middle == 0) || array[middle - 1] < value) {
                return middle;
            } else {
                high = middle - 1;
            }
        } else {
            low = middle + 1;
        }
    }
    return -1;
}

// Return last  position x, array[x] <= value
int bsearchLastLessEqual(int array[], int length, int value) {
    int low = 0, high = length - 1;
    while (low <= high) {
        int middle = low + ((high - low) >> 1);
        if (array[middle] > value) {
            high = middle - 1;
        } else {
            if ((middle == length - 1) || array[middle + 1] > value) {
                return middle;
            } else {
                low = middle + 1;
            }
        }
    }
    return -1;
}

int main() {
  int arr[] = {1, 1, 2, 4, 7, 9, 9};

  int loc = firstEqual(arr, 7, 9);
  cout << loc << endl;

  int loc1 = firstGreatOrEqual(arr, 7, 3);
  cout << loc1 << endl;

  int loc2 = firstGreat(arr, 7, 3);
  cout << loc2 << endl;

  return 0;
}
