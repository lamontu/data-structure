/* modexp.cpp */

#include <iostream>

using namespace std;

// rule 1: (a + b) % p = (a % p + b % p) % p
// rule 2: (a - b) % p = (a % p - b % p + p) % p
// rule 3: (a * b) % p = ((a % p) * (b % p)) % p
// rule 4: (pow(a, b)) % p = (pow(a % p, b)) % p

int modexp(int a, int n, int p) {
  int ret = 1;
  int tmp = a % p;  // rule 4
  if (tmp == 0)
    return 0;

  while (n) {
    if (n & 0x1) {
      ret = ret * tmp % p;
    }
    tmp = tmp * tmp % p;
    n >>= 1;
  }
  return ret;
}

int main(int argc, char* argv[]) {
  int a = 3781, n = 23947, p = 31847;
  int ret = modexp(a, n, p);
  cout << ret << endl;

  return 0;
}
