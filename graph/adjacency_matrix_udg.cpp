/* adjacency_matrix_udg.cpp
 * Adjacency Matrix of Undirected Graph
 */

#include <iostream>

using namespace std;

const int MAX = 100;

class MatrixUdg {
 private:
  char vertexes_[MAX];
  int vertex_num_;
  int edge_num_;
  int matrix_[MAX][MAX];

 public:
  MatrixUdg();
  MatrixUdg(char vertexes[], int vlen, char edges[][2], int elen);
  // ~MatrixUdg() {  }
  void DFS() const;
  void BFS() const;
  void Print() const;

 private:
  char read_char();
  int get_position(char ch) const;
  int first_vertex(int v) const;
  int next_vertex(int v, int w) const;
  void dfs(int i, int* visited) const;
};

char MatrixUdg::read_char() {
  char ch;
  // Input one character one time
  do {
    cin >> ch;
  } while (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')));
  return ch;
}

int MatrixUdg::get_position(char ch) const {
  int i;
  for (i = 0; i < vertex_num_; ++i) {
    if(vertexes_[i] == ch) return i;
  }
  return -1;
}

MatrixUdg::MatrixUdg() {
  char c1, c2;
  int i, p1, p2;
  cout << "Input vertex number:";
  cin >> vertex_num_;
  cout << "Input edge number:";
  cin >> edge_num_;
  if (vertex_num_ < 1 || edge_num_ < 0
      || (edge_num_ > (vertex_num_ * (vertex_num_ - 1)))) {
    cout << "Input error: invalid parameters!" << endl;
    return;
  }
  for (i = 0; i < vertex_num_; ++i) {
    cout << "vertex(" << i << "): ";
    vertexes_[i] = read_char();
  }
  for (i = 0; i < edge_num_; ++i) {
    cout << "edge(" << i << "): ";
    c1 = read_char();
    c2 = read_char();
    p1 = get_position(c1);
    p2 = get_position(c2);
    if (p1 == -1 || p2 == -1) {
      cout << "Input error: invalid edge!" << endl;
      return;
    }
    matrix_[p1][p2] = 1;
    matrix_[p2][p1] = 1;  // This is different from directed graph.
  }
}

MatrixUdg::MatrixUdg(char vertexes[], int vlen, char edges[][2], int elen) {
  int i, p1, p2;
  vertex_num_ = vlen;
  edge_num_ = elen;
  for (i = 0; i < vertex_num_; ++i) {
    vertexes_[i] = vertexes[i];
  }
  for (i = 0; i < edge_num_; ++i) {
    p1 = get_position(edges[i][0]);
    p2 = get_position(edges[i][1]);
    matrix_[p1][p2] = 1;
    matrix_[p2][p1] = 1;  // This is different from directed graph.
  }
}

int MatrixUdg::first_vertex(int v) const {
  int i;
  if (v < 0 || v > (vertex_num_ - 1)) return -1;
  for (i = 0; i < vertex_num_; ++i) {
    if (1 == matrix_[v][i]) return i;
  }
  return -1;
}

int MatrixUdg::next_vertex(int v, int w) const {
  int i;
  if (v < 0 || v > (vertex_num_ - 1) || w < 0 || w > (vertex_num_ - 1)) {
    return -1;
  }
  for (i = w + 1; i < vertex_num_; ++i) {
    if (1 == matrix_[v][i]) return i;
  }
  return -1;
}

void MatrixUdg::dfs(int i, int* visited) const {
  int w;
  visited[i] = 1;
  cout << vertexes_[i] << ", ";
  for (w = first_vertex(i); w >= 0; w = next_vertex(i, w)) {
    if (!visited[w]) {
      dfs(w, visited);
    }
  }
}

void MatrixUdg::DFS() const {
  int i;
  int visited[MAX];
  for (i = 0; i < vertex_num_; ++i) {
    visited[i] = 0;
  }
  cout << "DFS: ";
  for (i = 0; i < vertex_num_; ++i) {
    if (!visited[i]) {
      dfs(i, visited);
    }
  }
  cout << endl;
}

void MatrixUdg::BFS() const {
  int head = 0;
  int rear = 0;
  int queue[MAX];
  int visited[MAX];
  int i, j, k;
  for (i = 0; i < vertex_num_; ++i) {
    visited[i] = 0;
  }
  cout << "BFS: ";
  for (i = 0; i < vertex_num_; ++i) {
    if (!visited[i]) {
      visited[i] = 1;
      cout << vertexes_[i] << ", ";
      queue[rear++] = i;
    }
    while (head != rear) {
      j = queue[head++];
      for (k = first_vertex(j); k >= 0; k = next_vertex(j, k)) {
        if (!visited[k]) {
          visited[k] = 1;
          cout << vertexes_[k] << ", ";
          queue[rear++] = k;
        }
      }
    }
  }
  cout << endl;
} 

void MatrixUdg::Print() const {
  int i, j;
  cout << "Matrix Graph:" << endl;
  for (i = 0; i < vertex_num_; ++i) {
    for (j = 0; j < vertex_num_; ++j) {
      cout << matrix_[i][j] << ", ";
    }
    cout << endl;
  }
}

int main(int argc, char* argv[]) {
  char vertexes[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  char edges[][2] = {
    {'A', 'C'}, {'A', 'D'}, {'A', 'F'}, {'B', 'C'},
    {'C', 'D'}, {'E', 'G'}, {'F', 'G'}
  };
  int vlen = sizeof(vertexes) / sizeof(vertexes[0]);
  int elen = sizeof(edges) / sizeof(edges[0]);
  MatrixUdg* pUdg;
  // pUdg = new MatrixUdg();  // Manually input
  pUdg = new MatrixUdg(vertexes, vlen, edges, elen);
  pUdg->DFS();
  pUdg->BFS();
  pUdg->Print();

  delete pUdg;
  pUdg = nullptr;

  return 0;
}
