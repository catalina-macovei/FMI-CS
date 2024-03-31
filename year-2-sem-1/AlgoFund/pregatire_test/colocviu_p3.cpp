
// C++ program to print all the cycles
// in an undirected graph
#include <bits/stdc++.h>

using namespace std;
const int N = 100000;

// variables to be used
// in both functions
vector<int> graph[N];
vector<vector<int>> cicluri;
vector<int> elem_cicluri;
int nrCicluri = 0;
int color[N];
int tata[N];
// Function to mark the vertex with
// different colors for different cycles
void dfs_cycle(int u, int p)
{

    // nod complet vizitat
    if (color[u] == 2) {    // negru = vizitat
        return;
    }

    // nodul gri -> posibil ciclu , adica muchie de intoarcere
    // backtrack pe tata pentru a gasi toate nodurile
    if (color[u] == 1) {    // gri == in proces de explorare
        vector<int> tempv;
        nrCicluri++;

        int curent = p;
        tempv.push_back(curent);
        elem_cicluri.push_back(curent);
        // backtrack the vertex which are
        // in the current cycle thats found
        while (curent != u) {
            curent = tata[curent];
            tempv.push_back(curent);
            elem_cicluri.push_back(curent);
        }
        cicluri.push_back(tempv);
        return;
    }
    tata[u] = p;

    // partially visited.
    color[u] = 1;

    // simple dfs on graph
    for (int v : graph[u]) {

        // if it has not been visited previously
        if (v == tata[u]) {
            continue;
        }
        dfs_cycle(v, u);
    }

    // finalizat
    color[u] = 2;
}

// add the edges to the graph
void addEdge(int u, int v)
{
    graph[u].push_back(v);
    graph[v].push_back(u);
}

// Function to print the cycles
void printCycles()
{

    // print all the vertex with same cycle
    for (int i = 0; i < nrCicluri; i++) {
        // Print the i-th cycle
        cout << "Cycle Number " << i + 1 << ": ";
        for (int x : cicluri[i])
            cout << x << " ";
        cout << endl;
    }
}

// Driver Code
int main()
{
    int n, m, x, y, test_v;
    // add edges
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        addEdge(x, y);
    }
    // call DFS to mark the cycles
    dfs_cycle(1, 0);
    cin >> test_v;

    cout << "muchii critice: " << endl;
    for (int v : graph[test_v])
    {
        auto it = find(elem_cicluri.begin(), elem_cicluri.end(), v);
        if (it == elem_cicluri.end())
            cout << "1 " << v << endl;

    }

    // function to print the cycles
    // printCycles();

    // dc nu e muchie critica, o pot sterge pe oricare extrema din lista de vecini
}
/*
 11 13
 1 2
 1 3
 1 4
 1 5
 4 5
 5 6
 1 7
 7 8
 1 8
 4 9
 9 10
 10 4
 9 11

 */