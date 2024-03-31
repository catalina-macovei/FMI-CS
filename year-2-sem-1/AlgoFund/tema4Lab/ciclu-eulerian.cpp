/* input:
4
1 1 2
1 1 3
1 2 2
1 2 3
1 3 4
1 3 4
0
*/

#include <bits/stdc++.h>
using namespace std;
// un graf e eulerian -> are toate varfurile  de grad par

// Funcție pentru parcurgerea în adâncime (DFS)
void DFS(int v, vector<vector<int>> adl, vector<bool> &visited, vector<pair<int, int>> &eulerPath) {
    visited[v] = true;

    // Parcurgere vecini
    for (int i = 0; i < adl[v].size(); i++) {
        int u = adl[v][i];
        if (!visited[u]) {
            eulerPath.push_back({v, u});  // Adăugare muchie (v, u) la calea euleriană
            DFS(u, adl, visited, eulerPath);
        }
    }
}

int main() {
    int n;
    cout << "Introduceți numărul de vârfuri: ";
    cin >> n;

    vector<vector<int>> adl(n + 1);

    cout << "\n\nIntroduceți Muchiile în Graf (ex: 1 v1 v2 pentru adăugarea unei Muchii | 0 pentru a termina adăugarea Muchiilor) :\n";
    int q, x, y;
    do {
        cin >> q;
        if (q == 1) {
            cin >> x >> y;
            adl[x].push_back(y);
            adl[y].push_back(x);
        }
    } while (q != 0);

    vector<bool> visited(n + 1, false);
    vector<pair<int, int>> eulerPath;

    int startVertex = -1;

    // Găsirea primului vârf cu grad nenul pentru a începe traversarea
    for (int i = 1; i <= n; i++) {
        if (adl[i].size() != 0) {
            startVertex = i;
            break;
        }
    }

    if (startVertex == -1) {
        cout << "\nGraful are 0 Muchii -> Eulerian\n";
    } else {
        DFS(startVertex, adl, visited, eulerPath);

        // Verificare dacă toate vârfurile cu grad nenul au fost vizitate
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && adl[i].size() > 0) {
                cout << "\nNici Ciclu Eulerian, nici Drum Eulerian\n";
                exit(0);
            }
        }

        int odd = 0;

        // Verificare numărul de vârfuri cu grad impar
        for (int i = 1; i <= n; i++) {
            if (adl[i].size() % 2 != 0) {
                ++odd;
            }
        }

        if (odd > 2) {
            cout << "\nNici Ciclu Eulerian, nici Drum Eulerian\n";
        } else if (odd == 2) {
            cout << "\nDrum Eulerian\n";
        } else {
            cout << "\nCiclu Eulerian\n";
        }

        // Afișare cale sau ciclu Eulerian
        for (auto edge : eulerPath) {
            cout << edge.first << " " << edge.second << '\n';
        }
    }

    return 0;
}
