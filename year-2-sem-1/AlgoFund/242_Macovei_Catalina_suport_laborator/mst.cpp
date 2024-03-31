//
// Created by Catalina Macovei on 02.12.2023.
// ultim ex
// Al doilea arbore de acoperire minima cu multimi disjuncte
#include <bits/stdc++.h>

using namespace std;

struct DSet {  // structura disjoint set
    int n;
    vector<int> link, count;

    DSet(int n) : n(n), count(n, 1), link(n, -1) {}

    int root(int a) {
        if (link[a] == -1) return a;
        int radacina = root(link[a]);
        // "path compression"
        link[a] = radacina;

        return radacina;
    }

    bool Connected(int a, int b) {
        return root(a) == root(b);
    }


    void Link(int a, int b) {
        a = root(a); b = root(b);
        if (count[a] > count[b])
            swap(a, b);

        // b devine tata lui a
        link[a] = b;
        count[b] += count[a];
    }
};

struct Graph {
    struct Edge {
        int a, b, c;
        Edge(int a, int b, int c) : a(a), b(b), c(c) {}

        bool operator<(const Edge& oth) const {
            return c < oth.c;
        }
    };

    int n;
    vector<Edge> edges;
    vector<Edge> mst_edges;

    Graph(int n) : n(n) {}

    void AddEdge(int a, int b, int c) {
        edges.emplace_back(a, b, c);
    }

    long long ComputeMST() {
        // 1. sortam muchiile.
        sort(edges.begin(), edges.end());

        // 2. pentru fiecare muchie in ordine,
        DSet ds(n);
        long long answer = 0;
        for (auto e : edges) {
            // daca conecteaza cc diferite, o adaugam la raspuns.
            // se testeaza de m ori
            if (!ds.Connected(e.a, e.b)) {
                answer += e.c;
                // se apeleaza de maxim n - 1 ori
                ds.Link(e.a, e.b);
                mst_edges.push_back(e);
            }
        }
        return answer;
    }

    // Calculează al doilea cel mai mic cost pentru Arborele de Acoperire Minimă (MST)
    long long ComputeSecondMST() {
        // Inițializăm costul celui de-al doilea cel mai mic arbore ca fiind infinit
        long long second_cheapest_cost = LLONG_MAX;

        // Iterăm peste fiecare muchie din arborele de acoperire minimă original
        for (auto& excluded_edge : mst_edges) {
            // Inițializăm un nou DS (Sistem Disjunct) pentru a reprezenta noul arbore
            DSet second_ds(n);
            // Costul curent pentru noul arbore
            long long current_cost = 0;

            // Iterăm peste fiecare muchie din lista originală de muchii
            for (auto& e : edges) {
                // Excludem muchia pentru care calculăm al doilea cel mai mic cost
                if (e.a != excluded_edge.a || e.b != excluded_edge.b) {
                    // Verificăm dacă muchia nu face deja parte din arborele secundar și o adăugăm în caz contrar
                    if (!second_ds.Connected(e.a, e.b)) {
                        current_cost += e.c;
                        second_ds.Link(e.a, e.b);
                    }
                }
            }

            // Verificăm și actualizăm costul minim al arborelui secundar
            if (current_cost < second_cheapest_cost && second_ds.count[second_ds.root(0)] == n) {
                second_cheapest_cost = current_cost;
            }

        }

        // Returnăm cel de-al doilea cel mai mic cost al arborelui de acoperire minimă
        return second_cheapest_cost;
    }

};

int main() {

    int n, m; cin >> n >> m;
    Graph G(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c; --a; --b;
        G.AddEdge(a, b, c);
    }
    cout << G.ComputeMST() << endl;
    cout << G.ComputeSecondMST() << endl;

    return 0;
}

/**testrae
 *
4 4
1 2 2
1 4 5
1 3 4
2 3 3
 * */