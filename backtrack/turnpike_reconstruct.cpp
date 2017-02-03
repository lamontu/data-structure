/* turnpike_reconstruct.cpp */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool TurnpikeReconstruct(int idx, vector<int>& x, map<int, int>& dist_set,
                         const int far) {
  if (idx == 0) return true;

  int cur_n, cur_far, i;
  map<int, int>::iterator it;

  /* p_n = 0
   * p_n-1 = far
   * p_n-2 = d_max
   */
  cur_n = (int)x.size();
  cur_far = dist_set.rbegin()->first;
  for (i = 0; i < cur_n; ++i) {
    it = dist_set.find(abs(cur_far - x[i]));
    if (it == dist_set.end() || it->second == 0) {
      break;
    }
    --it->second;
    if (it->second == 0) {
      dist_set.erase(it);
    }
  }
  if (i == cur_n) {
    x.push_back(cur_far);
    if (TurnpikeReconstruct(idx - 1, x, dist_set, far)) {
      return true;
    }
    x.pop_back();  // Backtrack
  }
  cur_n = i;  // Restore the dist_set elements that have been decreased.
  for (i = 0; i < cur_n; ++i) {
    ++dist_set[abs(cur_far - x[i])];
  }

  /* p_n = 0
   * p_n-1 = far
   * p_n-2 = far - d_max
   */
  cur_n = (int)x.size();
  cur_far = dist_set.rbegin()->first;
  for (i = 0; i < cur_n; ++i) {
    it = dist_set.find(abs(far - cur_far - x[i]));
    if (it == dist_set.end() || it->second == 0) {
      break;
    }
    --it->second;
    if (it->second == 0) {
      dist_set.erase(it);
    }
  }
  if (i == cur_n) {
    x.push_back(far - cur_far);
    if (TurnpikeReconstruct(idx - 1, x, dist_set, far)) {
      return true;
    }
    x.pop_back();
  }
  cur_n = i;
  for (i = 0; i < cur_n; ++i) {
    ++dist_set[abs(far - cur_far - x[i])];
  }

  return false;
}

int main(int argc, char* argv[]) {
  int i, n, n2, dist, far;
  vector<int> x;
  map<int, int> dist_set;

  cout << "Input n2: ";
  cin >> n2;
  if (n2 < 1) {
    cout << "Invalid n2." << endl;
  }

  for (i = 0; i < n2; ++i) {
    cin >> dist;
    ++dist_set[dist];
  }
  n = (int)sqrt(n2 * 2) + 1;
  far = dist_set.rbegin()->first;
  --dist_set[far];
  if (dist_set.rbegin()->second == 0) {
    dist_set.erase(far);
  }

  x.push_back(0);
  x.push_back(far);
  if (!TurnpikeReconstruct(n - 2, x, dist_set, far)) {
    cout << "No solution." << endl;
  } else {
    sort(x.begin(), x.end());
    for (i = 0; i < n; ++i) {
      cout << x[i] << ", ";
    }
    cout << endl;
  }

  x.clear();
  dist_set.clear();

  return 0;
}
