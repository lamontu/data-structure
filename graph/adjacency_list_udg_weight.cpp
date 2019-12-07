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
  char start;
  char end;
  int weight;

  EData() {  }
  EData(char s, char e, int w) : start(s), end(e), weight(w) {  }
};

class ListUdg {
 private:
  struct ENode {
    int vertex_index;  // The vertex this edge points to
    int weight;
    ENode* next_edge;
  };

  struct VNode {
    char data;
    ENode* first_edge;  // Store all jointed edges in a singly linked list
  };

  int vertex_num_;
  int edge_num_;
  VNode vertexes_[MAX];

 public:
  ListUdg();
  ListUdg(char vertexes[], int vlen, EData* edges[], int elen);
  // ~ListUdg() {  }
  void DFS() const;
  void BFS() const;
  void Print() const;
  void Kruskal() const;
  void Prim(int start) const;
  void Dijkstra(int source, int previous[], int distance[]);
  void Floyd(int path[MAX][MAX], int distance[MAX][MAX]);

 private:
  char read_char();
  int get_position(char ch) const;
  void link_last(ENode* list, ENode* node) const;

  void dfs(int i, int* visited) const;

  EData* get_edges() const;
  void sort_edges(EData* edges, int elen) const;
  int get_end(int vends[], int i) const;

  int get_weight(int start, int end) const;
};

