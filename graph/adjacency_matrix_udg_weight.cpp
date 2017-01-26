/* adjacency_matrix_udg_weight.cpp
 * Adjacency Matrix of Undirected Graph with Weight
 */

#include <iostream>

using namespace std;

const int MAX = 100;
const int INF = ~(0x1 << 31);

// Store the information of an edge
class EData {
 public:
  char start;
  char end;
  int weight;

  EData() {  }
  EData(char s, char e, int w) : start(s), end(e), weight(w) {  }
};

class MatrixUdg {
 private:
  char vertexes_[MAX];
  int vertex_num_;
  int edge_num_;
  int matrix_[MAX][MAX];

 public:
  MatrixUdg();
  MatrixUdg(char vertexes[], int vlen, int matrix[][MAX]);
  // ~MatrixUdg() {  }
  void DFS() const;
  void BFS() const;
  void Print() const;
  void Kruskal() const;
  void Prim(int start) const;

 private:
  char read_char();
  int get_position(char ch) const;

  int first_vertex(int v) const;
  int next_vertex(int v, int w) const;
  void dfs(int i, int* visited) const;

  EData* get_edges() const;
  void sort_edges(EData* edges, int elen) const;
  int get_end(int vends[], int i) const;
};

char MatrixUdg::read_char() {
  char ch;
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
  int i, j, weight, p1, p2;
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

  for (i = 0; i < vertex_num_; ++i) {
    for (j = 0; j < vertex_num_; ++j) {
      if (i == j) {
        matrix_[i][j] = 0;
      } else {
        matrix_[i][j] = INF;
      }
    }
  }
  for (i = 0; i < edge_num_; ++i) {
    cout << "edge(" << i << "): ";
    c1 = read_char();
    c2 = read_char();
    cin >> weight;
    p1 = get_position(c1);
    p2 = get_position(c2);
    if (p1 == -1 || p2 == -1) {
      cout << "Input error: invalid edge!" << endl;
      return;
    }
    matrix_[p1][p2] = weight;
    matrix_[p2][p1] = weight;
  }
}

MatrixUdg::MatrixUdg(char vertexes[], int vlen, int matrix[][MAX]) {
  int i, j;
  vertex_num_ = vlen;
  for (i = 0; i < vertex_num_; ++i) {
    vertexes_[i] = vertexes[i];
  }

  for (i = 0; i < vertex_num_; ++i) {
    for (j = 0; j < vertex_num_; ++j) {
      matrix_[i][j] = matrix[i][j];
    }
  }
  for (i = 0; i < vertex_num_; ++i) {
    for (j = 0; j < vertex_num_; ++j) {
      if (i != j && matrix_[i][j] != INF) {
        edge_num_++;
      }
    }
  }
  edge_num_ /= 2;
}

int MatrixUdg::first_vertex(int v) const {
  int i;
  if (v < 0 || v > (vertex_num_ - 1)) return -1;
  for (i = 0; i < vertex_num_; ++i) {
    if (matrix_[v][i] != 0 && matrix_[v][i] != INF) return i;
  }
  return -1;
}

