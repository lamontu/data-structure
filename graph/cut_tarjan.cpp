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

const int MaxVertexNum = 64;
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
    size_t vertex_index;  // the end vertex index of this arc
    ArcNode* next_arc;
  };

  struct VNode {
    string data;
    ArcNode* first_arc;
  };

  size_t vertex_num_;
  size_t arc_num_;
  VNode vertexes_[MaxVertexNum];

 public:
  ALGraph();
  // ~ALGraph() {  }
  void DetectCutPoint();
  void DetectCutEdge();

 private:
  void tarjan_dfs(size_t v0, int fa);
};

/*  Sample undirected graph
 *    0  -------  1  -------  3
 *    |             ╲         |
 *    |                ╲      |
 *    |                   ╲   |
 *    2           5  -------  4
 */
ALGraph::ALGraph() {
  vector<string> vertex_data{"0", "1", "2", "3", "4", "5"};
  vertex_num_ = vertex_data.size();
  for (size_t i = 0; i < vertex_num_; ++i) {
    vertexes_[i].data = vertex_data[i];
    vertexes_[i].first_arc = nullptr;
  }

  vector<size_t> starts{0, 0, 1, 1, 3, 4};
  vector<size_t>   ends{1, 2, 3, 4, 4, 5};
  arc_num_ = starts.size();
  for (size_t k = 0; k < arc_num_; ++k) {
    size_t i = starts[k];
    size_t j = ends[k];
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

void ALGraph::tarjan_dfs(size_t v0, int father) {
  ArcNode* p;
  Parent[v0] = father;
  VisitOrder[v0] = LowPoint[v0] = ++timer;
  for (p = vertexes_[v0].first_arc; p != nullptr; p = p->next_arc) {
    size_t w = p->vertex_index;
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

  for (size_t v = 1; v < vertex_num_; ++v) {
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

  cout << "DetectCutPoint:";
  for (size_t i = 0; i < vertex_num_; ++i) {
    if (IsCutPoint[i]) {
      cout << i << ", ";
      CutPoints[i] = vertexes_[i].data;
    }
  }
  cout << endl;
}

void ALGraph::DetectCutEdge() {
  cout << "DetectCutEdge: ";
  for (size_t v = 0; v < vertex_num_; ++v) {
    int u = Parent[v];
    if (u != -1 && LowPoint[v] > VisitOrder[u]) {
      cout << "(" << u << ", " << v << ")" << ", ";
      CutEdges.push_back(pair<string, string>(
                         vertexes_[u].data, vertexes_[v].data));
    }
  }
  cout << endl;
}

int main() {
  ALGraph* pALG = new ALGraph();
  pALG->DetectCutPoint();
  pALG->DetectCutEdge();

  cout << "Cut points: ";
  for (int i = 0; i < 20; ++i) {
    if (IsCutPoint[i]) {
      cout << CutPoints[i] << "(" << BlockNum[i] << ")" << ", ";
    }
  }
  cout << endl;

  cout << "Cut edges: ";
  for (auto it = CutEdges.begin(); it != CutEdges.end(); ++it) {
    cout << "(" << (*it).first << ", " << (*it).second << "), ";
  }
  cout << endl;

  return 0;
}
