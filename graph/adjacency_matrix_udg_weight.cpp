/* adjacency_matrix_udg_weight.cpp
 * Adjacency Matrix of Undirected Graph with Weight
 */

#include <iomanip>
#include <iostream>

using namespace std;

const int MAX = 100;
const int INF = ~(0x1u << 31);

// Store the information of an edge
class EData {
 public:
  int weight;
  char start;
  char end;

  EData() {  }
  EData(char s, char e, int w) : weight(w), start(s), end(e) {  }
};

class MatrixUdg {
 private:
  char vertexes_[MAX];
  size_t vertex_num_;
  size_t edge_num_;
  int matrix_[MAX][MAX];

 public:
  MatrixUdg();
  MatrixUdg(char vertexes[], size_t vlen, int matrix[][MAX]);
  // ~MatrixUdg() {  }
  void DFS() const;
  void BFS() const;

  void Print() const;
  void Kruskal() const;
  void Prim(size_t start) const;
  void Dijkstra(size_t source, int previous[], int distance[]);
  void Floyd(size_t path[][MAX], int distance[][MAX]);

 private:
  char read_char();
  size_t get_position(char ch) const;
  int first_vertex(int v) const;
  int next_vertex(int v, int w) const;
  void dfs(int i, bool* visited) const;

  EData* get_edges() const;
  void sort_edges(EData* edges, size_t elen) const;
  size_t get_end(size_t vends[], size_t i) const;

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

  size_t i, j;
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
  int weight;
  for (i = 0; i < edge_num_; ++i) {
    cout << "edge(" << i << "): ";
    char c1 = read_char();
    char c2 = read_char();
    cin >> weight;
    size_t p1 = get_position(c1);
    size_t p2 = get_position(c2);
    if (p1 == MAX || p2 == MAX) {
      cout << "Input error: invalid edge!" << endl;
      return;
    }
    matrix_[p1][p2] = weight;
    matrix_[p2][p1] = weight;
  }
}

