#include <cstdio>
#include <cstdlib>

using std::fopen;
using std::fclose;
using std::fscanf;

const int WORD = 32;  // The type of bitmap is 32 bits int.
const int SHIFT = 5;  // 2^SHIFT = WORD
const int MASK = 0x1F;
const int N = 1024*16;

static int bitmap[1 + N / WORD];

/*
 * m mod 2^k ==> m & (2^k - 1)
 */
static void set(int i) {
  bitmap[i >> SHIFT] |= (0x1u << (i & MASK));
}

static void clear(int i) {
  bitmap[i >> SHIFT] &= ~(0x1u << (i & MASK));
}

static int test(int i) {
  return bitmap[i >> SHIFT] & (1 << (i & MASK));
}

// Sort without duplicated number
int main() {
  FILE* in = fopen("./bitmap/in.txt", "r");
  FILE* out = fopen("./bitmap/out.txt", "w");
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
