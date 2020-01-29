/* adjacency_matrix_udg.cpp
 * Adjacency Matrix of Undirected Graph
 */

#include <iostream>

using namespace std;

const int MAX = 100;

class MatrixUdg {
 private:
  size_t vertex_num_;
  size_t edge_num_;
  int matrix_[MAX][MAX];
  char vertexes_[MAX];

 public:
  MatrixUdg();
  MatrixUdg(char vertexes[], size_t vlen, char edges[][2], size_t elen);
  // ~MatrixUdg() {  }
  void DFS() const;
  void BFS() const;

  void Print() const;

 private:
  char read_char();
  size_t get_position(char ch) const;
  size_t first_vertex(size_t v) const;
  size_t next_vertex(size_t v, size_t w) const;
  void dfs(size_t i, bool* visited) const;

};

char MatrixUdg::read_char() {
  char ch;
  // Input one character one time
  do {
    cin >> ch;
  } while (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')));
  return ch;
}

size_t MatrixUdg::get_position(char ch) const {
  for (size_t i = 0; i < vertex_num_; ++i) {
    if(vertexes_[i] == ch) return i;
  }
  return MAX;
}

MatrixUdg::MatrixUdg() {
  cout << "Input vertex number:";
  cin >> vertex_num_;
  cout << "Input edge number:";
  cin >> edge_num_;
  if (vertex_num_ < 1 || edge_num_ > vertex_num_ * (vertex_num_ - 1)) {
    cout << "Input error: invalid parameters!" << endl;
    return;
  }

  size_t i;
  for (i = 0; i < vertex_num_; ++i) {
    cout << "vertex(" << i << "): ";
    vertexes_[i] = read_char();
  }
  for (i = 0; i < edge_num_; ++i) {
    cout << "edge(" << i << "): ";
    char c1 = read_char();
    char c2 = read_char();

    size_t p1 = get_position(c1);
    size_t p2 = get_position(c2);
    if (p1 == MAX || p2 == MAX) {
      cout << "Input error: invalid edge!" << endl;
      return;
    }
    matrix_[p1][p2] = 1;
    matrix_[p2][p1] = 1;  // This is different from directed graph.
  }
}

MatrixUdg::MatrixUdg(char vertexes[], size_t vlen, char edges[][2], size_t elen) {
  vertex_num_ = vlen;
  edge_num_ = elen;

  size_t i;
  for (i = 0; i < vertex_num_; ++i) {
    vertexes_[i] = vertexes[i];
  }
  for (i = 0; i < edge_num_; ++i) {
    size_t p1 = get_position(edges[i][0]);
    size_t p2 = get_position(edges[i][1]);
    matrix_[p1][p2] = 1;
    matrix_[p2][p1] = 1;  // This is different from directed graph.
  }

}

size_t MatrixUdg::first_vertex(size_t v) const {
  if (v > vertex_num_ - 1) return MAX;
  for (size_t i = 0; i < vertex_num_; ++i) {
    if (1 == matrix_[v][i]) return i;
  }
  return MAX;
}

size_t MatrixUdg::next_vertex(size_t v, size_t w) const {
  if (v > vertex_num_ - 1 || w > vertex_num_ - 1) {
    return MAX;
  }
  for (size_t i = w + 1; i < vertex_num_; ++i) {
    if (1 == matrix_[v][i]) return i;
  }
  return MAX;
}

void MatrixUdg::dfs(size_t i, bool* visited) const {
  visited[i] = true;
  cout << vertexes_[i] << ", ";
  for (size_t w = first_vertex(i); w != MAX; w = next_vertex(i, w)) {
    if (!visited[w]) {
      dfs(w, visited);
    }
  }
}

void MatrixUdg::DFS() const {
  size_t i;
  bool visited[MAX];
  for (i = 0; i < vertex_num_; ++i) {
    visited[i] = false;
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
  size_t queue[MAX];
  bool visited[MAX];
  size_t i, j;
  for (i = 0; i < vertex_num_; ++i) {
    visited[i] = false;
  }
  cout << "BFS: ";
  for (i = 0; i < vertex_num_; ++i) {
    if (!visited[i]) {
      visited[i] = true;
      cout << vertexes_[i] << ", ";
      queue[rear++] = i;
    }
    while (head != rear) {
      j = queue[head++];
      for (size_t k = first_vertex(j); k != MAX; k = next_vertex(j, k)) {
        if (!visited[k]) {
          visited[k] = true;
          cout << vertexes_[k] << ", ";
          queue[rear++] = k;
        }
      }
    }
  }
  cout << endl;
}

void MatrixUdg::Print() const {
  cout << "Matrix Graph:" << endl;
  for (size_t i = 0; i < vertex_num_; ++i) {
    for (size_t j = 0; j < vertex_num_; ++j) {
      cout << matrix_[i][j] << ", ";
    }
    cout << endl;
  }
}

int main() {
  char vertexes[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  char edges[][2] = {
    {'A', 'C'}, {'A', 'D'}, {'A', 'F'}, {'B', 'C'},
    {'C', 'D'}, {'E', 'G'}, {'F', 'G'}
  };
  size_t vlen = sizeof(vertexes) / sizeof(vertexes[0]);
  size_t elen = sizeof(edges) / sizeof(edges[0]);
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
