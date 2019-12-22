/* multiplication_times.cpp */

#include <iostream>
#include <vector>

using namespace std;

const int INF = 0x7fffffff;

/*
 * A1:30*35, A2:35*15, A3:15*5
 * dimension = {30, 35, 15, 5}
 */
int OrderMultiply(const vector<int>& dimension) {
  /* number of matrices
   * Matrix index: 0, 1, 2, ... , (n-1).
   */
  size_t n = dimension.size() - 1;
  vector<vector<int> > dp(n, vector<int>(n, INF));

  size_t d, i, k;
  for (i = 0; i < n; ++i) {
    dp[i][i] = 0;  // d = 0
  }

  for (d = 1; d < n; ++d) {  // d = right - left
    for (i = 0; i + d < n; ++i) {
      for (k = i; k < i + d; ++k) {
        dp[i][i+d] = min(dp[i][i+d], dp[i][k] + dp[k+1][i+d] +
                         dimension[i] * dimension[k+1] * dimension[i+d+1]);
      }
    }
  }

  int res = dp[0][n - 1];
  dp.clear();
  return res;
}

int main() {
  cout << "Matrix number: ";
  size_t n;
  cin >> n;
  if (n < 1) {
    cout << "Invalid matrix number!" << endl;
    exit(1);
  }
  vector<int> v(n+1);

  for (size_t i = 0; i < n + 1; ++i) {
    cin >> v[i];
  }

  int res = OrderMultiply(v);

  cout << "Minimum multiplication times: " << res << endl;

  return 0;
}
