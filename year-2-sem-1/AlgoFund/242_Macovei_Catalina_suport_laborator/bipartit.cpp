//
// Created by Catalina Macovei on 28.10.2023.
// exemplu date iesire: 1 2 2 1 2
///  O n+m

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

const string FISIER_INTRARE = "pregatire_test/bipartit.in";  // Numele fișierului de intrare
const string FISIER_IESIRE = "pregatire_test/bipartit.out";  // Numele fișierului de ieșire

vector<vector<int>> vecini;  // Listă de adiacență pentru graful de prietenii
vector<int> culoare;        // Vector pentru colorarea nodurilor
int n, m;                    // Numărul de elevi și numărul de prietenii

// BFS
bool esteBipartit() {
    culoare.assign(n, -1);  // toate valorile initial sunt -1

    for (int start = 0; start < n; ++start) {   // trec prin toate nodurile
        if (culoare[start] == -1) {
            queue<int> coada;
            coada.push(start);
            culoare[start] = 0;     // marcheaza elem prin care am trecut cu 0

            while (!coada.empty()) { ////
                int u = coada.front();  // iau primul element din coada (care astat cel mai mult in coada)
                coada.pop();    //apoi ii elimin

                for (int v : vecini[u])   //trec prin vectorul de vecini a nodului eleiminat din coada
                    if (culoare[v] == -1) {   // vecin nevizitat
                        culoare[v] = 1 - culoare[u];    // marchez cu 2 (1-(-1))
                        coada.push(v);  // adaug vecinul vizitat in coada
                    } else if (culoare[v] == culoare[u]) {   // dc au aceeasi culoare, ex: 2==2 , atunci nu-i bipartit
                        return false;
                    }

            }
        }
    }

    return true;
}

int main() {
    ifstream fisier_intrare(FISIER_INTRARE);
    ofstream fisier_iesire(FISIER_IESIRE);

    fisier_intrare >> n >> m;       // nr noduri, muchii
    vecini.resize(n);   // dimensiunea vectorului = nr de noduri

    for (int i = 0; i < m; ++i) {           // iterez prin muchii = nr linii
        int a, b;
        fisier_intrare >> a >> b;
        vecini[a - 1].push_back(b - 1);     // scad 1, deoarece numar elementele in vector de la 0
        vecini[b - 1].push_back(a - 1);
    }

    if (esteBipartit()) {   // dc este bipartit, scriu in fisier
        for (int i = 0; i < n; ++i) {
            if (culoare[i] == 0) {
                fisier_iesire << "1 ";
            } else {
                fisier_iesire << "2 ";
            }
        }
        fisier_iesire << "\n";
    } else {
        fisier_iesire << "IMPOSIBIL\n";
    }

    fisier_intrare.close();
    fisier_iesire.close();

    return 0;
}
