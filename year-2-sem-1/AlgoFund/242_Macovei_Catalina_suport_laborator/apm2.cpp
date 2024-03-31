//
// Created by Catalina Macovei on 02.12.2023.
// Graf dinamic KRUSKAL
#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000;    // inf

//  o structura Disjoint Set
struct DSet {
    int n; // noduri
    vector<int> link, count, cost; // Vectori pentru legături, numărul de elemente într-un grup și costul

    DSet(int n) : n(n), count(n, 1), link(n, -1), cost(n, INF) {} // Constructor pentru inițializare

    // Funcție pentru returnarea rădăcinii
    int root(int a) {
        while (link[a] != -1) a = link[a];
        return a;
    }

    // Funcție pentru verificarea dacă două noduri sunt conectate prin radacina
    bool Connected(int a, int b) {
        return root(a) == root(b);
    }

    // Funcție pentru reuniune ponderata și actualizarea structurii de date
    void Link(int a, int b, int c) {
        a = root(a); b = root(b);
        if (count[a] > count[b])
            swap(a, b);
        link[a] = b;
        cost[a] = c;
        count[b] += count[a];
    }

    // Funcție pentru rezolvarea cerinței
    int Solve(int a, int b) {   // sortare in ord cresc
        int answer = 0;
        while (a != b) {
            if (count[a] > count[b]) swap(a, b);
            answer = max(answer, cost[a]);
            a = link[a];
        }
        return answer;
    }
};

// Structura pentru gestionarea unui graf
struct Graph {
    struct Edge {
        int a, b, c;
        Edge(int a, int b, int c) : a(a), b(b), c(c) {}

        bool operator<(const Edge& oth) const {
            return c < oth.c;
        }
    };

    int n; // Numărul de noduri
    vector<Edge> edges; // Vector pentru stocarea muchiilor
    vector<Edge> mst_edges; // Vector pentru stocarea muchiilor din arborele minim de acoperire
    DSet ds; // Structura de date pentru Disjoint Set

    Graph(int n) : n(n), ds(n) {} // Constructor pentru inițializare

    // Funcție pentru adăugarea unei muchii în graf
    void AddEdge(int a, int b, int c) {
        edges.emplace_back(a, b, c);
    }

    // Funcție pentru calculul arborelui minim de acoperire și returnarea costului total
    long long ComputeMST() {
        sort(edges.begin(), edges.end());
        long long answer = 0;
        for (auto &e : edges) {
            if (!ds.Connected(e.a, e.b)) {
                answer += e.c;
                ds.Link(e.a, e.b, e.c);
                mst_edges.push_back(e);
            }
        }
        return answer;
    }

    // Funcție pentru rezolvarea cerinței prin găsirea maximului de pe calea dintre doi noduri
    int Solve(int u, int v) {
        return ds.Solve(u, v);
    }
};

int main() {

    int n, m, q;
    cin >> n >> m >> q; // Citirea datelor de intrare
    Graph G(n); // Inițializarea grafului cu n noduri

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b; // Citirea muchiilor
        G.AddEdge(a, b, c); // Adăugarea muchiilor în graf
    }

    cout << endl;
    G.ComputeMST(); // Calculul arborelui minim de acoperire

    // Rezolvarea
    for (int i = 0; i < q; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        cout << G.Solve(u, v) - 1 << '\n'; // Scrierea rezultatelor în fișierul de ieșire
    }

    return 0;
}

/*INPUT
 *
4 3 2
1 2 7
1 3 2
1 4 1
2 3
3 4
 */

/*
 * N, M, şi Q. Fiecare dintre următoarele M linii va descrie câte un drum prin trei numere întregi:
 * X, Y, cele două oraşe legate de drumul respectiv şi T, taxa asociată acestuia.
 * Fiecare dintre următoarele Q linii va descrie câte un drum adăugat de Marele Lider,
 * prin două numere, A şi B reprezentând cele două oraşe legate de drumul respectiv.
 * */