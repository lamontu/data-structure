#include <iostream>

using std::cout;
using std::endl;

// weights[i]: the weight of the item i
// weight: the allowed total weight of the item in the knapsack.
size_t knapsack(const size_t weights[], const size_t num, const size_t weight) {
    bool states[num][weight+1];
    memset(states, 0, num*(weight+1)*sizeof(bool));
    states[0][0] = true;
    if (weights[0] < weight) {
        states[0][weights[0]] = true;
    }

    for (size_t i = 1; i < num; ++i) {
        // Don't put the item i to the knapsack
        for (size_t j = 0; j <= weight; ++j) {
            if (states[i-1][j]) {
                states[i][j] = states[i-1][j];
            }
        }
        // Put the item i to the knapsack
        for (size_t j = 0; j <= weight - weights[i]; ++j) {
            if (states[i-1][j]) {
                states[i][j+weights[i]] = true;
            }
        }
    }

    for (size_t w = weight; w > 0; --w) {
        if (states[num-1][w]) {
            return w;
        }
    }

    return 0;
}

int main() {
    size_t weights[5] = {2, 2, 4, 6, 3};
    size_t allowed_weight = 9;
    size_t total_weight = knapsack(weights, 5, allowed_weight);
    cout << "total weight = " << total_weight << endl;
    return 0;
}
