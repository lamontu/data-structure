/* multiply_order_recur.cpp */

#include <iostream>

using namespace std;

const int L = 7;

int RecurMatrixChain(int i, int j, int** s, int* p) {
  if (i == j) return 0;
  int u = RecurMatrixChain(i, i, s, p) + RecurMatrixChain(i+1, j, s, p)
          + p[i-1] * p[i] * p[j];
  s[i][j] = i;

  for (int k = i + 1; k < j; ++k) {
    int t = RecurMatrixChain(i, k, s, p) + RecurMatrixChain(k+1, j, s, p)
            + p[i-1] * p[k] * p[j];
    if (t < u) {
      u = t;
      s[i][j] = k;
    }
  }
  return u;
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
  int** s = new int* [L];
  for (int i = 0; i < L; ++i) {
    s[i] = new int[L];
  }

  int res = RecurMatrixChain(1, 6, s, p);
  cout << "Minimum multiplication times: " << res << endl;

  cout << "Multiplication order:" << endl;
  Traceback(1, 6, s);

  return 0;
}