char ListUdg::read_char() {
  char ch;
  do {
    cin >> ch;
  } while (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')));
  return ch;
}

int ListUdg::get_position(char ch) const {
  int i;
  for (i = 0; i < vertex_num_; ++i) {
    if(vertexes_[i].data == ch) return i;
  }
  return -1;
}

void ListUdg::link_last(ENode* list, ENode* node) const {
  ENode* p = list;
  while (p->next_edge) {
    p = p->next_edge;
  }
  p->next_edge = node;
}

ListUdg::ListUdg() {
  char c1, c2;
  int weight;
  int v, e;
  int i, p1, p2;
  ENode *node1, *node2;

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
    cout << "vertex(" << i <<"): ";
    vertexes_[i].data = read_char();
    vertexes_[i].first_edge = nullptr;
  }
  for (i = 0; i < edge_num_; ++i) {
    cout << "edge(" << i << "): ";
    c1 = read_char();
    c2 = read_char();
    cin >> weight;
    p1 = get_position(c1);
    p2 = get_position(c2);

    node1 = new ENode();
    node1->vertex_index = p2;
    node1->weight = weight;
    if (nullptr == vertexes_[p1].first_edge) {
      vertexes_[p1].first_edge = node1;
    } else {
      link_last(vertexes_[p1].first_edge, node1);
    }

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

ListUdg::ListUdg(char vertexes[], int vlen, EData* edges[], int elen) {
  char c1, c2;
  int weight;
  int i, p1, p2;
  ENode *node1, *node2;
  vertex_num_ = vlen;
  edge_num_ = elen;
  for (i = 0; i < vertex_num_; ++i) {
    vertexes_[i].data = vertexes[i];
    vertexes_[i].first_edge = nullptr;
  }
  for (i = 0; i < edge_num_; ++i) {
    c1 = edges[i]->start;
    c2 = edges[i]->end;
    weight = edges[i]->weight;
    p1 = get_position(c1);
    p2 = get_position(c2);

    node1 = new ENode();
    node1->vertex_index = p2;
    node1->weight = weight;
    if (nullptr == vertexes_[p1].first_edge) {
      vertexes_[p1].first_edge = node1;
    } else {
      link_last(vertexes_[p1].first_edge, node1);
    }

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

void ListUdg::dfs(int i, int* visited) const {
  ENode* node;
  visited[i] = 1;
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
  int i;
  int visited[MAX];
  for (i = 0; i < vertex_num_; ++i) {
    visited[i] = 0;
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
  int queue[MAX];
  int visited[MAX];
  int i, j, k;
  ENode* node;
  for (i = 0; i < vertex_num_; ++i) {
    visited[i] = 0;
  }
  cout << "BFS: ";
  for (i = 0; i < vertex_num_; ++i) { // For loop is necessary for a disconnected graph.
    if (!visited[i]) {
      visited[i] = 1;
      cout << vertexes_[i].data << ", ";
      queue[rear++] = i;
    }
    while (head != rear) {
      j = queue[head++];
      node = vertexes_[j].first_edge;
      while (node != nullptr) {
        k = node->vertex_index;
        if (!visited[k]) {
          visited[k] = 1;
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
  int i, j;
  ENode* node;
  cout << "List Graph:" << endl;
  for (i = 0; i < vertex_num_; ++i) {
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
  int i, j;
  int index = 0;
  ENode* node;
  EData* edges;

  edges = new EData[edge_num_];
  for (i = 0; i < vertex_num_; ++i) {
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
void ListUdg::sort_edges(EData* edges, int elen) const {
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

int ListUdg::get_end(int vends[], int i) const {
  while (vends[i] != 0) {
    i = vends[i];
  }
  return i;
}

void ListUdg::Kruskal() const {
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

int ListUdg::get_weight(int start, int end) const {
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

void ListUdg::Prim(int start) const {
  int min, i, j, k, m, n, tmp, sum;
  int index = 0;
  char prims[MAX];
  int weights[MAX];

  prims[index++] = vertexes_[start].data;

  /* Initialize the weight of edges that connect each vertex with spanning
   * tree which only contains vertex start.
   */
  for (i = 0; i < vertex_num_; ++i) {
    weights[i] = get_weight(start, i);
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

  sum = 0;
  for (i = 1; i < index; ++i) {
    min = INF;
    n = get_position(prims[i]);
    for (j = 0; j < i; ++j) {
      m = get_position(prims[j]);
      tmp = get_weight(m, n);
      if (tmp < min) {
        min = tmp;
      }
    }
    sum += min;
  }

  cout << "Prim(" << vertexes_[start].data << ") = " << sum << ": ";
  for (i = 0; i < index; ++i) {
    cout << prims[i] << ", ";
  }
  cout << endl;
}

void ListUdg::Dijkstra(int source, int previous[], int distance[]) {
  int i, j, k;
  int min, tmp;
  int flag[MAX];

  // Initialize the distance between vertex source and each vertex.
  for (i = 0; i < vertex_num_; ++i) {
    flag[i] = 0;  // Distance between vertex i and source has not been found.
    distance[i] = get_weight(source, i);
    if (distance[i] != INF) {
      previous[i] = source;  // Denote the previous vertex of vertex i.
    }
  }
  // Add vertex source and mark it as finished.
  flag[source] = 1;
  previous[source] = -1;

  // Add vertex k and mark it as finished.
  for (i = 1; i < vertex_num_; ++i) {
    min = INF;
    for (j = 0; j < vertex_num_; ++j) {
      if (flag[j] == 0 && distance[j] < min) {
        min = distance[j];
        k = j;
      }
    }
    flag[k] = 1;

    // Update the distance between vertex source and remaining vertexes.
    for (j = 0; j < vertex_num_; ++j) {
      tmp = get_weight(k, j);
      tmp = (tmp == INF ? INF : (min + tmp));
      if (flag[j] == 0 && tmp < distance[j]) {
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

void ListUdg::Floyd(int path[][MAX], int distance[][MAX]) {
  int i, j, k;
  int tmp;

  for (i = 0; i < vertex_num_; ++i) {
    for (j = 0; j < vertex_num_; ++j) {
      distance[i][j] = get_weight(i, j);
      path[i][j] = j;  // Vertex j is on the path from vertex i to j.
    }
  }

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

int main(int argc, char* argv[]) {
  char vertexes[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  EData* edges[] = {
    new EData('A', 'B', 12), new EData('A', 'F', 16), new EData('A', 'G', 14),
    new EData('B', 'C', 10), new EData('B', 'F', 7), new EData('C', 'D', 3),
    new EData('C', 'E', 5), new EData('C', 'F', 6), new EData('D', 'E', 4),
    new EData('E', 'F', 2), new EData('E', 'G', 8), new EData('F', 'G', 9),
  };
  int vlen = sizeof(vertexes) / sizeof(vertexes[0]);
  int elen = sizeof(edges) / sizeof(edges[0]);
  ListUdg* pUdg;
  // pUdg = new ListUdg();  // Manually input
  pUdg = new ListUdg(vertexes, vlen, edges, elen);
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
  do {
    cout << vertexes[vt] << "<-";
    vt = prev[vt];
  } while (vt != vs);
  cout << vertexes[vs] << endl;

  cout << "## Test Floyd algorithm:" << endl;
  int path[MAX][MAX] = {0};
  int floyd_distance[MAX][MAX] = {0};
  pUdg->Floyd(path, floyd_distance);

  cout << "Floyd path:" << endl;
  for (int i = 0; i < vlen; ++i) {
    cout << setw(4) << vertexes[i];
  }
  cout << endl;
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
