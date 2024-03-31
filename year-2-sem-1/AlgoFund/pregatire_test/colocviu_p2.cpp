//
// Created by Catalina Macovei on 18.02.2024.
//
/*
 * graf neorientat ponderat G
 * 1 linie - nr varf , nr muchii
 * extremitati + pondere
 * a) afisati costul unui apcm O m log n
 * b) se citesc 2 muchii noi +ponderile lor
 *  decideti pe care o adaugati ai. noul graf sa aiba un arbore partial de cost cat mai mic si afisati muchiile unui apcm de cost minim in acest graf
 */

/*
 5 5
 1 2 1
 1 4 2
 2 3 4
 3 4 8
 4 5 6

 3 5 5
 1 3 5
 */

//
// Created by Catalina Macovei on 02.12.2023.
// ultim ex
// Al doilea arbore de acoperire minima cu multimi disjuncte


#include <iostream> // Kruskal O (m) in practica
#include <algorithm>
#include <vector>
#include <utility>
#include <list>
using namespace std;

int tata[100], dist[100]; // parent = vector tati, height = vector inaltime

void Initializare(int n) // Initializare
{
    // Fiecare Nod e propriul Arbore
    for (int i = 1; i <= n; i++)
        tata[i] = i, dist[i] = 0;
}

int Reprez(int x) // Cautam Radacina Arbore - Reprez
{
    if (x == tata[x])
        return x;
    return Reprez(tata[x]);
}

void Reuneste(int x, int y) // Unim 2 Arbori (=C.Conexe) - Reuneste
// Arborele cu height mai mica devine subarbore pt celalalt
{
    int rootA = Reprez(x), rootB = Reprez(y);
    if (dist[rootB] > dist[rootA])
        tata[rootA] = rootB;
    else if (dist[rootB] < dist[rootA])
        tata[rootB] = rootA;
    else if (rootA != rootB)
    {
        tata[rootB] = rootA;
        dist[rootA]++;
    }
}

int main()
{
    int n, m, i, x, y, pond;
    vector<pair<int, pair<int, int>>> G; // primul int = pondere, pair (nodeX, nodeY) = muchie

    cin >> n >> m;

    G.resize(m);
    list<pair<int, int>> apcm; // Arborele Partial de Cost Min

    // Citire Date
    for (i = 0; i < m; i++)
    {
        cin >> x >> y >> pond;
        G[i] = {pond, {x, y}};
    }

    // citesc muchiile suplimentare
    int muchieA[4];
    int muchieB[4];
    cin >> muchieA[0] >> muchieA[1] >> muchieA[2];
    cin >> muchieB[0] >> muchieB[1] >> muchieB[2];

    // Sortam Crescator Muchiile dupa Pondere
    sort(G.begin(), G.end());
    Initializare(n);

    /*
    // Afisare Muchii Sortate
    for (i = 0; i < numEdges; i++)
        cout << edges[i].first << ' ' << edges[i].second.first << "->" << edges[i].second.second << endl;
    cout << endl;
    */

    int totalCost = 0; // suma ponderi
    for (i = 0; i < m; i++)
    {
        pond = G[i].first;
        x = G[i].second.first;
        y = G[i].second.second;
        if (Reprez(x) != Reprez(y)) // Sa nu formeze un Ciclu
        {
            apcm.push_back({x, y});
            totalCost += pond;
            Reuneste(x, y);
        }
    }

    cout << "Cost: " << totalCost << endl;

    // Afisare APCM
    for (auto muchii : apcm)
        cout << muchii.first << ' ' << muchii.second << endl;


    /**         Adaug muchii apcm       */
    /// 1
    for ( i = 0; i <= n; i++)
    {
        cout << tata[i] << endl;
    }

    return 0;
}