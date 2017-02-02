/* miller_rabbin.cpp */

#include <iostream>

using namespace std;

typedef long long int64;

const int MaxTest = 5;

int64 random(int64 n) {
  return (int64)((double)rand() / RAND_MAX * n + 0.5);
}

int64 modexp(int64 a, int64 n, int64 p) {
  int64 ret = 1;
  int64 tmp = a;
  while (n) {
    if (n & 0x1) {
      ret = ret * tmp % p;
    }
    tmp = tmp * tmp % p;
    n >>= 1;
  }
  return ret;
}

bool miller_rabbin(int64 p) {
  for (int i = 1; i <= MaxTest; ++i) {
    int64 a = random(p - 2) + 1;
    if (modexp(a, p - 1, p) != 1) return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  int64 n;
  cout << "Input a number: ";
  cin >> n;
  if (miller_rabbin(n)) {
    cout << "True\n" << endl;
  } else {
    cout << "False\n" << endl;
  }

  return 0;
}
