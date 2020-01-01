#include "treap.h"

static void Visit(const int& a) {
  cout << a << ", ";
}

typedef void(*FuncType)(const int&);
static FuncType pfun = Visit;

int main() {
  FILE* fp = freopen("out.txt", "w", stdout);
  int const M = 10000;
  int const L = 500;
  Treap<int> tree;
  srand(0);
  cout << "## Add elements into treap:" << endl;
  for (int i = 0; i < L; ++i) {
    int a = rand() % M;
    cout << a << ", ";
    tree.Insert(a);
  }
  cout << endl;

  cout << "## Count: " << COUNT << endl;
  cout << "## Height: " << tree.Height() << endl;

  TreapNode<int>* root = tree.Root();
  cout << "### Root element is: " << root->key << endl;
  cout << "### Root count is: " << root->count << endl;
  cout << "### Root size is: " << root->size << endl;
  cout << "### Root priority is: " << root->priority << endl;

  cout << "## InOrder Traverse:" << endl;
  tree.InOrderTraverse(pfun);  cout << endl;

  fclose(fp);

  return 0;
}
