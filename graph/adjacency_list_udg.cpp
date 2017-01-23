/* adjacency_list_udg.cpp
 * Adjacency List of Undirected Graph
 */

#include <iostream>

using namespace std;

const int MAX = 100;

class ListUdg {
 private:
  struct ENode {
    int vertex_index;
    ENode* next_edge;
  };

  struct VNode {
    char data;
    ENode* first_edge;
  };

  int vertex_num_;
  int edge_num_;
  VNode vertexes_[MAX];

 public:
  ListUdg();
  ListUdg(char vertexes[], int vlen, char edges[][2], int elen);
  ~ListUdg();
  void Print();

 private:
  char read_char();
  int get_position(char ch);
  void link_last(ENode* list, ENode* node);
};

ListUdg::ListUdg() {
  char c1, c2;
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
    p1 = get_position(c1);
    p2 = get_position(c2);
    node1 = new ENode();
    node1->vertex_index = p2;
    if (nullptr == vertexes_[p1].first_edge) {
      vertexes_[p1].first_edge = node1;
    } else {
      link_last(vertexes_[p1].first_edge, node1);
    }
    node2 = new ENode();
    node2->vertex_index = p1;
    if (nullptr == vertexes_[p2].first_edge) {
      vertexes_[p2].first_edge = node2;
    } else {
      link_last(vertexes_[p2].first_edge, node2);
    }
  }
}

ListUdg::ListUdg(char vertexes[], int vlen, char edges[][2], int elen) {
  char c1, c2;
  int i, p1, p2;
  ENode *node1, *node2;
  vertex_num_ = vlen;
  edge_num_ = elen;
  for (i = 0; i < vertex_num_; ++i) {
    vertexes_[i].data = vertexes[i];
    vertexes_[i].first_edge = nullptr;
  }
  for (i = 0; i < edge_num_; ++i) {
    c1 = edges[i][0];
    c2 = edges[i][1];
    p1 = get_position(c1);
    p2 = get_position(c2);
    node1 = new ENode();
    node1->vertex_index = p2;
    if (nullptr == vertexes_[p1].first_edge) {
      vertexes_[p1].first_edge = node1;
    } else {
      link_last(vertexes_[p1].first_edge, node1);
    }
    node2 = new ENode();
    node2->vertex_index = p1;
    if (nullptr == vertexes_[p2].first_edge) {
      vertexes_[p2].first_edge = node2;
    } else {
      link_last(vertexes_[p2].first_edge, node2);
    }
  }
}

void ListUdg::link_last(ENode* list, ENode* node) {
  ENode* p = list;
  while (p->next_edge) {
    p = p->next_edge;
  }
  p->next_edge = node;
}

void ListUdg::Print() {
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

char ListUdg::read_char() {
  char ch;
  do {
    cin >> ch;
  } while (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')));
  return ch;
}

int ListUdg::get_position(char ch) {
  int i;
  for (i = 0; i < vertex_num_; ++i) {
    if(vertexes_[i].data == ch) return i;
  }
  return -1;
}


int main(int argc, char* argv[]) {
  char vertexes[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  char edges[][2] = {
    {'A', 'C'}, {'A', 'D'}, {'A', 'F'}, {'B', 'C'},
    {'C', 'D'}, {'E', 'G'}, {'F', 'G'}
  };
  int vlen = sizeof(vertexes) / sizeof(vertexes[0]);
  int elen = sizeof(edges) / sizeof(edges[0]);
  ListUdg* pUdg;
  // pUdg = new ListUdg(vertexes, vlen, edges, elen);
  pUdg = new ListUdg();
  pUdg->Print();

  return 0;
}