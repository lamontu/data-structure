/* adjacency_list_udg_weight.cpp
 * Adjacency List of Undirected Graph with Weight
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

class ListUdg {
 private:
  struct ENode {
    ENode* next_edge;
    size_t vertex_index;  // The vertex this edge points to
    int weight;  // This is different from Graph without weight
  };

  struct VNode {
    ENode* first_edge;  // Store all jointed edges in a singly linked list
    char data;
  };

  size_t vertex_num_;
  size_t edge_num_;
  VNode vertexes_[MAX];

 public:
  ListUdg();
  ListUdg(char vertexes[], size_t vlen, EData* edges[], size_t elen);
  // ~ListUdg() {  }
  void DFS() const;
  void BFS() const;

  void Print() const;
  void Kruskal() const;
  void Prim(size_t start) const;
  void Dijkstra(size_t source, size_t previous[], int distance[]);
  void Floyd(size_t path[MAX][MAX], int distance[MAX][MAX]);

 private:
  char read_char();
  size_t get_position(char ch) const;
  void link_last(ENode* list, ENode* node) const;
  void dfs(size_t i, bool* visited) const;
  EData* get_edges() const;
  void sort_edges(EData* edges, size_t elen) const;
  size_t get_end(size_t vends[], size_t i) const;
  int get_weight(size_t start, size_t end) const;
};

char ListUdg::read_char() {
  char ch;
  // Input one character one time
  do {
    cin >> ch;
  } while (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')));
  return ch;
}

size_t ListUdg::get_position(char ch) const {
  for (size_t i = 0; i < vertex_num_; ++i) {
    if(vertexes_[i].data == ch) return i;
  }
  return MAX;
}

void ListUdg::link_last(ENode* list, ENode* node) const {
  ENode* p = list;
  while (p->next_edge) {
    p = p->next_edge;
  }
  p->next_edge = node;
}

ListUdg::ListUdg() {
  ENode *node1, *node2;
  int weight;

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
    cout << "vertex(" << i <<"): ";
    vertexes_[i].data = read_char();
    vertexes_[i].first_edge = nullptr;
  }
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

    node1 = new ENode();
    node1->vertex_index = p2;
    node1->weight = weight;
    if (nullptr == vertexes_[p1].first_edge) {
      vertexes_[p1].first_edge = node1;
    } else {
      link_last(vertexes_[p1].first_edge, node1);
    }

    /* This is different from directed graph. */
    node2 = new ENode();
    node2->vertex_index = p1;
    node2->weight = weight;
    if (nullptr == vertexes_[p2].first_edge) {
      vertexes_[p2].first_edge = node2;
    } else {
      link_last(vertexes_[p2].first_edge, node2);
    }

  }
}

ListUdg::ListUdg(char vertexes[], size_t vlen, EData* edges[], size_t elen) {
  ENode *node1, *node2;
  vertex_num_ = vlen;
  edge_num_ = elen;

  size_t i;
  for (i = 0; i < vertex_num_; ++i) {
    vertexes_[i].data = vertexes[i];
    vertexes_[i].first_edge = nullptr;
  }
  for (i = 0; i < edge_num_; ++i) {
    char c1 = edges[i]->start;
    char c2 = edges[i]->end;
    int weight = edges[i]->weight;
    size_t p1 = get_position(c1);
    size_t p2 = get_position(c2);
    if (p1 == MAX || p2 == MAX) {
      cout << "Input error: invalid edge!" << endl;
      return;
    }

    node1 = new ENode();
    node1->vertex_index = p2;
    node1->weight = weight;
    if (nullptr == vertexes_[p1].first_edge) {
      vertexes_[p1].first_edge = node1;
    } else {
      link_last(vertexes_[p1].first_edge, node1);
    }

    /* This is different from directed graph. */
    node2 = new ENode();
    node2->vertex_index = p1;
    node2->weight = weight;
    if (nullptr == vertexes_[p2].first_edge) {
      vertexes_[p2].first_edge = node2;
    } else {
      link_last(vertexes_[p2].first_edge, node2);
    }

  }
}

void ListUdg::dfs(size_t i, bool* visited) const {
  ENode* node;
  visited[i] = true;
  cout << vertexes_[i].data <<", ";
  node = vertexes_[i].first_edge;
  while (node != nullptr) {
    if (!visited[node->vertex_index]) {
      dfs(node->vertex_index, visited);
    }
    node = node->next_edge;
  }
}

