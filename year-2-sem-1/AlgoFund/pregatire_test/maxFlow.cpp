//
// Created by Catalina Macovei on 04.01.2024.
//
#include <bits/stdc++.h>
using namespace std;
// O nm2

// Variabile globale pentru stocarea grafului original, grafului rezidual și a rezultatelor afișate.
int n, m;           // numărul de noduri și arce
int s, t;           // sursa și destinația
int graf[1001][1001];           // graful original
int rezgraf[1001][1001];        // graful rezidual
int graf_afisare[1001][1001];   // rezultatul afișat


// Funcție pentru găsirea unui drum valid folosind BFS
bool bfs(int rGraf[1001][1001], int s, int t, int parinti[]) {
    bool viz[n + 1];
    memset(viz, 0, sizeof(viz));
    queue<int> q;
    q.push(s);
    viz[s] = true;
    parinti[s] = -1;

    while (!q.empty()) {
        int from = q.front();
        q.pop();
        for (int to = 1; to <= n; to++) {
            if (viz[to] == false && rGraf[from][to] > 0) {
                q.push(to);
                parinti[to] = from;
                viz[to] = true;
            }
        }
    }

    return viz[t] == true;
}

// Funcție DFS pentru marcarea nodurilor accesibile din sursă
void dfs(int rGraf[1001][1001], int s, bool viz[]) {
    viz[s] = true;
    for (int i = 0; i < n; i++)
        if (rGraf[s][i] && !viz[i])
            dfs(rGraf, i, viz);
}

// Funcție Ford-Fulkerson pentru calculul fluxului maxim
int ford_fulkerson_max_flow(int s, int t) {
    int u, v;

    // Graful rezidual, inițial identic cu graful original
    int rGraf[1001][1001];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            rGraf[i][j] = rezgraf[i][j];

    // Vector pentru stocarea pathului găsit de BFS
    int parinti[1001];

    int max_flow = 0;  // fluxul maxim

    // Cautare drum valid
    while (bfs(rGraf, s, t, parinti)) {
        // Parcurg drumul găsit și aflu bottleneckul
        int flow = INT_MAX;
        for (int child = t; child != s; child = parinti[child]) {
            int parent = parinti[child];
            flow = min(flow, rGraf[parent][child]);
        }

        // Updatez valorile în drum: scad pe muchiile directe, adun pe cele inverse
        for (int child = t; child != s; child = parinti[child]) {
            int parent = parinti[child];
            rGraf[parent][child] -= flow;
            rGraf[child][parent] += flow;
        }

        max_flow += flow;
    }

    return max_flow;
}

// Funcție Ford-Fulkerson pentru afișarea rezultatelor și a grafului rezidual
int ford_fulkerson(int s, int t, int max_fl) {
    int u, v;

    // Graful rezidual, inițial identic cu graful original
    int rGraf[1001][1001];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            rGraf[i][j] = graf[i][j];

    // Vector pentru stocarea pathului găsit de BFS
    int parinti[1001];

    int max_flow = max_fl;  // fluxul maxim

    // Cautare drum valid
    while (bfs(rezgraf, s, t, parinti)) {
        // Parcurg drumul găsit și aflu bottleneckul
        int flow = INT_MAX;
        for (int child = t; child != s; child = parinti[child]) {
            int parent = parinti[child];
            flow = min(flow, rezgraf[parent][child]);
        }

        // Updatez valorile în drum: scad pe muchiile directe, adun pe cele inverse
        for (int child = t; child != s; child = parinti[child]) {
            int parent = parinti[child];
            rezgraf[parent][child] -= flow;
            rezgraf[child][parent] += flow;
        }

        max_flow += flow;
    }

    // Afișare rezultate
    cout << ((max_flow < 1) ? "NU" : "DA") << "\n" << max_flow << "\n";
    if (max_flow) {
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < m; j++) {
                if (graf_afisare[i][j])
                    cout << i << "\t" << j << "\t" << ((rezgraf[i][j] != 0) ? rezgraf[i][j] : rezgraf[j][i]) << "\n";
            }
        }

        cout << max_flow << "\n";

        // Fluxul este maxim acum, găsesc nodurile accesibile din sursă
        bool visited[n];
        memset(visited, false, sizeof(visited));
        dfs(rezgraf, s, visited);

        // Afișez toate muchiile care sunt de la un nod accesibil la un nod neaccesibil în graful original
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                if (visited[i] && !visited[j] && graf[i][j]) {
                    cout << i << "  " << j << endl;
                }
            }
    }
    return max_flow;
}


int main() {
    // Citire număr de noduri și arce, sursă, destinație
    cin >> n;
    cin >> s >> t;
    cin >> m;

    // Citire arce și capacități/costuri
    for (int i = 1; i <= m; i++) {
        int x, y, z, l;
        cin >> x >> y >> z >> l;
        graf[x][y] = z;
        rezgraf[x][y] = z - l;
        rezgraf[y][x] = l;
        graf_afisare[x][y] = 1;
    }

    // Calcul flux maxim și afișare rezultate
    int max_f = ford_fulkerson_max_flow(s, t);

    ford_fulkerson(s, t, max_f);

    return 0;
}