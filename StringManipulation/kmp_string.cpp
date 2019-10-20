#include <iostream>

using namespace std;

// next[i] = k
// Find the longest matched prefix(pattern[0,k]), suffix(pattern[i-k,i]) pair for every good prefix(pattern[0,i])
// next's index (i) is the end index of a good-prefix(pattern[0,i]) of the pattern
// next's value (k) is the end index of of the longest-matched-prefix(pattern[0,k]) of the good-prefix(pattern[0,i])
void create_next(const char pattern[], int size, int next[]) {
    next[0] = -1;
    int end_index = -1;
    // Calculate next[i] for every good-prefix(pattern[0,i]) of pattern
    for (int i = 1; i < size; ++i) {
        // Calcualte next[i] based on next[i-1]
        // end_index = next[i-1];
        while (end_index != -1 && pattern[end_index + 1] != pattern[i]) {
            end_index = next[end_index];
        }
        if (pattern[end_index + 1] == pattern[i]) {
            end_index++;            
        }
        next[i] = end_index;
        cout << "end_index: " << end_index << endl;
    }
}

int kmp(const char target[], int target_size, const char pattern[], int pattern_size) {
    int next[pattern_size];
    create_next(pattern, pattern_size, next);
    int j = 0;
    for (int i = 0; i < target_size; ++i) {
        while (j > 0 && target[i] != pattern[j]) {
            j = next[j - 1] + 1;
        }
        if (target[i] == pattern[j]) {
            ++j;
        }
        if (j == pattern_size) {
            return i - pattern_size + 1;
        }
    }
    return -1;
}

int main() {
    string strPattern("AT THAT");
    string strTarget("WHICH FINALLY HALTS.  AT THAT POINT...");
    const char* pattern = strPattern.c_str();
    const int pattern_size = strPattern.length();
    const char* target = strTarget.c_str();
    const int target_size = strTarget.length();
    int pos = kmp(target, target_size, pattern, pattern_size);
    cout << "position = " << pos << endl;
    return 0;
}