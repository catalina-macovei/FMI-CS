//
// Created by Catalina Macovei on 29.10.2023.
// Un punct de articulație este un nod într-un graf pentru
// care eliminarea sa poate diviza graful în două componente neconexe.
/*
Input:
3 3
1 2
2 3
1 3
6 8
1 3
6 1
6 3
4 1
6 4
5 2
3 2
3 5
0 0

 //radacina este punct de articulatie dc are cel putin 2 fii
 // dc are un fiu low > nivelul sau
Output:
0
1
*/
/// complexitate O n+m
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 10005;

vector<int> graf[MAXN];     // lista de adiacenta
vector<int> low(MAXN);  // timpul minim de discoperire
vector<int> timp_discoperire(MAXN);     // timpul de discoperire pentru fiecare nod
vector<bool> este_punct_articulatie(MAXN);  // vector cu punctele de articulatie
int timer = 0;  // contor pentru timp
int nr_articulatie = 0;   // nr puncte de articulatie gasite

// dfs, complex: O(n + m)
void gaseste_puncte_articulatie(int nod, int parinte, vector<bool> &vizitat) {
    vizitat[nod] = true;    // marchez nodul ca vizitat
    timp_discoperire[nod] = low[nod] = timer++; // incrementez contorul timp pentru fiecare nod si stochez in vectorul de timpi
    int fii = 0;    // nr de fii ai nodului
    bool este_punct = false;    // innitializez var dc este punct cu FALSE

    for (int vecin : graf[nod]) {   // pentru toti vecinii
        if (vecin == parinte) { // dc vecinul este acelasi nod il omit
            continue;
        }

        if (!vizitat[vecin]) {  // dc nu a fost vizitat
            fii++;  // atunci vecinul este fiu
            gaseste_puncte_articulatie(vecin, nod, vizitat);    // verific dc e ounct de articulatie
            low[nod] = min(low[nod], low[vecin]);   // gradul sau devine minimul dintre (grad vecin , propriul grad)

            if (low[vecin] >= timp_discoperire[nod]) {  // dc timpul care am descoperit vecinul fiu > timpul descoperirii nodului
                este_punct = true;  // e punct de articulatie
            }
        } else {
            low[nod] = min(low[nod], timp_discoperire[vecin]);  // atltfel, reinitializez valoarea timpului min de descoperire a nodului
        }
    }

    if ((parinte == -1 && fii > 1) || (parinte != -1 && este_punct)) {
        este_punct_articulatie[nod] = true;
        nr_articulatie++; // maresc nr de pct de articulatie
    }
}

int main() {
    int N, M;   // nr noduri, nr muchii

    while (true) {
        cin >> N >> M;
        if (N == 0 && M == 0) {
            break;
        }

        for (int i = 1; i <= N; i++) {
            graf[i].clear();
            low[i] = 0;
            timp_discoperire[i] = 0;
            este_punct_articulatie[i] = false;
        }

        timer = 0;
        nr_articulatie = 0;

        //citesc graful
        for (int i = 0; i < M; i++) {
            int Ui, Vi;
            cin >> Ui >> Vi;
            graf[Ui].push_back(Vi);
            graf[Vi].push_back(Ui);
        }

        // dupa ce am facut toate initializarile,
        vector<bool> vizitat(N + 1, false);
        for (int i = 1; i <= N; i++) {
            if (!vizitat[i]) {  // vizitez toate nodurile si le verific
                gaseste_puncte_articulatie(i, -1, vizitat);
            }
        }

        cout << "\n" << nr_articulatie << endl;   // nr punctelor de articulatie
    }

    return 0;
}
