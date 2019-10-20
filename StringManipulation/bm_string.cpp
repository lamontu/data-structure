#include <iostream>

using namespace std;

const int CHAR_SET_SIZE = 256;

void bad_character_rule(const char pattern[], int size, int bad_chars[]) {
    for (int i = 0; i < CHAR_SET_SIZE; ++i) {
        bad_chars[i] = -1;
    }
    for (int i = 0; i < size; ++i) {
        int ascii = (int)pattern[i];
        bad_chars[ascii] = i;
    }
}

// suffixes[k] = j
// For every k, there is a good suffix(pattern[size-k,size-1]) of the pattern
// Find the last occurence of subsequence(pattern[j,j+k-1]) that match the good suffix(pattern[size-k,size-1])
// suffixes' index(k) is the length of the good-suffix(pattern[size-k, size-1])
// suffixes' value(j) is the begin index of the last occurred subsequence(pattern[j,j+k-1])
void good_suffix_shift(const char pattern[], int size, int suffixes[], bool prefix[]) {
    for (int i = 0; i < size; ++i) {
        suffixes[i] = -1;
        prefix[i] = false;
    }
    for (int i = 0; i < size - 1; ++i) {
        // For every i, we find the overlap suffix size between pattern[0, i] and pattern[0, size-1]
        // Find the greatest overlap and its begin index in the pattern.
        int begin_index = i;
        int overlap_size = 1;
        while (begin_index >= 0 && pattern[begin_index] == pattern[size - overlap_size]) {
            suffixes[overlap_size++] = begin_index--;
        }
        if (begin_index == -1) {
            prefix[overlap_size] = true;
        }
    }
}

int shift_by_good_suffix(int bad_char_index, int pattern_size, int suffix[], bool prefix[]) {
    int suffix_length = pattern_size - (bad_char_index + 1);
    if (suffix[suffix_length] != -1) {
        return (bad_char_index + 1) - suffix[suffix_length]; // move step number
    }
    for (int suffix_sub_start = bad_char_index + 2; suffix_sub_start <= pattern_size - 1; 
        ++suffix_sub_start) {
        if (prefix[pattern_size - suffix_sub_start]) {
            // move step number: suffix_sub_start - suffix[pattern_size - suffix_sub_start]
            return suffix_sub_start;
        }
    }
    return pattern_size;
}

int boyer_moore(const char target[], int target_size, const char pattern[], int pattern_size) {
    int bad_chars[CHAR_SET_SIZE];
    bad_character_rule(pattern, pattern_size, bad_chars);
    int suffix[pattern_size];
    bool prefix[pattern_size];
    good_suffix_shift(pattern, pattern_size, suffix, prefix);

    int i = 0; // pattern head index in the target
    while (i <= target_size - pattern_size) {
        int j; // current comparing index in the pattern
        for (j = pattern_size - 1; j >= 0; --j) { // compare from tail to head
            if (target[i + j] != pattern[j]) {
                break;
            }
        }
        if (j < 0) {
            return i;
        }
        int x = j - bad_chars[(int)target[i + j]];
        int y = 0;
        if (j < target_size - 1) { // there are good suffix
            y = shift_by_good_suffix(j, pattern_size, suffix, prefix);
        }
        i = i + (x > y ? x : x);
        cout << "bad char move: " << x << "; " << "good suffix move: " << y << endl;
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
    int pos = boyer_moore(target, target_size, pattern, pattern_size);
    cout << "position = " << pos << endl;
    return 0;
}
