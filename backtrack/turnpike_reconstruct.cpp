/* turnpike_reconstruct.cpp */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool TurnpikeReconstruct(vector<int>& calculated_positions, map<int, int>& dist_set,
                         const int position_count, const int far) {
  if (position_count == 0) return true;

  int cur_n, cur_far, i;
  map<int, int>::iterator it;

  /* p_n = 0
   * p_n-1 = far
   * p_n-2 = cur_far
   */
  cur_n = (int)calculated_positions.size();
  cur_far = dist_set.rbegin()->first;
  for (i = 0; i < cur_n; ++i) {
    it = dist_set.find(abs(cur_far - calculated_positions[i]));
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
    ++dist_set[abs(cur_far - calculated_positions[i])];
  }

  /* position_n = 0
   * position_n-1 = far
   * position_n-2 = far - cur_far
   */
  cur_n = (int)calculated_positions.size();
  cur_far = dist_set.rbegin()->first;
  for (i = 0; i < cur_n; ++i) {
    it = dist_set.find(abs(far - cur_far - calculated_positions[i]));
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
    ++dist_set[abs(far - cur_far - calculated_positions[i])];
  }

  return false;
}

int main(int argc, char* argv[]) {
  int i, n2, dist, far;
  vector<int> calculated_positions;
  map<int, int> dist_set;

  cout << "Input n2: ";
  cin >> n2;
  if (n2 < 1) {
    cout << "Invalid n2." << endl;
    exit(0);
  } else if (n2 == 1) {
    cout << "Use default data: n2=15, dist_set={1,2,2,2,3,3,3,4,5,5,5,6,7,8,10}" << std::endl;
    n2 = 15;
    int arr[15] = {1,2,2,2,3,3,3,4,5,5,5,6,7,8,10};
    for (i = 0; i< n2; ++i) {
      ++dist_set[arr[i]];
    }
  } else {
      for (i = 0; i < n2; ++i) {
        cin >> dist;
        ++dist_set[dist];
      }
  }


  int position_count = (int)sqrt(n2 * 2) + 1;
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
