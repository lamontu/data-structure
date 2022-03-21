// https://www.geeksforgeeks.org/strongly-connected-components/
// https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#define NIL -1
using namespace std;

// A class that represents an directed graph
class Graph
{
	int V; // No. of vertices
	vector<list<int>> adj;
public:
	explicit Graph(int V); // Constructor
	void addEdge(int v, int w); // function to add an edge to graph

private:
	// A Recursive DFS based function used by SCC_tarjan()
	void SCCUtil(int u, int disc[], int low[],
		stack<int>* st, bool stackMember[]);
public:
	// find strongly connected components in a given directed graph using Tarjan's algorithm (single DFS)
	void SCC_Tarjan();

private:
	// Fills Stack with vertices (in increasing order of finishing
    // times). The top element of stack has the maximum finishing time
    void fillOrder(int v, bool visited[], stack<int> &Stack);
    // A recursive function to print DFS starting from v
    void DFSUtil(int v, bool visited[]);
	// Function that returns reverse (or transpose) of this graph
    Graph getTranspose();
public:	
	// find strongly connected components in a given directed graph using Kosaraju's algorithm
	void SCC_Kosaraju();
};

Graph::Graph(int V) : V(V), adj(vector<list<int>>(V, list<int>()))
{
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
}

// A recursive function that finds and prints strongly connected
// components using DFS traversal
// u --> The vertex to be visited next
// disc[] --> Stores discovery times of visited vertices
// low[] -- >> earliest visited vertex (the vertex with minimum
//			 discovery time) that can be reached from subtree
//			 rooted with current vertex
// *st -- >> To store all the connected ancestors (could be part
//		 of SCC)
// stackMember[] --> bit/index array for faster check whether
//				 a node is in stack
void Graph::SCCUtil(int u, int disc[], int low[], stack<int>* st,
	bool stackMember[])
{
	// A static variable is used for simplicity, we can avoid use
	// of static variable by passing a pointer.
	static int time = 0;

	// Initialize discovery time and low value
	disc[u] = low[u] = ++time;
	st->push(u);
	stackMember[u] = true;

	// Go through all vertices adjacent to this
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i; // v is current adjacent of 'u'

		// If v is not visited yet, then recur for it
		if (disc[v] == NIL)
		{
			SCCUtil(v, disc, low, st, stackMember);

			// Check if the subtree rooted with 'v' has a
			// connection to one of the ancestors of 'u'
			// Case 1 (per above discussion on Disc and Low value)
			low[u] = min(low[u], low[v]);
		}

		// Update low value of 'u' only of 'v' is still in stack
		// (i.e. it's a back edge, not cross edge).
		// Case 2 (per above discussion on Disc and Low value)
		else if (stackMember[v] == true)
			low[u] = min(low[u], disc[v]);
	}

	// head node found, pop the stack and print an SCC
	if (low[u] == disc[u])
	{
	    int w = -1; // To store stack extracted vertices
		do
		{
			w = (int)st->top();
			cout << w << " ";
			stackMember[w] = false;
			st->pop();
		} while (w != u);
		cout << endl;  // End of current SCC

	}
}

// The function to do DFS traversal. It uses SCCUtil()
void Graph::SCC_Tarjan()
{
	int* disc = new int[V];
	int* low = new int[V];
	bool* stackMember = new bool[V];
	stack<int>* st = new stack<int>();

	// Initialize disc and low, and stackMember arrays
	for (int i = 0; i < V; i++)
	{
		disc[i] = NIL;
		low[i] = NIL;
		stackMember[i] = false;
	}

	// Call the recursive helper function to find strongly
	// connected components in DFS tree with vertex 'i'
	for (int i = 0; i < V; i++)
		if (disc[i] == NIL)
			SCCUtil(i, disc, low, st, stackMember);
}

// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";
  
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}
  
Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

void Graph::fillOrder(int v, bool visited[], stack<int>& Stack)
{
    // Mark the current node as visited and print it
    visited[v] = true;
  
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            fillOrder(*i, visited, Stack);
  
    // All vertices reachable from v are processed by now, push v 
    Stack.push(v);
}

// The main function that finds and prints all strongly connected 
// components
void Graph::SCC_Kosaraju()
{
    stack<int> Stack;
  
    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
  
    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            fillOrder(i, visited, Stack);
  
    // Create a reversed graph
    Graph gr = getTranspose();
  
    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < V; i++)
        visited[i] = false;
  
    // Now process all vertices in order defined by Stack
    while (!Stack.empty())
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();
  
        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
            gr.DFSUtil(v, visited);
            cout << endl;
        }
    }
}

