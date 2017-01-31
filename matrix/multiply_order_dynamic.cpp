/* multiply_order_dynamic.cpp */

#include <iostream>

using namespace std;

const int L = 7;

int MatrixChain(int n, int** m, int** s, int* p) {
  for (int i = 1; i <= n; ++i) {
    m[i][i] = 0;  // the matrix number: 1
  }
  for (int r = 2; r <= n; ++r) {  // r: the matrix number: 2, 3, ... , n.
    for (int i = 1; i <= n - r + 1; ++i) {
      int j = i + r - 1;
      m[i][j] = m[i+1][j] + p[i-1] * p[i] * p[j];
      /*(A1 A2) ((A3 A4) (A5 A6))
       * The outmost layer bracket separation position: 2
       */
      s[i][j] = i;  
      for (int k = i + 1; k < j; ++k) {
        int t = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
        if (t < m[i][j]) {
          m[i][j] = t;
          s[i][j] = k;
        }
      }
    }
  }
  return m[1][L-1];
}

void Traceback(int i, int j, int** s) {
  if (i == j) return;
  Traceback(i, s[i][j], s);
  Traceback(s[i][j]+1, j, s);
  cout << "Multiply A" << i << "," << s[i][j];
  cout << " and A" << (s[i][j] + 1) << "," << j << endl;
}

int main(int argc, char* argv[]) {
  int p[L] = {30, 35, 15, 5, 10, 20, 25};
  int** m = new int* [L];
  int** s = new int* [L];
  for (int i = 0; i < L; ++i) {
    m[i] = new int[L];
    s[i] = new int[L];
  }

  int res = MatrixChain(6, m, s, p);
  cout << "Minimum multiplication times: " << res << endl;

  cout << "Multiplication order:" << endl;
  Traceback(1, 6, s);

  return 0;
}
