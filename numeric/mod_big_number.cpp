#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

using int64 = long long;

int64 mod_big_num(int64 n, int64 p) {
    int res = 0;
    while (n) {
        int digit = n % 10;
        n /= 10;
        res = ((res * 10) % p + digit % p) % p;
    }
    return res;
}

int main() {
    int64 n = 3333335;
    int64 p = 11;
    int64 res = mod_big_num(n, p);
    cout << res << endl;
}