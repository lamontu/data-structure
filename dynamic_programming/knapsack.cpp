#include <iostream>

using std::cout;
using std::endl;

// weights[i]: the weight of the item i
// weight: the allowed total weight of the item in the knapsack.
int knapsack(const int weights[], const int num, const int weight) {
    bool states[num][weight+1];
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

    for (int i = weight; i >= 0; --i) {
        if (states[num-1]) {
            return i;
        }
    }
}

int main() {
    int weights[5] = {2, 2, 4, 6, 3};
    int allowed_weight = 9;
    int total_weight = knapsack(weights, 5, allowed_weight);
    cout << "total weight = " << total_weight << endl;
    return 0;
}