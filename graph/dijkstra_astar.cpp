#include <vector>
#include <queue>
#include <functional>
#include <iostream>

using std::vector;
using std::priority_queue;
using std::greater;
using std::cout;
using std::endl;

const int INF = 1024;

struct Edge {
  size_t src; // 边的起始顶点编号
  size_t dest; // 边的终止顶点编号
  int weight; // 权重
  Edge(size_t s, size_t t, int w) : src(s), dest(t), weight(w) { }
};

struct Vertex {
  size_t id; // 顶点编号ID
  int distance; // 从起始顶点到这个顶点的距离, g(i)
  // int f;  // f(i) = g(i) + h(i), h(i): 从这个顶点到终点到距离
  // int x;
  // int y;
  explicit Vertex(size_t vertex = 0, int dist = INF) : id(vertex), distance(dist) {
  }

  friend bool operator < (const Vertex& lhs, const Vertex& rhs) {
    return lhs.distance < rhs.distance;
  }
  friend bool operator > (const Vertex& lhs, const Vertex& rhs) {
    return lhs.distance > rhs.distance;
  }
};

class Graph {  // 有向有权图的邻接表表示
private:
  size_t vertex_num;
  vector<vector<Edge> > adjacency;

public:
  explicit Graph(size_t num) : vertex_num(num), adjacency(vector<vector<Edge> >(num)) { }

  void addEdge(size_t src, size_t dest, int weight, bool undirectd = false) {
    adjacency[src].push_back(Edge(src, dest, weight));
    if (undirectd) {
      adjacency[dest].push_back(Edge(dest, src, weight));
    }
  }

  void dijkstra(size_t s, size_t t) {  // 从顶点s到顶点t的最短路径
    vector<size_t> predecessor(vertex_num);  // 用来还原最短路径
    vector<Vertex> vertexes(vertex_num);
    for (size_t i = 0; i < vertex_num; ++i) {
      vertexes[i] = Vertex(i, INF);
    }
    priority_queue<Vertex, vector<Vertex>, greater<Vertex> > priorityqueue;  // 小顶堆
    vector<bool> inqueue(vertex_num);  // 标记是否进入过队列
    vertexes[s].distance = 0;
    priorityqueue.push(vertexes[s]);
    while (!priorityqueue.empty()) {
      Vertex minVertex= priorityqueue.top();  // 取堆顶元素并删除s
      priorityqueue.pop();
      if (inqueue[minVertex.id]) {
        continue;
      }
      inqueue[minVertex.id] = true;
      if (minVertex.id == t) break;  // 最短路径产生了
      for (size_t i = 0; i < adjacency[minVertex.id].size(); ++i) {
        Edge e = adjacency[minVertex.id][i];  // 取出一条minVetex相连的边
        Vertex nextVertex = vertexes[e.dest];  // minVertex-->nextVertex
        if (minVertex.distance + e.weight < nextVertex.distance) {  // 更新next的dist
          nextVertex.distance = minVertex.distance + e.weight;
          predecessor[nextVertex.id] = minVertex.id;
          priorityqueue.push(nextVertex);
          vertexes[nextVertex.id].distance = nextVertex.distance;
        }
      }
    }
    // 输出最短路径
    cout << "Shortest path: ";
    cout << s;
    print(s, t, predecessor);
    cout << endl;
    cout << "Shortest path length: " << vertexes[t].distance;
    cout << endl;
  }

private:
  void print(size_t s, size_t t, vector<size_t> predecessor) {
    if (s == t) return;
    print(s, predecessor[t], predecessor);
    cout << "->" << t;
  }

};

int main() {
  // size_t V = 9;
  // Graph g(V);
  // g.addEdge(0, 1, 4);
  // g.addEdge(0, 7, 8);
  // g.addEdge(1, 2, 8);
  // g.addEdge(1, 7, 11);
  // g.addEdge(2, 3, 7);
  // g.addEdge(2, 8, 2);
  // g.addEdge(2, 5, 4);
  // g.addEdge(3, 4, 9);
  // g.addEdge(3, 5, 14);
  // g.addEdge(4, 5, 10);
  // g.addEdge(5, 6, 2);
  // g.addEdge(6, 7, 1);
  // g.addEdge(6, 8, 6);
  // g.addEdge(7, 8, 7);
  // g.dijkstra(0, 8);

  size_t V = 5;
  Graph g(V);
  g.addEdge(0,1,7, true);
  g.addEdge(0,2,3, true);
  g.addEdge(1,2,1, true);
  g.addEdge(1,3,2, true);
  g.addEdge(1,4,6, true);
  g.addEdge(2,3,2, true);
  g.addEdge(3,4,4, true);
  g.dijkstra(0, 4);

  return 0;
}
