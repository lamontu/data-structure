/* edmond_karp.cpp */

#include <iostream>
#include <queue>

using namespace std;

const int ArraySize = 100;
const int INF = ~(0x1 << 31);

int edge_num, vertex_num;
int flow[ArraySize];  // Current input flow of each vertex
int pre[ArraySize];  // The previous vertex in the path

/* The capacity of forward arc is the maximum flow that current flow can
 * increase. The capacity of reverse arc is the maximum flow that current
 * flow can decrease. 
 */
int capacity[ArraySize][ArraySize];
queue<int> myqueue;

int bfs(int src, int des) {
  int i, j;
  while (!myqueue.empty()) {  // Clear queue
    myqueue.pop();
  }
  // vertex index: from 1 to vertex_num
  for (i = 1; i <= vertex_num; ++i) {
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
    for (i = 1; i <= vertex_num; ++i) {
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

int MaxFlow(int src, int des) {
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

int main(int argc, char* argv[]) {
  int i, j;
  int start, end, ci;
  if (cin >> edge_num >> vertex_num) {
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    for (i = 0; i < edge_num; ++i) {
      cin >> start >> end >> ci;
      if (start == end) continue;
      capacity[start][end] += ci;
    }
    cout << MaxFlow(1, vertex_num) << endl;
  }
  return 0;
}
