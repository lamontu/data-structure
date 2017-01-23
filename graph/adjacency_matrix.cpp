/* adjacency_matrix.cpp */

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
  MatrixUdg() {
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
      vertexes_[i] = ReadChar();
    }
    for (i = 0; i < edge_num_; ++i) {
      cout << "edge(" << i << "): ";
      c1 = ReadChar();
      c2 = ReadChar();
      p1 = GetPosition(c1);
      p2 = GetPosition(c2);
      if (p1 == -1 || p2 == -1) {
        cout << "Input error: invalid edge!" << endl;
        return;
      }
      matrix_[p1][p2] = 1;
      matrix_[p2][p1] = 1;
    }
  }

  MatrixUdg(char vertexes[], int vlen, char edges[][2], int elen) {
    int i, p1, p2;
    vertex_num_ = vlen;
    edge_num_ = elen;
    for (i = 0; i < vertex_num_; ++i) {
      vertexes_[i] = vertexes[i];
    }
    for (i = 0; i < edge_num_; ++i) {
      p1 = GetPosition(edges[i][0]);
      p2 = GetPosition(edges[i][1]);

      matrix_[p1][p2] = 1;
      matrix_[p2][p1] = 1;
    }
  }

  ~MatrixUdg() {  }
  void Print() {
    int i, j;
    cout << "Matrix Graph:" << endl;
    for (i = 0; i < vertex_num_; ++i) {
      for (j = 0; j < vertex_num_; ++j) {
        cout << matrix_[i][j] << ", ";
      }
      cout << endl;
    }
  }
 private:
  char ReadChar() {
    char ch;
    // Input one character one time
    do {
      cin >> ch;
    } while (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')));
    return ch;
  }

  int GetPosition(char ch) {
    int i;
    for (i = 0; i < vertex_num_; ++i) {
      if(vertexes_[i] == ch) return i;
    }
    return -1;
  }
};

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
