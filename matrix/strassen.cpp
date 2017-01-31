/* strassen.cpp */

#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

void get_submatrix(const vector<vector<int>>& m, vector<vector<int>>& sub,
                   int part) {
  int n = (int)m.size();
  int i, j;
  int n1 = n / 2;
  int top = part / 2 * n1;
  int left = part % 2 * n1;
  for (i = 0; i < n1; ++i) {
    for (j = 0; j < n1; ++j) {
      sub[i][j] = m[top+i][left+j];
    }
  }
}

void set_submatrix(vector<vector<int>>& m, const vector<vector<int>>& sub,
                   int part) {
  int n = (int)m.size();
  int i, j;
  int n1 = n / 2;
  int top = part / 2 * n1;
  int left = part % 2 * n1;
  for (i = 0; i < n1; ++i) {
    for (j = 0; j < n1; ++j) {
      m[top+i][left+j] = sub[i][j];
    }
  }
}

void add_matrix(const vector<vector<int>>& a, const vector<vector<int>>& b,
                vector<vector<int>>& c, int n) {
  int i, j;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      c[i][j] = a[i][j] + b[i][j];
    }
  }
}

void substract_matrix(const vector<vector<int>>& a,
        const vector<vector<int>>& b, vector<vector<int>>& c, int n) {
  int i, j;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      c[i][j] = a[i][j] - b[i][j];
    }
  }
}

void matrix_multiply_recursion(const vector<vector<int>>& a,
        const vector<vector<int>>& b, vector<vector<int>>& c, int n) {
  if (n == 1) {
    c[0][0] = a[0][0] * b[0][0];
    return;
  }

  int i;
  int n1 = n / 2;
  
  vector<vector<int>> aa[4];
  vector<vector<int>> bb[4];
  for (i = 0; i < 4; ++i) {
    aa[i].resize(n1, vector<int>(n1));
    bb[i].resize(n1, vector<int>(n1));
  }
  for (i = 0; i < 4; ++i) {
    get_submatrix(a, aa[i], i);
    get_submatrix(b, bb[i], i);
  }

  vector<vector<int>> x, y;
  vector<vector<int>> m[7];
  x.resize(n1, vector<int>(n1));
  y.resize(n1, vector<int>(n1));
  for (i = 0; i < 7; ++i) {
    m[i].resize(n1, vector<int>(n1));
  }

  substract_matrix(aa[1], aa[3], x, n1);
  add_matrix(bb[2], bb[3], y, n1);
  matrix_multiply_recursion(x, y, m[0], n1);

  add_matrix(aa[0], aa[3], x, n1);
  add_matrix(bb[0], bb[3], y, n1);
  matrix_multiply_recursion(x, y, m[1], n1);

  substract_matrix(aa[0], aa[2], x, n1);
  add_matrix(bb[0], bb[1], y, n1);
  matrix_multiply_recursion(x, y, m[2], n1);

  add_matrix(aa[0], aa[1], x, n1);
  matrix_multiply_recursion(x, bb[3], m[3], n1);

  substract_matrix(bb[1], bb[3], y, n1);
  matrix_multiply_recursion(aa[0], y, m[4], n1);

  substract_matrix(bb[2], bb[0], y, n1);
  matrix_multiply_recursion(aa[3], y, m[5], n1);

  add_matrix(aa[2], aa[3], x, n1);
  matrix_multiply_recursion(x, bb[0], m[6], n1);

  add_matrix(m[0], m[1], x, n1);
  substract_matrix(x, m[3], x, n1);
  add_matrix(x, m[5], x, n1);
  set_submatrix(c, x, 0);

  add_matrix(m[3], m[4], x, n1);
  set_submatrix(c, x, 1);

  add_matrix(m[5], m[6], x, n1);
  set_submatrix(c, x, 2);
  
  substract_matrix(m[1], m[2], x, n1);
  add_matrix(x, m[4], x, n1);
  substract_matrix(x, m[6], x, n1);
  set_submatrix(c, x, 3);

  for (i = 0; i < 4; ++i) {
    aa[i].clear();
    bb[i].clear();
  }
  for (i = 0; i < 7; ++i) {
    m[i].clear();
  }
  x.clear();
  y.clear();
}

void MatrixMultiply(const vector<vector<int>>& a, const vector<vector<int>>& b,
        vector<vector<int>>& c) {
  int n = (int)a.size();
  matrix_multiply_recursion(a, b, c, n);
}

int main(int argc, char* argv[]) {
  int n;
  int i, j;
  vector<vector<int>> a, b, c;
  cout << "Matrix size: ";
  cin >> n;
  if (n < 1) {
    cout << "Invalid matrix size!" << endl;
    exit(1);
  }
  a.resize(n, vector<int>(n));
  b.resize(n, vector<int>(n));
  c.resize(n, vector<int>(n));

  cout << "Matrix a:" << endl;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      cin >> a[i][j];
    }
  }
  cout << "Matrix b:" << endl;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      cin >> b[i][j];
    }
  }

  MatrixMultiply(a, b, c);

  cout << "Matrix c:" << endl;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      cout << setw(4) << c[i][j];
    }
    cout << endl;
  }

  a.clear();
  b.clear();
  c.clear();

  cout << endl;
  return 0;
}
