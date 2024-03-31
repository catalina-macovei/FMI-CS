/////  O n+m
// Created by Catalina Macovei on 28.10.2023.
//
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> vecini;  // Listă de adiacență pentru graful de prietenii
vector<int> culoare;        // Vector pentru colorarea nodurilor
int n, m;                    // Numărul de elevi și numărul de prietenii

bool esteBipartit() {
    culoare.assign(n, -1);

    for (int start = 0; start < n; ++start) {
        if (culoare[start] == -1) {
            queue<int> coada;
            coada.push(start);
            culoare[start] = 0;

            while (!coada.empty()) {
                int u = coada.front();
                coada.pop();

                for (int v : vecini[u]) {
                    if (culoare[v] == -1) {
                        culoare[v] = 1 - culoare[u];
                        coada.push(v);
                    } else if (culoare[v] == culoare[u]) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

int main() {
    cin >> n >> m;
    vecini.resize(n);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        vecini[a - 1].push_back(b - 1);
        vecini[b - 1].push_back(a - 1);
    }

    if (esteBipartit()) {
        for (int i = 0; i < n; ++i) {
            if (culoare[i] == 0) {
                cout << "1 ";
            } else {
                cout << "2 ";
            }
        }
        cout << "\n";
    } else {
        cout << "IMPOSSIBLE";
    }

    return 0;
}
