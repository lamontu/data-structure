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
    for (size_t src = 0; src < vertex_num; ++src) {
      for (size_t j = 0; j < adjacency[src].size(); ++j) {
        size_t dest = adjacency[src][j];
        inDegree[dest]++;
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

  void topoSortByDFS() {
    vector<vector<size_t> > inverseAdjacency(vertex_num);
    for (size_t src = 0; src < vertex_num; ++src) {
      for (size_t j = 0; j < adjacency[src].size(); ++j) {
        size_t dest = adjacency[src][j];
        inverseAdjacency[dest].push_back(src);
      }
    }

    vector<bool> visited(vertex_num);
    for (size_t i = 0; i < vertex_num; ++i) {
      if (!visited[i]) {
        visited[i] = true;
        dfs(i, inverseAdjacency, visited);
      }
    }
  }

private:
  void dfs(size_t vertex, vector<vector<size_t> > &inverseAdj, vector<bool> & vertexVisited) {
    for (size_t i = 0; i < inverseAdj[vertex].size(); ++i) {
      size_t src = inverseAdj[vertex][i];
      if (vertexVisited[src]) {
        continue;
      }
      vertexVisited[src] = true;
      dfs(src, inverseAdj, vertexVisited);
    }
    cout << "->" << vertex;
  }

};

int main() {
  size_t VertexNum = 8;
  vector<Edge> edges = {
		{0, 6}, {1, 2}, {1, 4}, {1, 6}, {3, 0}, {3, 4}, {5, 1}, {7, 0}, {7, 1}
	};
  Graph g(VertexNum);
  for (auto &edge: edges) {
    g.addEdge(edge);
  }
  cout << "topoSortByKahn: " << endl;
  bool ret1 = g.topoSortByKahn();
  cout << (ret1 ? "Succeeded" : "Failed") << endl;
  cout << "topoSortByDFS: " << endl;
  g.topoSortByDFS();
  cout << endl;

  return 0;
}
