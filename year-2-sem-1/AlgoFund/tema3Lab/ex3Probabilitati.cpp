// Created by Catalina Macovei on 12.12.2023.
//O m log n
#include <iostream> // Dijkstra
#include <fstream>
#include <set>
#include <list>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

// Functie pentru afisarea drumului minim intre doua noduri
void printShortestPath(int start, int destination, int t[]) {
    cout << "Drum de siguranta de la " << start << " spre " << destination << ": ";
    vector<int> path;
    for (int v = destination; v != start; v = t[v]) {
        path.push_back(v);
    }
    path.push_back(start);

    reverse(path.begin(), path.end());

    // Afisarea caii
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1) {
            cout << "   ";
        }
    }
    cout << endl;
}

int main() {
    int n, m, p, i, t[100], d[100], st, x, y;
    ifstream fin("tema3Lab/retea.in");
    fin >> n >> m;
    list<pair<int, int>> L[100]; // Liste de adiacenta pentru a retine graful
    for (i = 0; i < m; i++) {
        fin >> x >> y >> p;
        L[x].push_back({p, y});
        L[y].push_back({p, x});
    }
    fin.close();

    // Initializarea vectorilor de distante si predecesori
    for (i = 1; i <= n; i++) {
        d[i] = 10000; // Valoare considerata infinit
        t[i] = 0;
    }

    cout << "Introduceti Nod Start: ";
    cin >> st;
    d[st] = 0;

    // Setul este folosit pentru a mentine "coada de prioritati"
    set<pair<int, int>> Q; // 1 int=d[x]=distanta; 2 int=eticheta nod
    Q.insert({d[st], st});

    // Algoritmul lui Dijkstra
    while (Q.size() > 0) {
        x = Q.begin()->second;
        Q.erase(Q.begin()); // Extragem nodul cu cea mai mica distanta

        // Actualizam distantele pentru fiecare vecin al nodului extras
        for (pair<int, int> it : L[x]) {
            y = it.second;
            p = it.first; // p=pondere

            // Daca gasim un drum mai scurt, actualizam distanta si predecesorul
            if (d[y] > d[x] + p) {
                Q.erase({d[y], y});
                d[y] = d[x] + p;
                t[y] = x;
                Q.insert({d[y], y});
            }
        }
    }

    int destinationNode = 7;
    printShortestPath(st, destinationNode, t);

    return 0;
}
