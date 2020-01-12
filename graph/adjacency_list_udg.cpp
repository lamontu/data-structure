/* adjacency_list_udg.cpp
 * Adjacency List of Undirected Graph
 */

#include <iostream>

using namespace std;

const int MAX = 100;

class ListUdg {
 private:
  struct ENode {
    ENode* next_edge;
    size_t vertex_index;  // The vertex this edge points to
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
  ListUdg(char vertexes[], size_t vlen, char edges[][2], size_t elen);
  // ~ListUdg() {  }
  void DFS() const;
  void BFS() const;
  void Print() const;

 private:
  char read_char();
  size_t get_position(char ch) const;
  void link_last(ENode* list, ENode* node) const;
  void dfs(size_t i, bool* visited) const;
};

char ListUdg::read_char() {
  char ch;
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

  cout << "Input vertex number:";
  cin >> vertex_num_;
  cout << "Input edge number:";
  cin >> edge_num_;
  if (vertex_num_ < 1 || edge_num_ > vertex_num_ * (vertex_num_ - 1)) {
    cout << "Input error: invalid parameters!" << endl;
    return;
  }

  size_t i = 0;
  for (i = 0; i < vertex_num_; ++i) {
    cout << "vertex(" << i <<"): ";
    vertexes_[i].data = read_char();
    vertexes_[i].first_edge = nullptr;
  }

  for (i = 0; i < edge_num_; ++i) {
    cout << "edge(" << i << "): ";
    char c1 = read_char();
    char c2 = read_char();
    size_t p1 = get_position(c1);
    size_t p2 = get_position(c2);
    if (p1 == MAX || p2 == MAX) continue;

    node1 = new ENode();
    node1->vertex_index = p2;
    if (nullptr == vertexes_[p1].first_edge) {
      vertexes_[p1].first_edge = node1;
    } else {
      link_last(vertexes_[p1].first_edge, node1);
    }

    /* This is different from directed graph. */
    node2 = new ENode();
    node2->vertex_index = p1;
    if (nullptr == vertexes_[p2].first_edge) {
      vertexes_[p2].first_edge = node2;
    } else {
      link_last(vertexes_[p2].first_edge, node2);
    }
  }
}

ListUdg::ListUdg(char vertexes[], size_t vlen, char edges[][2], size_t elen) {
  ENode *node1, *node2;
  vertex_num_ = vlen;
  edge_num_ = elen;
  size_t i;
  for (i = 0; i < vertex_num_; ++i) {
    vertexes_[i].data = vertexes[i];
    vertexes_[i].first_edge = nullptr;
  }

  for (i = 0; i < edge_num_; ++i) {
    char c1 = edges[i][0];
    char c2 = edges[i][1];
    size_t p1 = get_position(c1);
    size_t p2 = get_position(c2);
    if (p1 == MAX || p2 == MAX) continue;

    node1 = new ENode();
    node1->vertex_index = p2;
    if (nullptr == vertexes_[p1].first_edge) {
      vertexes_[p1].first_edge = node1;
    } else {
      link_last(vertexes_[p1].first_edge, node1);
    }

    /* This is different from directed graph. */
    node2 = new ENode();
    node2->vertex_index = p1;
    if (nullptr == vertexes_[p2].first_edge) {
      vertexes_[p2].first_edge = node2;
    } else {
      link_last(vertexes_[p2].first_edge, node2);
    }
  }
}

void ListUdg::dfs(size_t i, bool* visited) const {
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
  int visited[MAX];
  size_t i, j, k;
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
        k = node->vertex_index;
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
  for (size_t i= 0; i < vertex_num_; ++i) {
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

int main() {
  char vertexes[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  char edges[][2] = {
    {'A', 'C'}, {'A', 'D'}, {'A', 'F'}, {'B', 'C'},
    {'C', 'D'}, {'E', 'G'}, {'F', 'G'}
  };
  size_t vlen = sizeof(vertexes) / sizeof(vertexes[0]);
  size_t elen = sizeof(edges) / sizeof(edges[0]);
  ListUdg* pUdg;
  // pUdg = new ListUdg();  // Manually input
  pUdg = new ListUdg(vertexes, vlen, edges, elen);
  pUdg->DFS();
  pUdg->BFS();
  pUdg->Print();

  delete pUdg;
  pUdg = nullptr;

  return 0;
}
