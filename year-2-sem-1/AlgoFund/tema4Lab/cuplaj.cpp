#include <bits/stdc++.h>
using namespace std;

// Variabile globale pentru stocarea grafului și a rezultatelor
int n, m, e;
vector<int> muchie[10001];
ifstream f("tema4Lab/cuplaj.in");  // Fișierul de intrare
ofstream g("tema4Lab/cuplaj.out");  // Fișierul de ieșire

int stg[10001]; // nodurile din stg
int dr[10001];  // nodurile din dr
int used[10001];
int gasit = 0;

// Funcție DFS pentru căutarea cuplajelor
bool dfs(int from) {
    used[from] = 1;

    // Încercare să se lege direct
    for (auto &to : muchie[from]) {
        if (dr[to] != 0)
            continue;
        stg[from] = to;
        dr[to] = from;
        gasit = 1;
        return 1;
    }

    // Lant alternant
    for (auto &to : muchie[from]) {
        if (!used[dr[to]]) {
            if (dfs(dr[to])) {
                dr[to] = from;
                stg[from] = to;
                return 1;
            }
        }
    }
    return 0;
}


int main() {
    f >> n >> m >> e;

    // Citirea muchiilor și construirea grafului bipartit
    for (int i = 1; i <= e; i++) {
        int x, y;
        f >> x >> y;
        muchie[x].push_back(y);
    }

    // aplic alg
    do {
        gasit = 0;
        fill(used + 1, used + n + 1, 0);
        for (int i = 1; i <= n; i++) {
            if (stg[i] == 0) {
                dfs(i);
            }
        }
    } while (gasit);

    // Colectare și afișare rezultate
    vector<pair<int, int>> rez;
    for (int i = 1; i <= n; i++) {
        if (stg[i] != 0)
            rez.push_back({i, stg[i]});
    }
    g << rez.size() << '\n';
    for (auto &x : rez) {
        g << x.first << ' ' << x.second << '\n';
    }

    return 0;
}