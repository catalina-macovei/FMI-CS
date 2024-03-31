/*
 pentru ciclu negativ
 4 4

1 2 1

4 2 -7

2 3 2

3 4 3

2

 fara cilcu negativ
 4 5
1 2 2
4 2 7
2 3 2
3 4 3
1 3 1
1
 */


// O nm
#include <bits/stdc++.h>
using namespace std;

// Vector de perechi pentru a reprezenta graful ponderat
vector<pair<int,int>> graf[50005];

// Vector pentru a memora distantele minime
int dist[50005];

// Vector pentru a memora numarul de vizite ale fiecarui nod
int viz[50005];

// Vector pentru a memora parintii fiecarui nod in cadrul drumului minim
int parent[50005];

int n, m;

// Deschiderea fisierelor de intrare si iesire
ifstream f("tema3Lab/ford.in");
ofstream g("tema3Lab/ford.out");

int main() {
    // Citirea numarului de noduri si muchii
    f >> n >> m;

    // Constructia grafului ponderat
    for (int i = 1; i <= m; i++) {
        int x, y, c;
        f >> x >> y >> c;
        graf[x].push_back({y, c});
    }

    // Initializarea distantei cu valori mari pentru a simboliza infinit
    fill(dist, dist + n + 1, INT_MAX);
    // Distanta de la nodul sursa la el insusi este 0
    dist[1] = 0;

    // Coada pentru parcurgerea BFS
    queue<int> q;
    q.push(1);

    // Variabila pentru a memora ultimul nod actualizat in caz de ciclu negativ
    int last_updated = -1;

    // Parcurgerea nodurilor prin BFS folosind algoritmul Bellman-Ford
    while (!q.empty()) {
        int from = q.front();
        q.pop();
        viz[from]++;

        // Verificarea existentei unui ciclu negativ
        if (viz[from] == n + 1) {
            last_updated = from;
            break; // S-a gasit un ciclu negativ care il implica pe 'from'
        }

        // Parcurgerea vecinilor nodului curent
        for (auto &x : graf[from]) {
            int to = x.first;
            int cost = x.second;

            // Actualizarea distantei minime si a parintelui
            if (dist[to] > dist[from] + cost) {
                dist[to] = dist[from] + cost;
                parent[to] = from; // Retine predecesorul
                q.push(to);
            }
        }
    }

    // Afisarea rezultatelor
    if (last_updated != -1) {
        // Reconstructia ciclului negativ in caz de existenta
        int cycle_start = last_updated;
        for (int i = 0; i < n; ++i) {
            cycle_start = parent[cycle_start];
        }

        vector<int> cycle;
        int current = cycle_start;
        do {
            cycle.push_back(current);
            current = parent[current];
        } while (current != cycle_start);

        reverse(cycle.begin(), cycle.end());

        // Afisarea ciclului negativ
        g << "Ciclu negativ: ";
        for (int i = 0; i < cycle.size() - 1; i++) {
            g << cycle[i] << " ";
        }
        g << cycle_start << endl;
    } else {
        // Afisarea costurilor si a traseelor minime
        for (int i = 2; i <= n; i++) {
            if (dist[i] == INT_MAX) {
                dist[i] = 0; // Daca distanta este infinit, se considera 0
            }

            // Afisarea costului minim pentru fiecare nod
            g << " Cost : " << dist[i] ;

            // Reconstructia traseului minim de la nodul i la sursa
            vector<int> path;
            int current = i;
            while (current != 1) {
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(1); // Adaugarea nodului sursa
            reverse(path.begin(), path.end());

            // Afisarea traseului minim
            g << "Drum: ";
            for (int node : path) {
                g << node << " ";
            }
            g << '\n';
        }
    }

    return 0;
}


/*
 #include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> graf[50005];
int dist[50005];
int viz[50005];
int parent[50005]; // To remember the path

int n, m;
int remember_path[100];

ifstream f("tema3Lab/ford.in");
ofstream g("ford.out");

int main() {
    f >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, c;
        f >> x >> y >> c;
        graf[x].push_back({y, c});
    }

    fill(dist, dist + n + 1, INT_MAX);
    dist[1] = 0;
    queue<int> q;
    q.push(1);

    while (!q.empty()) {
        int from = q.front();
        q.pop();
        viz[from]++;
        if (viz[from] == n + 1) {
            g << "Ciclu negativ!";
            return 0;
        }
        for (auto &x : graf[from]) {
            int to = x.first;
            int cost = x.second;
            if (dist[to] > dist[from] + cost) {
                dist[to] = dist[from] + cost;
                parent[to] = from; // Remember the predecessor
                q.push(to);
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        if (dist[i] == INT_MAX) {
            dist[i] = 0;
        }
        g << dist[i] << ' ';

        // Reconstruct the path from node i to the source
        vector<int> path;
        int current = i;
        while (current != 1) {
            path.push_back(current);
            current = parent[current];
        }
        path.push_back(1); // Add the source node
        reverse(path.begin(), path.end());

        g << "Path to " << i << ": ";
        for (int node : path) {
            g << node << " ";
        }
        g << endl;
    }

    return 0;
}

 */