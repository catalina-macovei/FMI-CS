#include <iostream> // Kruskal
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <list>
using namespace std;

int parent[100], height[100]; // parent = vector tati, height = vector inaltime

void initialize(int n) // Initializare
{
    // Fiecare Nod e propriul Arbore
    for (int i = 1; i <= n; i++)
        parent[i] = i, height[i] = 0;
}

int findRoot(int x) // Cautam Radacina Arbore
{
    if (x == parent[x])
        return x;
    return findRoot(parent[x]);
}

void unionTrees(int x, int y) // Unim 2 Arbori (=C.Conexe)
// Arborele cu height mai mica devine subarbore pt celalalt
{
    int rootA = findRoot(x), rootB = findRoot(y);
    if (height[rootB] > height[rootA])
        parent[rootA] = rootB;
    else if (height[rootB] < height[rootA])
        parent[rootB] = rootA;
    else if (rootA != rootB)
    {
        parent[rootB] = rootA;
        height[rootA]++;
    }
}

int main()
{
    int numNodes, numEdges, i, j, nodeX, nodeY, weight;
    vector<pair<int, pair<int, int>>> edges; // primul int = pondere, pair (nodeX, nodeY) = muchie

    ifstream fin("pregatire_test/date.in");

    fin >> numNodes >> numEdges;

    edges.resize(numEdges);
    list<pair<int, int>> minimumCostSpanningTree; // Arborele Partial de Cost Min

    // Citire Date
    for (i = 0; i < numEdges; i++)
    {
        fin >> nodeX >> nodeY >> weight;
        edges[i] = {weight, {nodeX, nodeY}};
    }
    fin.close();

    // Sortam Crescator Muchiile dupa Pondere
    sort(edges.begin(), edges.end());
    initialize(numNodes);

    /*
    // Afisare Muchii Sortate
    for (i = 0; i < numEdges; i++)
        cout << edges[i].first << ' ' << edges[i].second.first << "->" << edges[i].second.second << endl;
    cout << endl;
    */

    int totalWeight = 0; // suma ponderi
    for (i = 0; i < numEdges; i++)
    {
        weight = edges[i].first;
        nodeX = edges[i].second.first;
        nodeY = edges[i].second.second;
        if (findRoot(nodeX) != findRoot(nodeY)) // Sa nu formeze un Ciclu
        {
            minimumCostSpanningTree.push_back({nodeX, nodeY});
            totalWeight += weight;
            unionTrees(nodeX, nodeY);
        }
    }
    cout << "Cost: " << totalWeight << endl;
    // Afisare APCM
    for (auto pairNodes : minimumCostSpanningTree)
        cout << pairNodes.first << ' ' << pairNodes.second << endl;

    return 0;
}
