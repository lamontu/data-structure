/* modexp_simple.cpp */

#include <iostream>

using namespace std;

/* (a * b) % c = ((a % c) * b) % c
 * a^2 % p = ((a % p) * a) % p
 */
int modexp_simple(int a, int n, int p) {
  int ret = 1;
  while(n--) {
    ret = a * ret % p;
  }
  return ret;
}

int main(int argc, char* argv[]) {
  int a = 3, n = 3, p = 4;
  int ret = modexp_simple(a, n, p);
  cout << ret << endl;

  return 0;
}
