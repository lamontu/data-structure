#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

using int64 = long long;

int add_mod(int a, int b, int p) {
    a %= p;
    b %= p;
    return (a + b) % p;
}

int sub_mod(int a, int b, int p) {
    a %= p;
    b %= p;
    return (a - b + p) % p;
}

int64 mul_mod(int a, int b, int p) {
    a %= p;
    b %= p;
    return a * b % p;
}

int biginteger_mod(int n, int p) {
    int64 res = 0;
    while (n) {
        int digit = n % 10;
        n /= 10;
        // res = ((res * 10) % p + digit % p) % p;  // equal to below
        res = ((res * 10) + digit) % p;
    }
    return (int)res;
}

int main() {
    int n = 6145156;
    int p = 3;
    int res1 = biginteger_mod(n, p);
    cout << res1 << endl;
}