int MatrixUdg::next_vertex(int v, int w) const {
  int i;
  if (v < 0 || v > (vertex_num_ - 1) || w < 0 || w > (vertex_num_ - 1)) {
    return -1;
  }
  for (i = w + 1; i < vertex_num_; ++i) {
    if (matrix_[v][i] != 0 && matrix_[v][i] != INF) return i;
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

EData* MatrixUdg::get_edges() const {
  int i, j;
  int index = 0;
  EData* edges;
  edges = new EData[edge_num_];
  for (i = 0; i < vertex_num_; ++i) {
    for (j = i + 1; j < vertex_num_; ++j) {
      if (matrix_[i][j] != INF) {
        edges[index].start = vertexes_[i];
        edges[index].end = vertexes_[j];
        edges[index].weight = matrix_[i][j];
        index++;
      }
    }
  }
  return edges;
}

// Selection sort
void MatrixUdg::sort_edges(EData* edges, int elen) const {
  int i, j;
  int min;
  for (i = 0; i < elen - 1; ++i) {
    min = i;
    for (j = i + 1; j < elen; ++j) {
      if (edges[min].weight > edges[j].weight) {
        min = j;
      }
    }
    if (min == i) continue;
    swap(edges[min], edges[i]);
  }
}

int MatrixUdg::get_end(int vends[], int i) const {
  while (vends[i] != 0) {
    i = vends[i];
  }
  return i;
}

void MatrixUdg::Kruskal() const {
  int i, m, n, p1, p2;
  int length;
  int index = 0;
  int vends[MAX] = {0};
  EData* edges;  // All edges of the graph 
  EData rets[MAX];  // The edges of the kruskal spanning tree

  edges = get_edges();
  sort_edges(edges, edge_num_);

  for (i = 0; i < edge_num_; ++i) {
    p1 = get_position(edges[i].start);
    p2 = get_position(edges[i].end);
    m = get_end(vends, p1);
    n = get_end(vends, p2);
    if (m != n) {
      vends[m] = n;
      rets[index++] = edges[i];
    }
  }
  delete edges;
  edges = nullptr;

  length = 0;
  for (i = 0; i < index; ++i) {
    length += rets[i].weight;
  }
  cout << "Kruskal = " << length << ": ";
  for (i = 0; i < index; ++i) {
    cout << "(" << rets[i].start << "," << rets[i].end << ") ";
  }
  cout << endl;
}

void MatrixUdg::Prim(int start) const {
  int min, i, j, k, m, n, sum;
  int index = 0;
  char prims[MAX];
  int weights[MAX];
  
  prims[index++] = vertexes_[start];
  /* Initialize the weight of edges that connect each vertex with the spanning
   * tree which only contains vertex start.
   */
  for (i = 0; i < vertex_num_; ++i) {
    weights[i] = matrix_[start][i];
  }

  for (i = 0; i < vertex_num_; ++i) {
    if (start == i) continue;
    j = 0;
    k = 0;
    min = INF;
    while (j < vertex_num_) {
      if (weights[j] != 0 && weights[j] < min) {
        min = weights[j];
        k = j;
      }
      j++;
    }
    prims[index++] = vertexes_[k];
    weights[k] = 0; 
    /* Update the weight of edges that connect each vertex with the spanning
     * tree which adds a new vertex k.
     */
    for (j = 0; j < vertex_num_; ++j) {
      if (weights[j] != 0 && matrix_[k][j] < weights[j]) {
        weights[j] = matrix_[k][j];
      }
    }
  }

  sum = 0;
  for (i = 1; i < index; ++i) {
    min = INF;
    n = get_position(prims[i]);
    for (j = 0; j < i; ++j) {
      m = get_position(prims[j]);
      if (matrix_[m][n] < min) {
        min = matrix_[m][n];
      }
    }
    sum += min;
  }

  cout << "Prim(" << vertexes_[start] << ") = " << sum << ": ";
  for (i = 0; i < index; ++i) {
    cout << prims[i] << ", ";
  }
  cout << endl;
}

int main(int argc, char* argv[]) {
  char vertexes[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  int vlen = sizeof(vertexes) / sizeof(vertexes[0]);
  int matrix[7][MAX] = {
    {0,   12,  INF, INF, INF, 16,  14 },
    {12,  0,   10,  INF, INF, 7,   INF},
    {INF, 10,  0,   3,   5,   6,   INF},
    {INF, INF, 3,   0,   4,   INF, INF},
    {INF, INF, 5,   4,   0,   2,   8  },
    {16,  7,   6,   INF, 2,   0,   9  },
    {14,  INF, INF, INF, 8,   9,   0  }
  };
  MatrixUdg* pUdg;
  // pUdg = new MatrixUdg();  // Manually input
  pUdg = new MatrixUdg(vertexes, vlen, matrix);
  pUdg->DFS();
  pUdg->BFS();
  pUdg->Print();
  pUdg->Kruskal();
  pUdg->Prim(0);

  delete pUdg;
  pUdg = nullptr;
  return 0;
}
