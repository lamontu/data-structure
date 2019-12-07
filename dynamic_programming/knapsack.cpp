#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

class Solution {
private:
    vector<size_t> weights;  // weights[i]: the weight of the item i
    size_t limit_weight;  // the allowed total weight of the item in the knapsack.
    size_t sum_weight;  // the sum weight of the item in the knapsack.
    vector< vector<bool> > call_memo;
public:

    size_t backtrace_call_count;
    size_t dp_yes_count;
    size_t dp_no_count;
    size_t dp_dupliate_count;

    Solution(const vector<size_t> &weights_, const size_t allowed_weight) :
        weights(weights_), limit_weight(allowed_weight)
    {
        sum_weight = 0;
        call_memo = vector< vector<bool> > (weights.size(), vector<bool>(allowed_weight + 1, false));

        backtrace_call_count = 0;
        dp_yes_count = 0;
        dp_no_count = 0;
        dp_dupliate_count = 0;
    }

    size_t knapsack_bt_1(size_t index, size_t weight) {
        backtrace_call_count++;
        if (weight == limit_weight || index == weights.size()) {
            if (weight > sum_weight) {
                sum_weight = weight;
            }
            return sum_weight;
        }

        // Don't put the item i to the knapsack
        knapsack_bt_1(index + 1, weight);

        // Put the item i to the knapsack
        if (weight + weights[index] <= limit_weight) {
            knapsack_bt_1(index + 1, weight + weights[index]);
        }
        return sum_weight;
    }

    size_t knapsack_bt_2(size_t index, size_t weight) {
        backtrace_call_count++;
        if (weight == limit_weight || index == weights.size()) {
            if (weight > sum_weight) {
                sum_weight = weight;
            }
            return sum_weight;
        }

        if (call_memo[index][weight]) {
            return sum_weight;
        }
        call_memo[index][weight] = true;

        // Don't put the item i to the knapsack
        knapsack_bt_2(index + 1, weight);

        // Put the item i to the knapsack
        if (weight + weights[index] <= limit_weight) {
            knapsack_bt_2(index + 1, weight + weights[index]);
        }
        return sum_weight;
    }

    size_t knapsack_dp_1() {
        const size_t total_num = weights.size();
        vector< vector<bool> > states(total_num, vector<bool>(limit_weight+1, false));
        states[0][0] = true;
        if (weights[0] < limit_weight) {
            states[0][weights[0]] = true;
        }

        for (size_t i = 1; i < total_num; ++i) {
            // Don't put the item i to the knapsack
            for (size_t j = 0; j <= limit_weight; ++j) {
                if (states[i-1][j]) {
                    states[i][j] = states[i-1][j];
                    dp_no_count++;
                }
            }
            // Put the item i to the knapsack
            for (size_t j = 0; j <= limit_weight - weights[i]; ++j) {
                if (states[i-1][j]) {
                    states[i][j+weights[i]] = true;
                    dp_yes_count++;
                }
            }
        }

        for (size_t w = limit_weight; w > 0; --w) {
            if (states[total_num-1][w]) {
                return w;
            }
        }

        return 0;
    }

    size_t knapsack_dp_2() {
        const size_t total_num = weights.size();
        vector<bool> states(limit_weight+1, false);
        states[0] = true;
        if (weights[0] < limit_weight) {
            states[weights[0]] = true;
        }

        for (size_t i = 1; i < total_num; ++i) {
            for (size_t j = limit_weight - weights[i]; ; --j) {
                if (states[j]) {
                    // Put the item i to the knapsack
                    if (states[j + weights[i]]) {
                        dp_dupliate_count++;
                    }
                    states[j + weights[i]] = true;
                    dp_yes_count++;
                    // Don't put the item i to the knapsack
                    //states[j] = true
                }
                if (j == 0) {
                    break;
                }
            }
        }

        for (size_t w = limit_weight; w > 0; --w) {
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
    size_t limit_weight = 9;
    Solution sln(weights, limit_weight);

    // size_t sum_weight = sln.knapsack_bt_1(0, 0);
    // size_t sum_weight = sln.knapsack_bt_2(0, 0);
    // cout << "bt call count = " << sln.backtrace_call_count << endl;

    // size_t sum_weight = sln.knapsack_dp_1();
    size_t sum_weight = sln.knapsack_dp_2();

    cout << "sum weight = " << sum_weight << endl;

    cout << "dp yes count = " << sln.dp_yes_count << endl;
    cout << "dp 1 no count = " << sln.dp_no_count << endl;
    cout << "dp 2 duplicates count = " << sln.dp_dupliate_count << endl;
    return 0;
}
