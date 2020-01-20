#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::queue;
using std::min;

const int VertexNum = 6;
const int INF = ~(0x1u << 31);

static int flow[VertexNum];  // Current input flow of each vertex
static int pre[VertexNum];  // The previous vertex in the path

/* The capacity of forward arc is the maximum flow that current flow can
 * increase. The capacity of reverse arc is the maximum flow that current
 * flow can decrease.
 */
static int capacity[VertexNum][VertexNum] =
  { {0, 16, 13, 0,  0,  0 },
    {0, 0,  10, 12, 0,  0 },
    {0, 4,  0,  0,  14, 0 },
    {0, 0,  9,  0,  0,  20},
    {0, 0,  0,  7,  0,  4 },
    {0, 0,  0,  0,  0,  0 }
  };

static queue<int> myqueue;

static int bfs(int src, int des) {
  int i;
  while (!myqueue.empty()) {  // Clear queue
    myqueue.pop();
  }

  for (i = 0; i < VertexNum; ++i) {
    pre[i] = -1;
  }
  pre[src] = 0;
  flow[src] = INF;
  myqueue.push(src);
  while (!myqueue.empty()) {
    int index = myqueue.front();
    myqueue.pop();
    if (index == des) {
      break;
    }
    for (i = 0; i < VertexNum; ++i) {
      if (i != src && capacity[index][i] > 0 && pre[i] == -1) {
        pre[i] = index;
        flow[i] = min(capacity[index][i], flow[index]);
        myqueue.push(i);
      }
    }
  }
  if (pre[des] == -1) {
    return -1;
  } else {
    return flow[des];
  }
}

static int MaxFlow(int src, int des) {
  int increasement = 0;
  int sumflow = 0;
  while ((increasement = bfs(src, des)) != -1) {
    int k = des;
    while (k != src) {
      int last = pre[k];
      capacity[last][k] -= increasement;  // forward arc
      capacity[k][last] += increasement;  // reverse arc
      k = last;
    }
    sumflow += increasement;
  }
  return sumflow;
}

int main() {
  memset(flow, 0, sizeof(flow));

  int maxflow = MaxFlow(0, VertexNum - 1);
  cout << "maximum flow: " << maxflow << endl;

  return 0;
}
