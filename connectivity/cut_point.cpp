/* cut_point.cpp */

#include <iostream>
#include <string>

using namespace std;

const int MaxVertexNum = 100;

// Visited[i]: The visit sequence of vertex i, range from 1 to vertex_num_.
int Visited[MaxVertexNum];

/* LowPoint[i]: The least Visited[k] of vertex k on the path starting from
 * vertex i using no more than one back edge.
 *
 * LowPoint[v] = minimum(Visited[v], LowPoint[w], Visited[k])
 * Vertex w is the child of vertex v,
 * Vertex k is vertex v or ancestor of vertex v vertex with least Visited[k]
 * tracing back through one back edge from vertex v or the child of vertex v.
 */
int LowPoint[MaxVertexNum];

int Count;
string CutPoint[MaxVertexNum];
// The number of increased connected block after a vertex is removed.
int CutBlock[MaxVertexNum];  

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
  void DetectCutVertex();

 private:
  int locate_vertex(string u);
  void find_cut_vertex(int v0);
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

void ALGraph::find_cut_vertex(int v0) {
  int min, w;
  ArcNode* p;
  Visited[v0] = min = ++Count;
  for (p = vertexes_[v0].first_arc; p; p = p->next_arc) {
    w = p->vertex_index;
    if (Visited[w] == 0) {
      find_cut_vertex(w);
      if (LowPoint[w] < min) {
        min = LowPoint[w];
      }
      if (LowPoint[w] >= Visited[v0]) {
        cout << vertexes_[v0].data << ", ";
        CutBlock[v0]++;
        if (CutBlock[v0] == 1) {
          CutPoint[v0] = vertexes_[v0].data;
        }
      }
    } else if (Visited[w] < min) {
      min = Visited[w];
    }
  }
  LowPoint[v0] = min;
}

void ALGraph::DetectCutVertex() {
  int i, v;
  ArcNode* p;
  for (i = 0; i < vertex_num_; ++i) {
    Visited[i] = 0;
    CutBlock[i] = 0;
  }

  Visited[0] = 1;
  Count = 1;

  p = vertexes_[0].first_arc;
  v = p->vertex_index;
  find_cut_vertex(v);
  if (Count < vertex_num_) {
    cout << vertexes_[0].data << ", ";
    CutBlock[0]++;
    CutPoint[0] = vertexes_[0].data;
    while (p->next_arc) {
      p = p->next_arc;
      v = p->vertex_index;
      if (Visited[v] == 0) {
        find_cut_vertex(v);
      }
    }
  }
}

int main(int argc, char* argv[]) {
  ALGraph* pALG = new ALGraph();
  pALG->DetectCutVertex();
  cout << endl;
  for (int i = 0; i < 20; ++i) {
    if (CutBlock[i] > 0) {
      cout << CutPoint[i] << "(" << CutBlock[i] << ")" << ", ";
    }
  }
  cout << endl;

  return 0;
}
