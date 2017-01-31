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
  int n = (int)dimension.size() - 1;
  vector<vector<int>> dp;
  dp.resize(n, vector<int>(n, INF));

  int d, i, k;
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

int main(int argc, char* argv[]) {
  int i;
  int n;
  vector<int> v;

  cout << "Matrix number: ";
  cin >> n;
  if (n < 1) {
    cout << "Invalid matrix number!" << endl;
    exit(1);
  }
  v.resize(n + 1);

  for (i = 0; i < n + 1; ++i) {
    cin >> v[i];
  }

  int res = OrderMultiply(v);

  cout << "Minimum multiplication times: " << res << endl;

  return 0;
}
