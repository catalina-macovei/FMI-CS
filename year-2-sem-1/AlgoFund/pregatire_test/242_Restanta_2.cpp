//
// Created by Catalina Macovei on 21.02.2024.
//
#include <iostream> // Kruskal O (m) in practica
#include <algorithm>
#include <vector>
#include <utility>
#include <list>
#include <cassert>
using namespace std;

int parent[10001], height[10001]; // parent = vector tati, height = vector inaltime

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
    int n, m, i, x, y,k, weight;
    vector<pair<int, pair<int, int>>> G; // primul int = pondere, pair (nodeX, nodeY) = muchie
    vector<pair<int, pair<int, int>>> muchii_cerute;
    vector<int> indici_muchii;

    cin >> n >> m;

    assert(n >= 1 && n <= 1000);
    assert(m >= 1 && m <= n*(n-1)/2);

    G.resize(m);
    list<pair<int, int>> apcm; // Arborele Partial de Cost Min

    // Citire Date
    for (i = 0; i < m; i++)
    {
        cin >> x >> y >> weight;
        if (weight >= 1 && weight <= 1000)
            G[i] = {weight, {x, y}};
        else
            return (42);
    }

    cin >> k;
    assert(k >= 1 && k <= m);

    for (i = 0; i < k ; i++)
    {
        cin >> x;
        indici_muchii.push_back(x);
    }

    for ( int ind : indici_muchii)
    {
        muchii_cerute.push_back(G[ind]);
    }

    // Sortam Crescator Muchiile dupa Pondere
    sort(G.begin(), G.end());
    Initializare(n);


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

    // Afisare APCM
    for (auto muc_cerr : muchii_cerute)
        for (auto muchii : apcm)
        {
            //cout << muchii.first << ' ' << muchii.second << endl;
            if ( (muchii.first == muc_cerr.second.first) && (muchii.second == muc_cerr.second.second))
            {
                cout << "Da" << endl;
            }
        }
    cout << "Da" << endl;

    return 0;
}