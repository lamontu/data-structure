/* tarjan.cpp */

#include <iostream>
#include <vector>

using namespace std;

const int N = 201;

vector<int> G[N];
int n, m, low[N], dfn[N];
bool is_cut[N];
int father[N];
int tim = 0;

void input() {
  cin >> n >> m;
  char u, v;
  int a, b;
  for (int i = 1; i <= m; ++i) {
    cin >> u >> v;
    a = u - 'A';
    b = v - 'A';
    G[a].push_back(b);
    G[b].push_back(a);
  }
}

void Tarjan(int i, int fa) {
  father[i] = fa;
  dfn[i] = low[i] = tim++;
  for (int j = 0; j < G[i].size(); ++j) {
    int k = G[i][j];
    if (dfn[k] == -1) {
      Tarjan(k, i);
      low[i] = min(low[i], low[k]);
    } else if (fa != k) {
      low[i] = min(low[i], dfn[k]);
    }
  }
}

void Count() {
  int rootson = 0;
  Tarjan(0, -1);
  for (int i = 1; i < n; ++i) {
    int v = father[i];
    if (v == 0) {
      rootson++;
    } else {
      if (low[i] >= dfn[v]) {
        is_cut[v] = true;
      }
    }
  }

  if (rootson > 1) {
    is_cut[0] = true;
  }

  for (int i = 0; i < n; ++i) {
    if (is_cut[i]) {
      cout << i << ", ";
    }
  }
  cout << endl;

  for (int i = 0; i < n; ++i) {
    int v = father[i];
    if (v != -1 && low[i] > dfn[v]) {
      cout << "(" << v << ", " << i << ")" << ", ";
    }
  }
  cout << endl;
}

int main(int argc, char* argv[]) {
  input();

  memset(dfn, -1, sizeof(dfn));
  memset(father, 0, sizeof(father));
  memset(low, -1, sizeof(low));
  memset(is_cut, false, sizeof(is_cut));

  Count();

  return 0;
}
