/* tarjan_adjacency_list.cpp */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::max;
using std::min;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::pair;

const int MaxVertexNum = 100;
int VisitOrder[MaxVertexNum];
int LowPoint[MaxVertexNum];

int Parent[MaxVertexNum];
bool IsCutPoint[MaxVertexNum];
string CutPoints[MaxVertexNum];
int BlockNum[MaxVertexNum];

vector<pair<string, string>> CutEdges;

int timer = 0;

class ALGraph {
 private:
  struct ArcNode {
    int vertex_index;
    ArcNode* next_arc;
  };

  struct VNode {
    string data;
    ArcNode* first_arc;
  };

  int vertex_num_;
  int arc_num_;
  VNode vertexes_[MaxVertexNum];

 public:
  ALGraph();
  // ~ALGraph() {  }
  void DetectCutPoint();
  void DetectCutEdge();

 private:
  int locate_vertex(string u);
  void tarjan_dfs(int v0, int fa);
};

int ALGraph::locate_vertex(string u) {
  for (int i = 0; i < vertex_num_; ++i) {
    if (vertexes_[i].data == u) {
      return i;
    }
  }
  return -1;
}

ALGraph::ALGraph() {
  string v1, v2;
  int i, j, k;
  cout << "Vertex number: ";
  cin >> vertex_num_;
  cout << "Arc number: ";
  cin >> arc_num_;

  for (i = 0; i < vertex_num_; ++i) {
    cin >> vertexes_[i].data;
    vertexes_[i].first_arc = nullptr;
  }

  for (k = 0; k < arc_num_; ++k) {
    cout << "arc(" << k << "): ";
    cin >> v1 >> v2;
    i = locate_vertex(v1);
    j = locate_vertex(v2);

    ArcNode* arc = new ArcNode();
    arc->vertex_index = j;
    arc->next_arc = vertexes_[i].first_arc;
    vertexes_[i].first_arc = arc;

    arc = new ArcNode();
    arc->vertex_index = i;
    arc->next_arc = vertexes_[j].first_arc;
    vertexes_[j].first_arc = arc;
  }
}

void ALGraph::tarjan_dfs(int v0, int father) {
  ArcNode* p;
  int w;
  Parent[v0] = father;
  VisitOrder[v0] = LowPoint[v0] = ++timer;
  for (p = vertexes_[v0].first_arc; p != nullptr; p = p->next_arc) {
    w = p->vertex_index;
    if (VisitOrder[w] == 0) {
      tarjan_dfs(w, v0);
      LowPoint[v0] = min(LowPoint[v0], LowPoint[w]);
    } else if (w != father) {
      LowPoint[v0] = min(LowPoint[v0], VisitOrder[w]);
    }
  }
}

void ALGraph::DetectCutPoint() {
  memset(BlockNum, 0, sizeof(BlockNum));
  memset(IsCutPoint, false, sizeof(IsCutPoint));
  int root_son = 0;
  tarjan_dfs(0, -1);
  for (int v = 1; v < vertex_num_; ++v) {
    int u = Parent[v];
    if (u == 0) {
      root_son++;
    } else {
      if (LowPoint[v] >= VisitOrder[u]) {
        BlockNum[u]++;
        if (IsCutPoint[u] == false) {
          IsCutPoint[u] = true;
        }
      }
    }
  }
  if (root_son > 1) {
    IsCutPoint[0] = true;
    BlockNum[0] = root_son - 1;
  }

  for (int i = 0; i < vertex_num_; ++i) {
    if (IsCutPoint[i]) {
      cout << i << ", ";
      CutPoints[i] = vertexes_[i].data;
    }
  }
  cout << endl;
}

void ALGraph::DetectCutEdge() {
  for (int v = 0; v < vertex_num_; ++v) {
    int u = Parent[v];
    if (u != -1 && LowPoint[v] > VisitOrder[u]) {
      cout << "(" << u << ", " << v << ")" << ", ";
      CutEdges.push_back(pair<string, string>(
                         vertexes_[u].data, vertexes_[v].data));
    }
  }
  cout << endl;
}

int main(int argc, char* argv[]) {
  ALGraph* pALG = new ALGraph();
  pALG->DetectCutPoint();
  pALG->DetectCutEdge();

  for (int i = 0; i < 20; ++i) {
    if (IsCutPoint[i]) {
      cout << CutPoints[i] << "(" << BlockNum[i] << ")" << ", ";
    }
  }
  cout << endl;

  for (auto it = CutEdges.begin(); it != CutEdges.end(); ++it) {
    cout << "(" << (*it).first << ", " << (*it).second << "), ";
  }
  cout << endl;

  return 0;
}
