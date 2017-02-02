/* modexp_recursion.cpp */

#include <iostream>

using namespace std;

int modexp_recursion(int a, int n, int p) {
  int t = 1;
  if (n == 0) return 1;
  if (n == 1) return a % p;

  t = modexp_recursion(a, n >> 1, p);
  t = t * t % p;
  if (n & 0x1) {
    t = t * a % p;
  }

  return t;
}

int main(int argc, char* argv[]) {
  int a = 2, n = 5, p = 3;
  int ret = modexp_recursion(a, n, p);
  cout << ret << endl;
  return 0;
}
