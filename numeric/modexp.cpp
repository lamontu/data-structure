/* modexp.cpp */

#include <iostream>

using namespace std;

int modexp(int a, int n, int p) {
  int ret = 1;
  int tmp = a;
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
  int a = 2, n = 5, p = 3;
  int ret = modexp(a, n, p);
  cout << ret << endl;

  return 0;
}
