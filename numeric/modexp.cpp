/* modexp.cpp */

#include <iostream>

using namespace std;

// (a + b) % p = (a % p + b % p) % p
// (a - b) % p = (a % p - b % p + p) % p
// (a * b) % p = (a % p * b % p) % p
// (pow(a, b)) % p = (pow(a % p, b)) % p

int modexp(int a, int n, int p) {
  int ret = 1;
  int tmp = a % p;
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
