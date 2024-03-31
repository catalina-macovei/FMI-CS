//
// Created by Catalina Macovei on 28.10.2023.
// iesire: 3 4 1 5 2

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_N = 100005;

int n, m;
vector<int> vecini[MAX_N];
vector<int> grad_intrare(MAX_N, 0);
vector<int> ordine;

bool sortare_topologica() {
    queue<int> q;

    for (int i = 1; i <= n; i++) {
        if (grad_intrare[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int curs = q.front();
        q.pop();
        ordine.push_back(curs);

        for (int curs_urmator : vecini[curs]) {
            grad_intrare[curs_urmator]--;
            if (grad_intrare[curs_urmator] == 0) {
                q.push(curs_urmator);
            }
        }
    }

    return ordine.size() == n;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        vecini[a].push_back(b);
        grad_intrare[b]++;
    }

    if (sortare_topologica()) {
        for (int curs : ordine) {
            cout << curs << " ";
        }
        cout << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}

/** Problema   -- AICI DOAR SORTARE -> in sortareTopologicaB e raspunsul acestei probleme
 *  Modificați programul de la a) astfel încât în cazul în care nu pot fi urmate toate cursurile (deci se afișează IMPOSSIBLE),
 *  să afișeze și o listă de cursuri [c1, c2, …, ck, c1] care depind circular unele de altele (orice curs ci trebuie urmat
 *  înaintea cursului ci-1, iar ck înaintea cursului c1).
 * */

/* Input:
10 20
5 2
2 4
8 9
6 4
7 6
8 4
5 3
9 4
8 3
10 8
3 9
1 8
2 9
7 4
7 2
9 6
3 4
2 6
1 9
10 1
 */