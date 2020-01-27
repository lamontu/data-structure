#include <vector>
#include <queue>
#include <iostream>

using std::vector;
using std::queue;
using std::cout;
using std::endl;

struct Edge {
  size_t src;
  size_t dest;
};

class Graph {
private:
  size_t vertex_num;
  vector<vector<size_t> > adjacency;

public:
  explicit Graph(size_t num) : vertex_num(num), adjacency(vector<vector<size_t> >(num)) { }

  void addEdge(const Edge& edge) {
    adjacency[edge.src].push_back(edge.dest);
  }

  // Kahn algorithm: an g
  bool topoSortByKahn() {
    vector<size_t> inDegree(vertex_num);
    for (size_t i = 0; i < vertex_num; ++i) {
      for (size_t j = 0; j < adjacency[i].size(); ++j) {
        size_t vertex = adjacency[i][j];
        inDegree[vertex]++;
      }
    }

    queue<size_t> verticesQueue;
    for (size_t i = 0; i < vertex_num; ++i) {
      if (inDegree[i] == 0) {
        verticesQueue.push(i);
      }
    }

    while (!verticesQueue.empty()) {
      size_t i = verticesQueue.front();
      verticesQueue.pop();
      cout << "->" << i;
      for (size_t j = 0; j < adjacency[i].size(); ++j) {
        size_t k = adjacency[i][j];
        inDegree[k]--;
        if (inDegree[k] == 0) {
          verticesQueue.push(k);
        }
      }
    }
    cout << endl;

    // Check if the graph is a directed acyclic graph(DAG)
    for (size_t i = 0; i < vertex_num; ++i) {
      if (inDegree[i]) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  size_t VertexNum = 8;
  vector<Edge> edges = {
		{0, 6}, {1, 2}, {1, 4}, {1, 6}, {3, 0}, {3, 4}, {5, 1}, {7, 0}, {7, 1}
	};
  Graph g = Graph(VertexNum);
  for (auto &edge: edges) {
    g.addEdge(edge);
  }
  bool ret = g.topoSortByKahn();
  cout << (ret ? "Succeeded" : "Failed") << endl;
  return 0;
}
