/* multiply_order_memo.cpp */

#include <iostream>

using namespace std;

const int L = 7;

int LookupChain(int i, int j, int** m, int** s, int* p) {
  if (m[i][j] > 0) {
    return m[i][j];
  }
  if (i == j) {
    return 0;
  }
  int u = LookupChain(i, i, m, s, p) + LookupChain(i + 1, j, m, s, p)
          + p[i-1] * p[i] * p[j];
  s[i][j] = i;
  for (int k = i + 1; k < j; ++k) {
    int t = LookupChain(i, k, m, s, p) + LookupChain(k + 1, j, m, s, p)
            + p[i-1] * p[k] * p[j];
    if (t < u) {
      u = t;
      s[i][j] = k;
    }
  }
  m[i][j] = u;
  return u;
}

int MemoMatrixChain(int n, int** m, int** s, int* p) {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      m[i][j] = 0;
    }
  }
  return LookupChain(1, n, m, s, p);
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

  int res = MemoMatrixChain(6, m, s, p);
  cout << "Minimum multiplication times: " << res << endl;

  cout << "Multiplication order:" << endl;
  Traceback(1, 6, s);

  return 0;
}
