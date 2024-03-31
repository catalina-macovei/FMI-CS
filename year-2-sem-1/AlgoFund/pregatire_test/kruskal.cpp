#include <iostream> // Kruskal O (m) in practica
#include <algorithm>
#include <vector>
#include <utility>
#include <list>
using namespace std;

int parent[100], height[100]; // parent = vector tati, height = vector inaltime

void Initializare(int n) // Initializare
{
    // Fiecare Nod e propriul Arbore
    for (int i = 1; i <= n; i++)
        parent[i] = i, height[i] = 0;
}

int Reprez(int x) // Cautam Radacina Arbore - Reprez
{
    if (x == parent[x])
        return x;
    return Reprez(parent[x]);
}

void Reuneste(int x, int y) // Unim 2 Arbori (=C.Conexe) - Reuneste
// Arborele cu height mai mica devine subarbore pt celalalt
{
    int rootA = Reprez(x), rootB = Reprez(y);
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
    int n, m, i, x, y, weight;
    vector<pair<int, pair<int, int>>> G; // primul int = pondere, pair (nodeX, nodeY) = muchie

    cin >> n >> m;

    G.resize(m);
    list<pair<int, int>> apcm; // Arborele Partial de Cost Min

    // Citire Date
    for (i = 0; i < m; i++)
    {
        cin >> x >> y >> weight;
        G[i] = {weight, {x, y}};
    }

    // Sortam Crescator Muchiile dupa Pondere
    sort(G.begin(), G.end());
    Initializare(n);

    /*
    // Afisare Muchii Sortate
    for (i = 0; i < numEdges; i++)
        cout << edges[i].first << ' ' << edges[i].second.first << "->" << edges[i].second.second << endl;
    cout << endl;
    */

    int totalWeight = 0; // suma ponderi
    for (i = 0; i < m; i++)
    {
        weight = G[i].first;
        x = G[i].second.first;
        y = G[i].second.second;
        if (Reprez(x) != Reprez(y)) // Sa nu formeze un Ciclu
        {
            apcm.push_back({x, y});
            totalWeight += weight;
            Reuneste(x, y);
        }
    }

    cout << "Cost: " << totalWeight << endl;

    // Afisare APCM
    for (auto muchii : apcm)
        cout << muchii.first << ' ' << muchii.second << endl;

    return 0;
}

/*

7 9
5 1 9
3 1 7
3 2 15
1 2 11
1 6 1
6 4 16
6 7 8
2 7 4
7 4 2
 * */