void ListUdg::DFS() const {
  size_t i;
  bool visited[MAX];
  for (i = 0; i < vertex_num_; ++i) {
    visited[i] = false;
  }
  cout << "DFS: ";
  for (i = 0; i < vertex_num_; ++i) { // For loop is necessary for a disconnected graph.
    if (!visited[i]) {
      dfs(i, visited);
    }
  }
  cout << endl;
}

void ListUdg::BFS() const {
  int head = 0;
  int rear = 0;
  size_t queue[MAX];
  bool visited[MAX];
  size_t i, j;
  ENode* node;
  for (i = 0; i < vertex_num_; ++i) {
    visited[i] = false;
  }
  cout << "BFS: ";
  for (i = 0; i < vertex_num_; ++i) { // For loop is necessary for a disconnected graph.
    if (!visited[i]) {
      visited[i] = true;
      cout << vertexes_[i].data << ", ";
      queue[rear++] = i;
    }
    while (head != rear) {
      j = queue[head++];
      node = vertexes_[j].first_edge;
      while (node != nullptr) {
        size_t k = node->vertex_index;
        if (!visited[k]) {
          visited[k] = true;
          cout << vertexes_[k].data << ", ";
          queue[rear++] = k;
        }
        node = node->next_edge;
      }
    }
  }
  cout << endl;
}

void ListUdg::Print() const {
  ENode* node;
  cout << "List Graph:" << endl;
  for (size_t i = 0; i < vertex_num_; ++i) {
    cout << i << "(" << vertexes_[i].data << "): ";
    node = vertexes_[i].first_edge;
    while (node != nullptr) {
      cout << node->vertex_index << "("
           << vertexes_[node->vertex_index].data << ")";
      node = node->next_edge;
    }
    cout << endl;
  }
}

EData* ListUdg::get_edges() const {
  int index = 0;
  ENode* node;
  EData* edges;

  edges = new EData[edge_num_];
  for (size_t i = 0; i < vertex_num_; ++i) {
    node = vertexes_[i].first_edge;
    while (node != nullptr) {
      if (node->vertex_index > i) {
        edges[index].start = vertexes_[i].data;
        edges[index].end = vertexes_[node->vertex_index].data;
        edges[index].weight = node->weight;
        index++;
      }
      node = node->next_edge;
    }
  }
  return edges;
}

