#include <iostream>

using std::cout;
using std::endl;

/*
 * number: 234
 * 0st digit: 4
 * 1st digit: 3
 * 2nd digit: 2
 * 3rd digit: 0
 */

static int get_digit(int number, size_t index) {
  for (int i = index; i > 0; --i) {
    number /= 10;
  }
  return number % 10;
}

/* Counting sort using specific digit
 * K is base, K = 10
 */
static void counting_sort_digit(int array[], size_t length, size_t digit, size_t K=10) {
  if (nullptr == array || 0 == length) return;
  int* digit_num = new int[length];
  memset(digit_num, 0, sizeof(int) * length);
  int* count = new int[K];
  memset(count, 0, sizeof(int) * K);
  int* array_result = new int[length];
  memset(array_result, 0, sizeof(int) * length);

  for (size_t i = 0; i < length; ++i) {
    digit_num[i] = get_digit(array[i], digit);
  }
  for (size_t i = 0; i < length; ++i) {
    count[digit_num[i]]++;
  }
  for (size_t i = 1; i < K; ++i) {
    count[i] += count[i - 1];
  }
  for (int i = length - 1; i >= 0; --i) {
    array_result[count[digit_num[i]] - 1] = array[i];
    count[digit_num[i]]--;
  }
  memcpy(array, array_result, sizeof(int) * length);
  delete [] digit_num;
  delete [] count;
  delete [] array_result;
}

// The biggest number has wide digits.
static void radix_sort(int array[], size_t length, size_t wide) {
  for (size_t i = 0; i < wide; ++i) {
    counting_sort_digit(array, length, i);
  }
}

static void print(int* arr, int length) {
  for (int i = 0; i < length; ++i) {
    cout << arr[i] << ", ";
  }
  cout << endl;
}

int main() {
  const int M = 1000;
  const int length = 12;
  int* arr1 = new int[length];
  srand(0);
  for (int i = 0; i < length; ++i) {
    int rand_num = rand() % M;
    arr1[i] = rand_num;
  }
  print(arr1, length);

  radix_sort(arr1, length, 3);
  print(arr1, length);
  delete [] arr1;

  return 0;
}
