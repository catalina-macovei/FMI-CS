//
// Created by Catalina Macovei on 17.01.2024.
//
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10001;

// O mn2

int n;
vector<int> inDegree(MAXN), outDegree(MAXN), indegreeSum(MAXN), outdegreeSum(MAXN);
vector<vector<int>> graph(MAXN, vector<int>(MAXN));

ifstream f("tema4Lab/secvente.in");
ofstream g("tema4Lab/secvente.out");

// Functia constructGraph face constructia grafului in functie de gradele de intrare si iesire ale nodurilor
void constructGraph() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (indegreeSum[i] > 0 && outdegreeSum[j] > 0) {
                // Adaugam arce in graful rezultat, minimul dintre gradele de intrare si iesire ale nodurilor
                graph[i][j] = min(inDegree[i], outDegree[j]);
                indegreeSum[i] -= graph[i][j];
                outdegreeSum[j] -= graph[i][j];
            }
        }
    }
}

int main() {
    f >> n;

    for (int i = 1; i <= n; ++i) {
        f >> inDegree[i];
        indegreeSum[i] = inDegree[i];
    }

    for (int i = 1; i <= n; ++i) {
        f >> outDegree[i];
        outdegreeSum[i] = outDegree[i];
    }

    // Verificare dacă secvențele pot forma un graf
    if (accumulate(inDegree.begin(), inDegree.end(), 0) != accumulate(outDegree.begin(), outDegree.end(), 0)) {
        g << "NU";  // Mesajul "NU" în caz negativ
        return 0;
    }

    constructGraph();

    // Afișare arcele grafului
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= graph[i][j]; ++k) {
                g << i << ' ' << j << '\n';
            }
        }
    }

    return 0;
}
