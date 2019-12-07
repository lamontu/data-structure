/* ford_fulkerson.cpp */

#include <iostream>
#include <vector>

using namespace std;

const int INF = ~(0x1u << 31);
const int VertexNum = 100;

/* Store the information of an arc.
 * Each arc has a corresponding vertex as arc tail.
 */
struct Node {
  int head;  // Denote arc head index.
  int capacity;  // Denote capacity of an arc.

  // Denote the index of this arc's reverse arc in its tail(vertex head).
  int reverse;

  Node(int to, int cap, int rev) : head(to), capacity(cap), reverse(rev) {  }
};

// Each vertex, or arc tail, has a related vector.
vector<Node> v[VertexNum];

bool used[VertexNum];

/* Each edge is related to a forward arc and a reverse arc. The direction of
 * an edge is represented by the arc with non-zero initial capacity.
 */
void add_node(int from, int to, int cap) {
  v[from].push_back( Node(to, cap, v[to].size()) );
  v[to].push_back( Node(from, 0, v[from].size() - 1) );
}

/* The forward arc's capacity is the maximum flow the current flow can increase.
 * The reverse arc's capacity is the maximum flow the current flow can decrease.
 */
int dfs(int s, int t, int f) {
  if (s == t) return f;
  used[s] = true;
  for (int i = 0; i < v[s].size(); ++i) {
    Node& tmp = v[s][i];
    if (used[tmp.head] == false && tmp.capacity > 0) {
      int d = dfs(tmp.head, t, min(f, tmp.capacity));
      if (d > 0) {

        tmp.capacity -= d;
        v[tmp.head][tmp.reverse].capacity += d;
        return d;
      }
    }
  }
  return 0;
}

int MaxFlow(int s, int t) {
  int flow = 0;
  for (;;) {
    memset(used, false, sizeof(used));
    int f = dfs(s, t, INF);
    if (f == 0) {
      return flow;
    }
    flow += f;
  }
}

int main(int argc, char* argv[]) {
  int arc_num, vertex_num;
  cout << "arc number: "; cin >> arc_num;
  cout << "vertex number: "; cin >> vertex_num;

  if (vertex_num < 1 || arc_num < 0
      || (arc_num > (vertex_num * (vertex_num - 1)))) {
    cout << "Input error: invalid parameters!" << endl;
    exit(1);
  }

  memset(v, 0, sizeof(v));
  for (int i = 0; i < arc_num; ++i) {
    int tail, head, capacity;
    cout << "arc tail index: "; cin >> tail;
    cout << "arc head index: "; cin >> head;
    cout << "arc capacity: "; cin >> capacity;
    add_node(tail, head, capacity);
  }
  // cout << "Maximum flow: " << MaxFlow(1, vertex_num) << endl;
  cout << "Maximum flow: " << MaxFlow(0, vertex_num - 1) << endl;
  return 0;
}
