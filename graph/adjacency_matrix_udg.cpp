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
  ~MatrixUdg() {  }
  void Print();

 private:
  char read_char();
  int get_position(char ch);
};

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
    matrix_[p2][p1] = 1;
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
    matrix_[p2][p1] = 1;
  }
}

char MatrixUdg::read_char() {
  char ch;
  // Input one character one time
  do {
    cin >> ch;
  } while (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')));
  return ch;
}

int MatrixUdg::get_position(char ch) {
  int i;
  for (i = 0; i < vertex_num_; ++i) {
    if(vertexes_[i] == ch) return i;
  }
  return -1;
}

void MatrixUdg::Print() {
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
  // pUdg = new MatrixUdg(vertexes, vlen, edges, elen);
  pUdg = new MatrixUdg();  // Mannually input
  pUdg->Print();
  return 0;
}