// Driver program to test above function
int main()
{
	cout << "\nSCCs in first graph \n";
	Graph g1(5);
	g1.addEdge(1, 0);
	g1.addEdge(0, 2);
	g1.addEdge(2, 1);
	g1.addEdge(0, 3);
	g1.addEdge(3, 4);
	g1.SCC_Tarjan();
	cout << "--------\n";
	g1.SCC_Kosaraju();

	cout << "\nSCCs in second graph \n";
	Graph g2(4);
	g2.addEdge(0, 1);
	g2.addEdge(1, 2);
	g2.addEdge(2, 3);
	g2.SCC_Tarjan();
	cout << "--------\n";
	g2.SCC_Kosaraju();

	cout << "\nSCCs in third graph \n";
	Graph g3(7);
	g3.addEdge(0, 1);
	g3.addEdge(1, 2);
	g3.addEdge(2, 0);
	g3.addEdge(1, 3);
	g3.addEdge(1, 4);
	g3.addEdge(1, 6);
	g3.addEdge(3, 5);
	g3.addEdge(4, 5);
	g3.SCC_Tarjan();
	cout << "--------\n";
	g3.SCC_Kosaraju();

	cout << "\nSCCs in fourth graph \n";
	Graph g4(11);
	g4.addEdge(0, 1); g4.addEdge(0, 3);
	g4.addEdge(1, 2); g4.addEdge(1, 4);
	g4.addEdge(2, 0); g4.addEdge(2, 6);
	g4.addEdge(3, 2);
	g4.addEdge(4, 5); g4.addEdge(4, 6);
	g4.addEdge(5, 6); g4.addEdge(5, 7); g4.addEdge(5, 8); g4.addEdge(5, 9);
	g4.addEdge(6, 4);
	g4.addEdge(7, 9);
	g4.addEdge(8, 9);
	g4.addEdge(9, 8);
	g4.SCC_Tarjan();
	cout << "--------\n";
	g4.SCC_Kosaraju();

	cout << "\nSCCs in fifth graph \n";
	Graph g5(5);
	g5.addEdge(0, 1);
	g5.addEdge(1, 2);
	g5.addEdge(2, 3);
	g5.addEdge(2, 4);
	g5.addEdge(3, 0);
	g5.addEdge(4, 2);
	g5.SCC_Tarjan();
	cout << "--------\n";
	g5.SCC_Kosaraju();

	cout << "\nSCCs in sixth graph \n";
	Graph g6(6);
	g6.addEdge(0, 1);
	g6.addEdge(0, 3);
	g6.addEdge(1, 2);
	g6.addEdge(1, 4);
	g6.addEdge(2, 5);
	g6.addEdge(3, 4);
	g6.addEdge(4, 0);
	g6.addEdge(4, 5);
	g6.SCC_Tarjan();
	cout << "--------\n";
	g6.SCC_Kosaraju();

	cout << "\nSCCs in seventh graph \n";
	Graph g7(10);
	g7.addEdge(0, 1);  //AB
	g7.addEdge(1, 2);  //BC
	g7.addEdge(2, 3);  //CD
	g7.addEdge(3, 0);  //DA
	g7.addEdge(2, 0);  //CA
	g7.addEdge(2, 4);  //CE
	g7.addEdge(4, 5);  //EF
	g7.addEdge(5, 6);  //FG
	g7.addEdge(6, 2);  //GC
	g7.addEdge(6, 4);  //GE
	g7.addEdge(5, 7);  //FH
	g7.addEdge(7, 8);  //HI
	g7.addEdge(8, 9);  //IJ
	g7.addEdge(9, 5);  //JF
	g7.addEdge(8, 5);  //IF
	g7.SCC_Tarjan();
	cout << "--------\n";
	g7.SCC_Kosaraju();

	cout << "\nSCCs in eighth graph \n";
	Graph g8(8);
	g8.addEdge(0, 1);  // A B
	g8.addEdge(1, 7);  // B H
	g8.addEdge(7, 0);  // H A
	g8.addEdge(0, 2);  // A C
	g8.addEdge(2, 5);  // C F
	g8.addEdge(5, 0);  // F A
	g8.addEdge(0, 6);  // A G
	g8.addEdge(6, 5);  // G F
	g8.addEdge(2, 3);  // C D
	g8.addEdge(3, 4);  // D E
	g8.SCC_Tarjan();
	cout << "--------\n";
	g8.SCC_Kosaraju();

	return 0;
}