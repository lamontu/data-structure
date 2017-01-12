/* bitmap.cpp */

#include <cstdio>
#include <cstdlib>

using namespace std;

const int WORD = 32;
const int SHIFT = 5;
const int MASK = 0x1F;
const int N = 10000000;

int bitmap[1 + N / WORD];

/*
 * m mod 2^k ==> m & (2^k - 1)
 */
void set(int i) {
  bitmap[i >> SHIFT] |= (1 << (i & MASK));
}

void clear(int i) {
  bitmap[i >> SHIFT] &= ~(1 << (i & MASK));
}

int test(int i) {
  return bitmap[i >> SHIFT] & (1 << (i & MASK));
}

// Sort without duplicated number
int main(int argc, char* argv[]) {
  FILE* in = fopen("in.txt", "r");
  FILE* out = fopen("out.txt", "w");
  if (nullptr == in || nullptr == out) {
    exit(-1);
  }
  int i = 0;
  int m;
  for (i = 0; i < N; ++i) {
    clear(i);
  }
  while (!feof(in)) {
    fscanf(in, "%d", &m);
    printf("%d\n", m);
    set(m);
  }
  printf("----------------------------------------\n");

  for (i = 0; i < N; ++i) {
    if (test(i)) {
      printf("%d\n", i);
      fprintf(out, "%d\n", i);
    }
  }
  fclose(in);
  fclose(out);
  return 0;
}
