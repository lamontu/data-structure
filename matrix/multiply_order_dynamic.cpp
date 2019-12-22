/* multiply_order_dynamic.cpp */

#include <iostream>

using namespace std;

const int L = 7;

/*
Matrix      A1      A2      A3      A4      A5      A5
Dimension (d0,d1) (d1,d2) (d2,d3) (d3,d4) (d4,d5) (d5,d6)
*/
int MatrixChain(int num, int** multiplyTimes, int** seperateIndexes, int* d) {
  for (int i = 1; i <= num; ++i) {
    multiplyTimes[i][i] = 0;  // the matrix number: 1
  }
  for (int r = 2; r <= num; ++r) {  // r: the matrix number: 2, 3, ... , n.
    for (int i = 1; i <= num - r + 1; ++i) {
      int j = i + r - 1;
      multiplyTimes [i][j] = multiplyTimes[i+1][j] + d[i-1] * d[i] * d[j];
      /*(A1 A2) ((A3 A4) (A5 A6))
       * The outmost layer bracket separation position: 2
       */
      seperateIndexes[i][j] = i;
      for (int k = i + 1; k < j; ++k) {
        int t = multiplyTimes[i][k] + multiplyTimes[k+1][j] + d[i-1] * d[k] * d[j];
        if (t < multiplyTimes[i][j]) {
          multiplyTimes[i][j] = t;
          seperateIndexes[i][j] = k;
        }
      }
    }
  }
  return multiplyTimes[1][L-1];
}

void Traceback(int i, int j, int** seperateIndexes) {
  if (i == j) return;
  Traceback(i, seperateIndexes[i][j], seperateIndexes);
  Traceback(seperateIndexes[i][j]+1, j, seperateIndexes);
  cout << "Multiply A" << i << "," << seperateIndexes[i][j];
  cout << " and A" << (seperateIndexes[i][j] + 1) << "," << j << endl;
}

int main() {
  int dimensions[L] = {30, 35, 15, 5, 10, 20, 25};
  int** mul = new int* [L];
  int** sep = new int* [L];
  for (int i = 0; i < L; ++i) {
    mul[i] = new int[L];
    sep[i] = new int[L];
  }

  int res = MatrixChain(6, mul, sep, dimensions);
  cout << "Minimum multiplication times: " << res << endl;

  cout << "Multiplication order:" << endl;
  Traceback(1, 6, sep);

  return 0;
}
