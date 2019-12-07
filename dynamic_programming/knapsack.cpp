#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

class Solution {
private:
    vector<size_t> weights;  // weights[i]: the weight of the item i
    size_t limit_weight;  // the allowed total weight of the items in the knapsack.
    vector<ptrdiff_t> values;  // values[i]: the value of the item i
    size_t sum_weight;  // the sum weight of the items in the knapsack.
    ptrdiff_t sum_value;  // the sum value of the items in the knapsack.
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
        sum_value = 0;
        call_memo = vector< vector<bool> > (weights.size(), vector<bool>(allowed_weight + 1, false));

        backtrace_call_count = 0;
        dp_yes_count = 0;
        dp_no_count = 0;
        dp_dupliate_count = 0;
    }

    Solution(const vector<size_t> &weights_, const size_t allowed_weight,
             const vector<ptrdiff_t> &values_) :
        weights(weights_), limit_weight(allowed_weight), values(values_)
    {
        sum_weight = 0;
        sum_value = 0;
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

    ptrdiff_t knapsack_bt(size_t index, size_t weight, ptrdiff_t value) {
        backtrace_call_count++;
        if (weight == limit_weight || index == weights.size()) {
            if (value > sum_value) {  // Different from knapsack_bt_1()
                sum_value = value;
            }
            return sum_value;
        }

        // Don't put the item i to the knapsack
        knapsack_bt(index + 1, weight, value);

        // Put the item i to the knapsack
        if (weight + weights[index] <= limit_weight) {
            knapsack_bt(index + 1, weight + weights[index], value + values[index]);
        }
        return sum_value;
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

    ptrdiff_t knapsack_dp() {
        const size_t total_num = weights.size();
        vector< vector<ptrdiff_t> > states(total_num, vector<ptrdiff_t>(limit_weight+1, -1));
        states[0][0] = 0;
        if (weights[0] < limit_weight) {
            states[0][weights[0]] = values[0];  // Different from knapsack_dp_1()
        }

        for (size_t i = 1; i < total_num; ++i) {
            // Don't put the item i to the knapsack
            for (size_t j = 0; j <= limit_weight; ++j) {
                if (states[i-1][j] >= 0) {  // Different from knapsack_dp_1()
                    states[i][j] = states[i-1][j];
                    dp_no_count++;

                }
            }
            // Put the item i to the knapsack
            for (size_t j = 0; j <= limit_weight - weights[i]; ++j) {
                if (states[i-1][j] >= 0) {  // Different from knapsack_dp_1()
                    ptrdiff_t state_value = states[i-1][j] + values[i];
                    if (state_value > states[i][j+weights[i]]) {
                        states[i][j+weights[i]] = state_value;
                    }
                    dp_yes_count++;
                }
            }
        }

        for (size_t w = limit_weight; w > 0; --w) {
            if (states[total_num-1][w] > sum_value) {
                sum_value =  states[total_num-1][w];
            }
        }

        return sum_value;
    }
};

int main() {
    size_t items[5] = {2, 2, 4, 6, 3};
    const vector<size_t> weights(items, items + sizeof(items)/sizeof(*items));
    size_t limit_weight = 9;

    cout << "==== Solution for maximizing weights ====" << endl;
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

    cout << "==== Solution for maximizing values ====" << endl;

    ptrdiff_t item_values[5] = {3, 4, 8, 9, 6};
    const vector<ptrdiff_t> values(item_values, item_values + sizeof(item_values)/sizeof(*item_values));
    Solution sln2(weights, limit_weight, values);
    // ptrdiff_t sum_value = sln2.knapsack_bt(0,0,0);
    ptrdiff_t sum_value = sln2.knapsack_dp();
    cout << "sum value = " << sum_value << endl;

    return 0;
}
