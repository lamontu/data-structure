#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
    size_t count_no;
    size_t count_yes;
    size_t count_dup;

    // weights[i]: the weight of the item i
    // total_weight: the allowed total weight of the item in the knapsack.
    size_t knapsack(const vector<size_t> &weights, const size_t total_num, const size_t total_weight) {
        vector< vector<bool> > states(total_num, vector<bool>(total_weight+1, false));
        states[0][0] = true;
        if (weights[0] < total_weight) {
            states[0][weights[0]] = true;
        }

        for (size_t i = 1; i < total_num; ++i) {
            // Don't put the item i to the knapsack
            for (size_t j = 0; j <= total_weight; ++j) {
                if (states[i-1][j]) {
                    states[i][j] = states[i-1][j];
                    count_no++;
                }
            }
            // Put the item i to the knapsack
            for (size_t j = 0; j <= total_weight - weights[i]; ++j) {
                if (states[i-1][j]) {
                    states[i][j+weights[i]] = true;
                    count_yes++;
                }
            }
        }

        for (size_t w = total_weight; w > 0; --w) {
            if (states[total_num-1][w]) {
                return w;
            }
        }

        return 0;
    }

    // weights[i]: the weight of the item i
    // total_weight: the allowed total weight of the item in the knapsack.
    size_t knapsack2(const vector<size_t> &weights, const size_t total_num, const size_t total_weight) {
        vector<bool> states(total_weight+1, false);
        states[0] = true;
        if (weights[0] < total_weight) {
            states[weights[0]] = true;
        }

        for (size_t i = 1; i < total_num; ++i) {
            for (size_t j = total_weight - weights[i]; ; --j) {
                if (states[j]) {
                    // Put the item i to the knapsack
                    if (states[j + weights[i]]) {
                        count_dup++;
                    }
                    states[j + weights[i]] = true;
                    count_yes++;
                    // Don't put the item i to the knapsack
                    //states[j] = true
                }
                if (j == 0) {
                    break;
                }
            }
        }

        for (size_t w = total_weight; w > 0; --w) {
            if (states[w]) {
                return w;
            }
        }

        return 0;
    }
};

int main() {
    size_t items[5] = {2, 2, 4, 6, 3};
    const vector<size_t> weights(items, items + sizeof(items)/sizeof(*items));
    size_t allowed_weight = 9;
    Solution sln;
    //size_t total_weight = sln.knapsack(weights, 5, allowed_weight);
    size_t total_weight = sln.knapsack2(weights, 5, allowed_weight);
    cout << "total weight = " << total_weight << endl;
    cout << "count no = " << sln.count_no << endl;
    cout << "count yes = " << sln.count_yes << endl;
    cout << "count duplicates = " << sln.count_dup << endl;
    return 0;
}
