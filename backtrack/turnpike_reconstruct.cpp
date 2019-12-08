/* turnpike_reconstruct.cpp */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool TurnpikeReconstruct(vector<size_t>& calculated_positions, map<size_t, size_t>& dist_set,
                         const size_t position_count, const size_t far) {
  if (position_count == 0) return true;

  size_t cur_n, cur_far, i;
  map<size_t, size_t>::iterator it;

  /* p_n = 0
   * p_n-1 = far
   * p_n-2 = cur_far
   */
  cur_n = calculated_positions.size();
  cur_far = dist_set.rbegin()->first;
  for (i = 0; i < cur_n; ++i) {
    it = dist_set.find(abs((long)(cur_far - calculated_positions[i])));
    if (it == dist_set.end() || it->second == 0) {
      break;
    }
    --it->second;
    if (it->second == 0) {
      dist_set.erase(it);
    }
  }
  if (i == cur_n) {
    calculated_positions.push_back(cur_far);
    if (TurnpikeReconstruct(calculated_positions, dist_set, position_count -1 , far)) {
      return true;
    }
    calculated_positions.pop_back();  // Backtrack
  }
  cur_n = i;  // Restore the dist_set elements that have been decreased.
  for (i = 0; i < cur_n; ++i) {
    ++dist_set[abs((long)(cur_far - calculated_positions[i]))];
  }

  /* position_n = 0
   * position_n-1 = far
   * position_n-2 = far - cur_far
   */
  cur_n = calculated_positions.size();
  cur_far = dist_set.rbegin()->first;
  for (i = 0; i < cur_n; ++i) {
    it = dist_set.find(abs((long)((far - cur_far) - calculated_positions[i])));
    if (it == dist_set.end() || it->second == 0) {
      break;
    }
    --it->second;
    if (it->second == 0) {
      dist_set.erase(it);
    }
  }
  if (i == cur_n) {
    calculated_positions.push_back(far - cur_far);
    if (TurnpikeReconstruct(calculated_positions, dist_set, position_count - 1 , far)) {
      return true;
    }
    calculated_positions.pop_back();
  }
  cur_n = i;
  for (i = 0; i < cur_n; ++i) {
    ++dist_set[abs((long)((far - cur_far) - calculated_positions[i]))];
  }

  return false;
}

int main() {
  size_t i, n2, dist, far;
  vector<size_t> calculated_positions;
  map<size_t, size_t> dist_set;

  cout << "Input n2: ";
  cin >> n2;
  if (n2 < 1) {
    cout << "Invalid n2." << endl;
    exit(0);
  } else if (n2 == 1) {
    cout << "Use default data: n2=15, dist_set={1,2,2,2,3,3,3,4,5,5,5,6,7,8,10}" << std::endl;
    n2 = 15;
    size_t arr[15] = {1,2,2,2,3,3,3,4,5,5,5,6,7,8,10};
    for (i = 0; i< n2; ++i) {
      ++dist_set[arr[i]];
    }
  } else {
      for (i = 0; i < n2; ++i) {
        cin >> dist;
        ++dist_set[dist];
      }
  }


  size_t position_count = (size_t)sqrt(n2 * 2) + 1;
  far = dist_set.rbegin()->first;
  --dist_set[far];
  if (dist_set.rbegin()->second == 0) {
    dist_set.erase(far);
  }

  calculated_positions.push_back(0);
  calculated_positions.push_back(far);
  if (!TurnpikeReconstruct(calculated_positions, dist_set, position_count - 2, far)) {
    cout << "No solution." << endl;
  } else {
    sort(calculated_positions.begin(), calculated_positions.end());
    for (i = 0; i < position_count; ++i) {
      cout << calculated_positions[i] << ", ";
    }
    cout << endl;
  }

  calculated_positions.clear();
  dist_set.clear();

  return 0;
}
