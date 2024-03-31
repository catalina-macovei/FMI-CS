////
//// Created by Catalina Macovei on 20.02.2024.
////
//#include<bits/stdc++.h>
//using namespace std;
//
//// visited[] array to make nodes visited
//// src is starting node for DFS traversal
//// prev_len is sum of cable length till current node
//// max_len is pointer which stores the maximum length
//// of cable value after DFS traversal
//void DFS(vector< pair<int,int> > graph[], int src,
//         int prev_len, int *max_len,
//         vector <bool> &visited)
//{
//    // Mark the src node visited
//    visited[src] = 1;
//
//    // curr_len is for length of cable from src
//    // city to its adjacent city
//    int curr_len = 0;
//
//    // Adjacent is pair type which stores
//    // destination city and cable length
//    pair < int, int > adjacent;
//
//    // Traverse all adjacent
//    for (int i=0; i<graph[src].size(); i++)
//    {
//        // Adjacent element
//        adjacent = graph[src][i];
//
//        // If node or city is not visited
//        if (!visited[adjacent.first])
//        {
//            // Total length of cable from src city
//            // to its adjacent
//            curr_len = prev_len + adjacent.second;
//
//            // Call DFS for adjacent city
//            DFS(graph, adjacent.first, curr_len,
//                max_len,  visited);
//        }
//
//        // If total cable length till now greater than
//        // previous length then update it
//        if ((*max_len) < curr_len)
//            *max_len = curr_len;
//
//        // make curr_len = 0 for next adjacent
//        curr_len = 0;
//    }
//}
//
//// n is number of cities or nodes in graph
//// cable_lines is total cable_lines among the cities
//// or edges in graph
//int longestCable(vector<pair<int,int> > graph[],
//                 int n)
//{
//    // maximum length of cable among the connected
//    // cities
//    int max_len = INT_MIN;
//
//    // call DFS for each city to find maximum
//    // length of cable
//    for (int i=1; i<=n; i++)
//    {
//        // initialize visited array with 0
//        vector< bool > visited(n+1, false);
//
//        // Call DFS for src vertex i
//        DFS(graph, i, 0, &max_len, visited);
//    }
//
//    return max_len;
//}
//
//// driver program to test the input
//int main()
//{
//    // n is number of cities
//    int n = 8;
//
//    vector< pair<int,int> > graph[n+1];
//
//    // create undirected graph
//    // first edge
//    graph[1].push_back(make_pair(1, 3));
//    graph[2].push_back(make_pair(3, 1));
//
//    // second edge
//    graph[2].push_back(make_pair(1, 5));
//    graph[3].push_back(make_pair(5, 1));
//
//    // third edge
//    graph[2].push_back(make_pair(3, 5));
//    graph[6].push_back(make_pair(5, 3));
//
//    // fourth edge
//    graph[4].push_back(make_pair(2, 4));
//    graph[6].push_back(make_pair(4, 2));
//
//    // fifth edge
//    graph[5].push_back(make_pair(1, 2));
//    graph[6].push_back(make_pair(2, 1));
//
//    graph[7].push_back(make_pair(2, 6));
//    graph[8].push_back(make_pair(6, 2));
//
//    cout << "Maximum length of cable = "
//         << longestCable(graph, n);
//
//    return 0;
//}

#include <bits/stdc++.h>
using namespace std;

// This class represents a undirected graph using adjacency list
class Graph
{
    int V;              // No. of vertices
    list<int> *adj;     // Pointer to an array containing
    // adjacency lists
public:
    Graph(int V);              // Constructor
    void addEdge(int v, int w);// function to add an edge to graph
    void longestPathLength();  // prints longest path of the tree
    pair<int, int> bfs(int u); // function returns maximum distant
    // node from u with its distance
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);    // Add w to v’s list.
    adj[w].push_back(v);    // Since the graph is undirected
}

//  method returns farthest node and its distance from node u
pair<int, int> Graph::bfs(int u)
{
    //  mark all distance with -1
    int dis[V];
    memset(dis, -1, sizeof(dis));

    queue<int> q;
    q.push(u);

    //  distance of u from u will be 0
    dis[u] = 0;

    while (!q.empty())
    {
        int t = q.front();       q.pop();

        //  loop for all adjacent nodes of node-t
        for (auto it = adj[t].begin(); it != adj[t].end(); it++)
        {
            int v = *it;

            // push node into queue only if
            // it is not visited already
            if (dis[v] == -1)
            {
                q.push(v);

                // make distance of v, one more
                // than distance of t
                dis[v] = dis[t] + 1;
            }
        }
    }

    int maxDis = 0;
    int nodeIdx;

    //  get farthest node distance and its index
    for (int i = 0; i < V; i++)
    {
        if (dis[i] > maxDis)
        {
            maxDis = dis[i];
            nodeIdx = i;
        }
    }
    return make_pair(nodeIdx, maxDis);
}

//  method prints longest path of given tree
void Graph::longestPathLength()
{
    pair<int, int> t1, t2;

    // first bfs to find one end point of
    // longest path
    t1 = bfs(6);

    //  second bfs to find actual longest path
    t2 = bfs(t1.first);

    cout << "Longest path is from " << 6 << " to "
         << t1.first << " of length " << t1.second;
}

// Driver code to test above methods
int main()
{
    // Create a graph given in the example
    Graph g(8);
    g.addEdge(1, 3);
    g.addEdge(1, 5);
    g.addEdge(3, 5);
    g.addEdge(2, 4);
    g.addEdge(1, 2);
    g.addEdge(2, 6);

    g.longestPathLength();
    return 0;
}