MatrixUdg::MatrixUdg(char vertexes[], size_t vlen, int matrix[][MAX]) {
  vertex_num_ = vlen;
  edge_num_ = 0;

  size_t i, j;
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

void MatrixUdg::dfs(int i, bool* visited) const {
  int w;
  visited[i] = true;
  cout << vertexes_[i] << ", ";
  for (w = first_vertex(i); w >= 0; w = next_vertex(i, w)) {
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
      int k;
      for (k = first_vertex(j); k >= 0; k = next_vertex(j, k)) {
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
      if (matrix_[i][j] == INF) {
        cout << setw(4) << "INF";
      } else {
        cout << setw(4) << matrix_[i][j];
      }
    }
    cout << endl;
  }
}

EData* MatrixUdg::get_edges() const {
  int index = 0;
  EData* edges;
  edges = new EData[edge_num_];
  for (size_t i = 0; i < vertex_num_; ++i) {
    for (size_t j = i + 1; j < vertex_num_; ++j) {
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
void MatrixUdg::sort_edges(EData* edges, size_t elen) const {
  size_t i, j;
  for (i = 0; i < elen - 1; ++i) {
    size_t minimum = i;
    for (j = i + 1; j < elen; ++j) {
      if (edges[minimum].weight > edges[j].weight) {
        minimum = j;
      }
    }
    if (minimum == i) continue;
    swap(edges[minimum], edges[i]);
  }
}

size_t MatrixUdg::get_end(size_t vends[], size_t i) const {
  while (vends[i] != 0) {
    i = vends[i];
  }
  return i;
}

void MatrixUdg::Kruskal() const {
  int i, m, n;
  int length;
  int index = 0;
  size_t vends[MAX] = {0};
  EData* edges;  // All edges of the graph
  EData rets[MAX];  // The edges of the kruskal spanning tree

  edges = get_edges();
  sort_edges(edges, edge_num_);

  for (i = 0; i < edge_num_; ++i) {
    size_t p1 = get_position(edges[i].start);
    size_t p2 = get_position(edges[i].end);
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

void MatrixUdg::Prim(size_t start) const {
  int index = 0;
  char prims[MAX];
  int weights[MAX];

  prims[index++] = vertexes_[start];
  /* Initialize the weight of edges that connect each vertex with the spanning
   * tree which only contains vertex start.
   */
  size_t i, j, k;
  for (i = 0; i < vertex_num_; ++i) {
    weights[i] = matrix_[start][i];
  }

  int minimum;
  for (i = 0; i < vertex_num_; ++i) {
    if (start == i) continue;
    j = 0;
    k = 0;
    minimum = INF;
    while (j < vertex_num_) {
      if (weights[j] != 0 && weights[j] < minimum) {
        minimum = weights[j];
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

  int sum = 0;
  for (i = 1; i < index; ++i) {
    minimum = INF;
    size_t n = get_position(prims[i]);
    for (j = 0; j < i; ++j) {
      size_t m = get_position(prims[j]);
      if (matrix_[m][n] < minimum) {
        minimum = matrix_[m][n];
      }
    }
    sum += minimum;
  }

  cout << "Prim(" << vertexes_[start] << ") = " << sum << ": ";
  for (i = 0; i < index; ++i) {
    cout << prims[i] << ", ";
  }
  cout << endl;
}

void MatrixUdg::Dijkstra(size_t source, int previous[], int distance[]) {
  size_t i, j;
  int flag[MAX];

  // Initialize the distance between vertex source and each vertex.
  for (i = 0; i < vertex_num_; ++i) {
    flag[i] = 0;  // Distance between vertex i and source has not been found.
    distance[i] = matrix_[source][i];
    if (distance[i] != INF) {
      previous[i] = source;  // Denote the previous vertex of vertex i.
    }
  }
  // Add vertex source and mark it as finished.
  flag[source] = 1;
  previous[source] = -1;

  size_t k = 0;
  // Add vertex k and mark it as finished.
  for (i = 1; i < vertex_num_; ++i) {
    int minimum = INF;
    for (j = 0; j < vertex_num_; ++j) {
      if (flag[j] == 0 && distance[j] < minimum) {
        minimum = distance[j];
        k = j;
      }
    }
    flag[k] = 1;

    // Update the distance between vertex source and remaining vertexes.
    for (j = 0; j < vertex_num_; ++j) {
      int tmp = (matrix_[k][j] == INF ? INF : (minimum + matrix_[k][j]));
      if (flag[j] == 0 && tmp < distance[j]) {
        distance[j] = tmp;
        previous[j] = k;
      }
    }
  }

  cout << "Dijkstra(" << vertexes_[source] << "): " << endl;
  for (i = 0; i < vertex_num_; ++i) {
    cout << "  shortest(" << vertexes_[source] << ", " << vertexes_[i] << ") = "
         << distance[i] << endl;
  }
}

void MatrixUdg::Floyd(size_t path[][MAX], int distance[][MAX]) {
  int i, j, k;

  for (i = 0; i < vertex_num_; ++i) {
    for (j = 0; j < vertex_num_; ++j) {
      distance[i][j] = matrix_[i][j];
      path[i][j] = j;  // Vertex j is on the path from vertex i to j.
    }
  }

  int tmp;
  for (k = 0; k < vertex_num_; ++k) {
    for (i = 0; i < vertex_num_; ++i) {
      for (j = 0; j < vertex_num_; ++j) {
        tmp = (distance[i][k] == INF || distance[k][j] == INF)
              ? INF : (distance[i][k] + distance[k][j]);
        if (distance[i][j] > tmp) {
          distance[i][j] = tmp;
          path[i][j] = path[i][k];
        }
      }
    }
  }

  cout << "Floyd:" << endl;
  for (i = 0; i < vertex_num_; ++i) {
    cout << setw(4) << vertexes_[i];
  }
  cout <<  endl;
  cout << "   -------------------------" << endl;
  for (i = 0; i < vertex_num_; ++i) {
    for (j = 0; j < vertex_num_; ++j) {
      if (distance[i][j] == INF) {
        cout << setw(4) << "INF";
      } else {
        cout << setw(4) << distance[i][j];
      }
    }
    cout << endl;
  }
}

int main() {
  char vertexes[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  size_t vlen = sizeof(vertexes) / sizeof(vertexes[0]);
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

  cout << "## Test Dijkstra algorithm:" << endl;
  int prev[MAX] = {0};
  int dist[MAX] = {0};
  int vs = 3;
  int vt = 5;
  pUdg->Dijkstra(vs, prev, dist);
  cout << "Previous vertex:" << endl;
  for (int i = 0; i < 20; ++i) {
    cout << prev[i] << ", ";
  }
  cout << endl;
  cout << "Path between vertex " << vertexes[vt]
       << " and " << vertexes[vs] << ": ";
  while (vt != vs) {
    cout << vertexes[vt] << "<-";
    vt = prev[vt];
  }
  cout << vertexes[vs] << endl;

  cout << "## Test Floyd algorithm:" << endl;
  size_t path[MAX][MAX] = {0};
  int floyd_distance[MAX][MAX] = {0};
  pUdg->Floyd(path, floyd_distance);

  cout << "Floyd path:" << endl;
  for (int i = 0; i < vlen; ++i) {
    cout << setw(4) << vertexes[i];
  }
  cout <<  endl;
  cout << "   -------------------------" << endl;
  for (int i = 0; i < vlen; ++i) {
    for (int j = 0; j < vlen; ++j) {
      cout << setw(4) << vertexes[path[i][j]];
    }
    cout << endl;
  }
  vs = 0;
  vt = 3;
  int k = path[vs][vt];
  cout << vertexes[vs] << "->";
  while (k != vt) {
    cout << vertexes[k] << "->";
    vs = path[k][vt];
    k = path[vs][vt];
    cout << vertexes[vs] << "->";
  }
  cout << vertexes[vt] << endl;

  delete pUdg;
  pUdg = nullptr;

  return 0;
}
