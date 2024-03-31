//
// Created by Catalina Macovei on 13.12.2023.
//
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101; // Increased the size of the array

long long graph[MAXN][MAXN];

void warshall(int node) {
    for (int k = 1; k <= node; k++)
        for (int i = 1; i <= node; i++)
            for (int j = 1; j <= node; j++)
                if (graph[i][k] != LLONG_MAX && graph[k][j] != LLONG_MAX)
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}

// Funcție pentru afișarea tuturor drumurilor minime
void print(int n) {
    cout << "Toate drumurile cele mai scurte dintre perechi sunt: " << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (graph[i][j] == LLONG_MAX) {
                cout << "INF ";
            } else {
                cout << graph[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// Funcție pentru reconstrucția unui lanț cu diametrul specificat
void reconstructDiameterChain(long long graph[MAXN][MAXN], int n, long long diameter) {
    // Inițializare matrice de distanțe și predecesori
    vector<vector<long long>> dist(n, vector<long long>(n, LLONG_MAX));
    vector<vector<int>> prev(n, vector<int>(n, -1));

    // Inițializare distanțe pentru muchii
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph[i][j] != -1) {
                dist[i][j] = graph[i][j];
                prev[i][j] = i;
            }
        }
    }

    // Algoritmul Floyd-Warshall pentru toate perechile de noduri
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    prev[i][j] = prev[k][j];
                }
            }
        }
    }

    // Găsirea lanțului cu diametrul specificat
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && dist[i][j] == diameter) {
                cout << "Cel mai scurt lanț cu lungimea totală " << diameter << " a fost găsit: " << i << " ";
                int node = j;
                while (node != i) {
                    cout << node << " ";
                    node = prev[i][node];
                }
                cout << node << endl;
                return;
            }
        }
    }

    cout << "Nu s-a putut găsi un lanț cu diametrul specificat." << endl;
}

// Funcție pentru calculul razei, diametrului și centrului grafului
void calculateRadiusDiameterCenterChain(int n) {
    long long radius = LLONG_MAX;
    long long diameter = 0;
    int center = -1;

    // Parcurgerea nodurilor pentru găsirea excentricității
    for (int i = 1; i <= n; i++) {
        long long eccentricity = 0;
        for (int j = 1; j <= n; j++) {
            eccentricity = max(eccentricity, graph[i][j]);
        }

        // Actualizarea razei, diametrului și centrului grafului
        if (eccentricity < radius) {
            radius = eccentricity;
            center = i;
        }
        diameter = max(diameter, eccentricity);
    }

    // Afișarea razei, diametrului și centrului grafului
    cout << "Raza: " << radius << endl;
    cout << "Centrul: " << center << endl;
    cout << "Diametrul: " << diameter << endl;

    // Reconstrucția și afișarea unui lanț cu diametrul specificat (exemplu pentru diametrul 13)
    //reconstructDiameterChain(graph, n, 13);
}

int main() {
    int n, e, u, v, w;

    // Inițializare matrice de adiacență cu distanțe inițiale
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = LLONG_MAX;
            }
        }
    }

    // Citirea numărului de noduri și muchii
    cout << "Introduceți numărul de noduri și muchii: ";
    cin >> n >> e;

    // Citirea muchiilor și ponderilor lor
    cout << "Introduceți muchiile (u, v, w):" << endl;
    while (e--) {
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w; // Pentru graful neorientat
    }

    // Aplicarea algoritmului Warshall pentru găsirea drumurilor minime
    warshall(n);

    // Afișarea distanțelor minime între perechi de noduri
    print(n);

    // Calculul și afișarea razei, diametrului și centrului grafului
    calculateRadiusDiameterCenterChain(n);

    return 0;
}


/*
7 9

1 2 8

1 3 1

1 4 2

3 2 4

2 6 3

3 5 6

4 5 5

6 5 2

5 7 6
 */