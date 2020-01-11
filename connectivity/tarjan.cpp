#include <algorithm>
#include <iostream>

using std::min;
using std::cout;
using std::cin;
using std::endl;

const size_t MAX_SIZE = 64;

static struct edge {
    size_t v;  // index of the end vertex of this edges
    int next;  // index of the next edges that has the same start vertex with this edges
 } edges[MAX_SIZE];

static size_t edge_index;
static int heads[MAX_SIZE];

static bool visited[MAX_SIZE];

static size_t visit_order, st_idx;
static size_t DFN[MAX_SIZE], LOW[MAX_SIZE], stack[MAX_SIZE];

static size_t start_vertexes[MAX_SIZE] = {1, 1, 2, 2, 3, 4, 5, 5};
static size_t end_vertexes[MAX_SIZE] =   {2, 4, 3, 5, 6, 5, 1, 6};
/*  Sample graph
 *    1  ------>  2  ------>  3
 *    |  ↖︎        |           |
 *    |    ╲      |           |
 *    ↓       ╲   ↓           ↓
 *    4  ------>  5  ------>  6
 */

static void add(size_t start,size_t y) {
    edges[++edge_index].next = heads[start];
    edges[edge_index].v = y;
    heads[start] = edge_index;
    return ;
}

static void CreateGraph(size_t* starts, size_t* ends, size_t edge_num) {
    for (size_t i = 0; i < edge_num; ++i) {
        add(starts[i], ends[i]);
    }
}

static void Tarjan(size_t start) {
    DFN[start] = LOW[start] = ++visit_order;  // 新进点的初始化。
    stack[++st_idx]=start;  // 入栈
    visited[start]=1;  // 表示在栈里
    for (int i = heads[start]; i != -1; i=edges[i].next) {
        if (!DFN[edges[i].v]) {  // 如果没访问过
            Tarjan(edges[i].v);  // 按照边的方向延伸访问边的终点，开始递归
            LOW[start] = min(LOW[start], LOW[edges[i].v]);  // 递归出来，比较谁是谁的儿子／父亲，就是树的对应关系，涉及到强连通分量子树最小根的事情。
        } else if (visited[edges[i].v]) {  // 如果访问过，并且还在栈里。
            LOW[start] = min(LOW[start], DFN[edges[i].v]);  // 比较谁是谁的儿子／父亲。就是链接对应关系
        }
    }
    if (LOW[start] == DFN[start]) {  // 发现是整个强连通分量子树里的最小根。
        do {
            cout << stack[st_idx] << " ";
            visited[stack[st_idx]]=0;
            st_idx--;
        } while (start!=stack[st_idx+1]);  // 出栈，并且输出。
        cout << endl;
    }
    return;
}

int main() {
    memset(heads,-1,sizeof(heads));
    size_t n, m;
    cout << "Input verter number and edges number:" << endl;
    // scanf("%d%d",&n,&m);
    cin >> n >> m;

    // size_t start,end;
    // cout << "Input edges start vertex and end vertex:" << endl;
    // for (size_t i = 1; i <= m; ++i) {
    //     // scanf("%d%d",&start,&y);
    //     cin >> start >> end;
    //     add(start, end);
    // }

    CreateGraph(start_vertexes, end_vertexes, m);

    cout << "Found connectivity by tarjan:" << endl;
    for (size_t i = 1; i <= n; ++i) {
        if (!DFN[i]) {
            Tarjan(i);  // 当这个点没有访问过，就从此点开始。防止图没走完
        }
    }
    return 0;
 }
