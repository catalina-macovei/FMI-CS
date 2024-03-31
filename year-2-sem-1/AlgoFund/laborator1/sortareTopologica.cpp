//
// Created by Catalina Macovei on 28.10.2023.
// sortare topologică a unui graf orientat aciclic
// iesire: 3 4 1 5 2
//testare:
//6 7
//1 2
//1 3
//2 4
//3 4
//3 5
//4 6
//5 6

/// Complexit O (n+m)
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_N = 100005;

int n, m;
vector<int> vecini[MAX_N];  //vectorul de vecini
vector<int> grad_intrare(MAX_N, 0);     // nr de muchii de intrare, adică numărul de muchii care se termină într-un nod  initial toate valorile sunt 0
vector<int> ordine_elem;

//bfs
bool sortare_topologica() {
    queue<int> q;   //

    for (int i = 1; i <= n; i++) {  // numar de la 1 pana la nr de noduri n
        if (grad_intrare[i] == 0) { // daca e 0 inseamna ca nu am accesat nodul i
            q.push(i);  // il adaug in coada
        }
    }

    while (!q.empty()) {    // dc coada nu e goala
        int curs = q.front();   // folosesc ultimul element din coada,
        q.pop();    //  apoi il elimin
        ordine_elem.push_back(curs); // pastrez ordinea elementelor in vectorul ordine

        for (int curs_urmator : vecini[curs]) { // vizitez vecinii
            grad_intrare[curs_urmator]--;   // marchez gradul de intrare
            if (grad_intrare[curs_urmator] == 0) {  // dc gradul a devenit 0,
                q.push(curs_urmator);       // il adaug in coada
            }
        }
    }

    return ordine_elem.size() == n;  // daca am ordonat toate elementele
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {   // iterez prin toate muchiile grafului
        int a, b;
        cin >> a >> b;
        vecini[a].push_back(b);     // pentru fiecare nod, ii adaug vecinul
        grad_intrare[b]++;  // gradul de intrare a vecinului se mareste cu 1 decat nodul sau parinte
    }
    cout << endl;
    if (sortare_topologica()) {     // dc am ordonat  elementele
        for (int curs : ordine_elem) {   // le afisez
            cout << curs << " ";
        }
        cout << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}

