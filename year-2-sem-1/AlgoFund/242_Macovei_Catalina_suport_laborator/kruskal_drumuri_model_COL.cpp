//
// Created by Catalina Macovei on 23.01.2024.
//
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

int degree[100000], degree1[100000];
vector<pair<int, int>> adjacencyList[100000], adjacencyList1[100000];
int parent[100000], height[100000];

void init(int n)
{
    for (int i = 1; i <= n; i++)
        parent[i] = i;
}

int Find(int x)     // detectare recursiva de ciclu
{
    if (x == parent[x]) // x == tata[x] ciclu
        return x;
    return Find(parent[x]);
}

void Union(int x, int y)    // reuniunea padurilor
{
    int a = Find(x), b = Find(y);
    if (height[a] < height[b])
        parent[a] = b;
    else if (height[a] > height[b])
        parent[b] = a;
    else if (a != b)
    {
        parent[b] = a;
        height[a]++;
    }
}

int main()
{
    int i, vertex1, vertex2, cost, count = 0, totalCost = 0, budged = 0;
    vector<pair<int, pair<int, int>>> edges, graph; // cost, vertex1, vertex2
    vector<pair<int, pair<int, int>>> graph2;

    //ifstream fin("pregatire_test/date.in");
    int n, m, k;
    cin >> n >> m >> k >> budged;

    // gestionarea limitelor
    assert(n >= 1 && n <= 100000);
    assert(k <= 5);
    assert(m >= 1 && m <= 2*100000);

    // initializarea grafului original
    for (i = 0; i < m; i++)
    {
        cin >> vertex1 >> vertex2 >> cost;
        graph.push_back({cost, {vertex1, vertex2}});

        adjacencyList[vertex1].push_back({vertex2, cost});
        adjacencyList[vertex2].push_back({vertex1, cost});
        degree[vertex1]++; // degree of vertices
        degree[vertex2]++;
    }

    // initializarea muchiilor obligatorii si atribuirea costurilor coresp
    for (int j=0; j < k; j++) {
        int cost_org, vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        for (i = 0; i < m; i++) {
            if (vertex1 == graph[i].second.first && vertex2 == graph[i].second.second) {
                cost_org = graph[i].first;

                edges.push_back({cost_org, {vertex1, vertex2}}); // le stocam intr-un vector separat
            }
        }
    }
    //fin.close();

    list<pair<int, int>> minSpanningTree; // acesta e MST final
    graph2 = graph;
    sort(graph.begin(), graph.end());      // sortam lista de adiacenta in functie de costuri
    init(n);
    totalCost = 0;

    // incep cu muchiile obligatorii
    for (i = 0; i < k; i++)
    {
        cost = edges[i].first;
        vertex1 = edges[i].second.first;
        vertex2 = edges[i].second.second;

        if (Find(vertex1) != Find(vertex2))
        {
            totalCost += cost;
            Union(vertex1, vertex2);
            minSpanningTree.push_back({vertex1, vertex2});
            adjacencyList1[vertex1].push_back({vertex2, cost});
            adjacencyList1[vertex2].push_back({vertex1, cost});
            degree1[vertex1]++;
            degree1[vertex2]++;
        }
//            // If mandatory edges cannot be added, then we don't have a tree
//        else
//        {
//            cout << "No spanning tree exists";
//            return 0;
//        }
    }

    count = 0;

    // Continui cu restul muchiilor
    for (i = 0; i < m - k; i++)
    {
        cost = graph[i].first;
        vertex1 = graph[i].second.first;
        vertex2 = graph[i].second.second;

        if (Find(vertex1) != Find(vertex2))  // dc nu formeaza un ciclu
        {
            totalCost += cost;
            Union(vertex1, vertex2);
            minSpanningTree.push_back({vertex1, vertex2});
            adjacencyList1[vertex1].push_back({vertex2, cost});
            adjacencyList1[vertex2].push_back({vertex1, cost});
            count++;
            degree1[vertex1]++;
            degree1[vertex2]++;
        }
    }

    // Total Cost <= bugetul alocat
    if ( totalCost <= budged) {
        cout << "Da" << endl;
        for (auto edge: minSpanningTree)
            cout << edge.first << " " << edge.second << endl;
    } else {
        cout << "Nu";
    }
    return 0;
}

/* input
9 14 2 100
1 2 10
1 3 11
2 4 11
2 5 11
5 6 13
3 4 10
4 6 12
4 7 5
3 7 4
3 8 5
8 7 5
8 9 4
9 7 3
6 7 11
1 2
3 4
 * */