// Selection sort
void ListUdg::sort_edges(EData* edges, size_t elen) const {
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

size_t ListUdg::get_end(size_t vends[], size_t i) const {
  while (vends[i] != 0) {
    i = vends[i];
  }
  return i;
}

void ListUdg::Kruskal() const {
  int length;
  EData* edges;  // All edges of the graph
  EData rets[MAX];  // The edges of the kruskal spanning tree

  edges = get_edges();
  sort_edges(edges, edge_num_);

  size_t i;
  size_t index = 0;
  size_t vends[MAX] = {0};
  for (i = 0; i < edge_num_; ++i) {
    size_t p1 = get_position(edges[i].start);
    size_t p2 = get_position(edges[i].end);
    if (p1 == MAX || p2 == MAX) continue;

    size_t m = get_end(vends, p1);
    size_t n = get_end(vends, p2);
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

int ListUdg::get_weight(size_t start, size_t end) const {
  ENode* node;
  if (start == end) return 0;
  node = vertexes_[start].first_edge;
  while (node != nullptr) {
    if (end == node->vertex_index) {
      return node->weight;
    }
    node = node->next_edge;
  }
  return INF;
}

void ListUdg::Prim(size_t start) const {
  char prims[MAX];
  int weights[MAX];

  size_t index = 0;
  prims[index++] = vertexes_[start].data;

  /* Initialize the weight of edges that connect each vertex with spanning
   * tree which only contains vertex start.
   */
  size_t i, j, k;
  int minimum, tmp;
  for (i = 0; i < vertex_num_; ++i) {
    weights[i] = get_weight(start, i);
  }

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
    prims[index++] = vertexes_[k].data;
    weights[k] = 0;

    /* Update the weight of edges that connect each vertex with spanning
     * tree which adds a new vertex k.
     */
    for (j = 0; j < vertex_num_; ++j) {
      tmp = get_weight(k, j);
      if (weights[j] != 0 && tmp < weights[j]) {
        weights[j] = tmp;
      }
    }
  }

  int sum = 0;
  for (i = 1; i < index; ++i) {
    minimum = INF;
    size_t n = get_position(prims[i]);
    for (j = 0; j < i; ++j) {
      size_t m = get_position(prims[j]);
      tmp = get_weight(m, n);
      if (tmp < minimum) {
        minimum = tmp;
      }
    }
    sum += minimum;
  }

  cout << "Prim(" << vertexes_[start].data << ") = " << sum << ": ";
  for (i = 0; i < index; ++i) {
    cout << prims[i] << ", ";
  }
  cout << endl;
}

void ListUdg::Dijkstra(size_t source, size_t previous[], int distance[]) {
  size_t i, j;
  int tmp;
  bool flag[MAX];

  // Initialize the distance between vertex source and each vertex.
  for (i = 0; i < vertex_num_; ++i) {
    flag[i] = false;  // Distance between vertex i and source has not been found.
    distance[i] = get_weight(source, i);
    if (distance[i] != INF) {
      previous[i] = source;  // Denote the previous vertex of vertex i.
    }
  }
  // Add vertex source and mark it as finished.
  flag[source] = true;
  previous[source] = MAX;
  size_t count = 1;
  size_t k = 0;
  // Add vertex k and mark it as finished.
  while (count < vertex_num_) {
    int minimum = INF;
    for (j = 0; j < vertex_num_; ++j) {
      if (!flag[j] && distance[j] < minimum) {
        minimum = distance[j];
        k = j;
      }
    }
    flag[k] = true;
    count++;
    // Update the distance between vertex source and remaining vertexes.
    for (j = 0; j < vertex_num_; ++j) {
      tmp = get_weight(k, j);
      tmp = (tmp == INF ? INF : (minimum + tmp));
      if (!flag[j] && tmp < distance[j]) {
        distance[j] = tmp;
        previous[j] = k;
      }
    }
  }

  cout << "Dijkstra(" << vertexes_[source].data << "): " << endl;
  for (i = 0; i < vertex_num_; ++i) {
    cout << "  shortest(" << vertexes_[source].data << ", "
         << vertexes_[i].data << ") = " << distance[i] << endl;
  }
}

void ListUdg::Floyd(size_t path[][MAX], int distance[][MAX]) {
  size_t i, j, k;

  for (i = 0; i < vertex_num_; ++i) {
    for (j = 0; j < vertex_num_; ++j) {
      distance[i][j] = get_weight(i, j);
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
    cout << setw(4) << vertexes_[i].data;
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
  EData* edges[] = {
    new EData('A', 'B', 12), new EData('A', 'F', 16), new EData('A', 'G', 14),
    new EData('B', 'C', 10), new EData('B', 'F', 7), new EData('C', 'D', 3),
    new EData('C', 'E', 5), new EData('C', 'F', 6), new EData('D', 'E', 4),
    new EData('E', 'F', 2), new EData('E', 'G', 8), new EData('F', 'G', 9),
  };
  size_t vlen = sizeof(vertexes) / sizeof(vertexes[0]);
  size_t elen = sizeof(edges) / sizeof(edges[0]);
  ListUdg* pUdg;
  // pUdg = new ListUdg();  // Manually input
  pUdg = new ListUdg(vertexes, vlen, edges, elen);
  pUdg->DFS();
  pUdg->BFS();
  pUdg->Print();
  pUdg->Kruskal();
  pUdg->Prim(0);

  cout << "## Test Dijkstra algorithm:" << endl;
  size_t prev[MAX] = {0};
  int dist[MAX] = {0};
  size_t vs = 3;
  size_t vt = 5;
  pUdg->Dijkstra(vs, prev, dist);
  cout << "Previous vertex:" << endl;
  for (int i = 0; i < 20; ++i) {
    cout << prev[i] << ", ";
  }
  cout << endl;
  cout << "Path between vertex " << vertexes[vt]
       << " and " << vertexes[vs] << ": ";
  do {
    cout << vertexes[vt] << "<-";
    vt = prev[vt];
  } while (vt != vs);
  cout << vertexes[vs] << endl;

  cout << "## Test Floyd algorithm:" << endl;
  size_t path[MAX][MAX] = {0};
  int floyd_distance[MAX][MAX] = {0};
  pUdg->Floyd(path, floyd_distance);

  cout << "Floyd path:" << endl;
  for (size_t i = 0; i < vlen; ++i) {
    cout << setw(4) << vertexes[i];
  }
  cout << endl;
  cout << "   -------------------------" << endl;
  for (size_t i = 0; i < vlen; ++i) {
    for (size_t j = 0; j < vlen; ++j) {
      cout << setw(4) << vertexes[path[i][j]];
    }
    cout << endl;
  }
  vs = 0;
  vt = 3;
  size_t k = path[vs][vt];
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
