//
// Created by Catalina Macovei on 02.12.2023.

// Conectarea cu cost minim a nodurilor la mai multe  surse:
// Nature Reserve

#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100000;
int dist[NMAX + 1];  // vector pentru stocarea distanțelor
bool vis[NMAX + 1];  // vector pentru marcarea nodurilor vizitate
vector<pair<int, int>> graf[NMAX + 1];  // Listă de adiacență pentru graf

int main() {
    int t;
    cin >> t;
    while (t--) {
        set<pair<int, int>> stiva;  // multime pentru stocarea perechilor de distanțe și noduri
        int n, m, L, k;
        long long cost_total = 0;  // Variabilă pentru stocarea costului total

        /**    Citire si Initializare        **/
        cin >> n >> m >> L >> k;
        for (int i = 1; i <= n; i++) {
            dist[i] = 1000000;  // Inițializare distanțe la o valoare mare
            vis[i] = 0;   // Marchează toate nodurile ca nevizitate
        }

        // Citirea rezervațiilor naturale inițiale și actualizarea distanțelor
        for (int i = 1; i <= k; i++) {
            int x;
            cin >> x;
            dist[x] = 0;  // Setare distanță către rezervațiile inițiale la 0
            stiva.insert({0, x});  // Inserare pereche {0, x} distanta, nod=rezervatie
        }

        // Construire (conexiuni rutiere între orașe)
        for (int i = 1; i <= m; i++) {
            int x, y, pondere;
            cin >> x >> y >> pondere;
            graf[x].push_back({y, pondere});
            graf[y].push_back({x, pondere});
        }



        /**      DIJKSTRA       **/
        while (!stiva.empty()) {
            auto iter = stiva.begin();  // Selecția nodului cu cea mai mică distanță
            stiva.erase(iter);

            int cost = (*iter).first;  // Extrage costul din pereche
            int node = (*iter).second;  // Extrage nodul din pereche

            if (vis[node]) {
                continue;  // Sari peste dacă nodul este deja vizitat
            }
            vis[node] = 1;  // marchez nodul ca vizitat
            cost_total += 1LL * cost;  // Adaugă costul la soluția totală

            // Actualizează distanțele și inserează în set pentru nodurile adiacente
            for (auto next : graf[node]) {
                if (dist[next.first] > next.second) {
                    dist[next.first] = next.second;
                    stiva.insert({dist[next.first], next.first});
                }
            }
        }

        // Curăță graful pentru următoarea iterație
        for (int i = 1; i <= n; i++) {
            graf[i].clear();
        }

        // Adaugă costul de construire a rezervațiilor naturale pentru orașele rămase
        cost_total += 1LL * (n - k) * L;

        cout << cost_total << '\n';
    }
    return 0;
}

/** INPUT 1 linie -> number of datasets - nr de multimi
 * The first line contains four positive integers: the number of environmental monitoring stations
N, the number of two-way communication channels M
, the size of the program L
 (in bytes), and the number of initial stations S
 The second line contains
 positive integer representing the initial
 stations.
*
1
4 6 10 1
3
1 2 4
1 3 8
1 4 1
2 3 2
2 4 5
3 4 20
 */