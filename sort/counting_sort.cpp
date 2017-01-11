/* counting_sort.cpp */

#include <iostream>

using namespace std;

void print(int* arr, int length) {
  for (int i = 0; i < length; ++i) {
    cout << arr[i] << ", ";
  }
  cout << endl;
}

// 0 <= array_in[i] < K
void counting_sort(int* array_in, int* array_out, int size, int K) {
  int* c = new int[sizeof(int) * K];
  // Initialize array c with 0
  for (int i = 0; i < K; ++i) {
    c[i] = 0;
  }
  // Count each element of array_in
  for (int i = 0; i < size; ++i) {
    c[array_in[i]] += 1;
  }
  // Count the number of elements less than or equal to current element
  for (int i = 1; i < K; ++i) {
    c[i] += c[i - 1];
  }
  for (int j = size - 1; j >= 0; --j) {
    array_out[c[array_in[j]] - 1] = array_in[j];
    // Next same element shall be put at the previous position.
    c[array_in[j]] -= 1;  
  }
  delete [] c;
}

int main(int argc, char* argv[]) {
  const int K = 10;
  const int size = 15;
  int* arr1 = new int[sizeof(int) * size];
  int* arr2 = new int[sizeof(int) * size];
  srand(0);
  for (int i = 0; i < size; ++i) {
    int rand_num = rand() % K;
    arr1[i] = rand_num;
  }
  print(arr1, size);
  counting_sort(arr1, arr2, size, K);
  print(arr2, size);
  delete [] arr1;
  delete [] arr2;
  return 0;
}
