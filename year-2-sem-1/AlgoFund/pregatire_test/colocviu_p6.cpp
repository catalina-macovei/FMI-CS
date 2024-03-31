//
// Created by Catalina Macovei on 29.10.2023.
// Un punct de articulație este un nod într-un graf pentru
// care eliminarea sa poate diviza graful în două componente neconexe.
// Un nod se numeşte punct de articulaţie dacă subgraful obţinut prin eliminarea nodului şi a muchiilor incidente cu acesta nu mai este conex
// componenta biconexa = nu are pct de articulatie
/// complexitate O n+m
/*
 Problema:
 Se afiseaza punctele critice in care nu sunt incidente muchii critice.
 Pentru  fiecare astfel de punct se va afisa nr de componente biconexe ale grafului
 - citire
 pe 1 linie sunt n si m
 pe urm linii sunt cate 2 nr naturale reprezentand extremitratile unei muchii
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 10005;

// pentru muchii critice
vector<vector<int>> cicluri;
vector<int> elem_cicluri;
int nrCicluri = 0;
int color[MAXN];
int tata[MAXN];

// pentru puncte critice
vector<int> graf[MAXN];
vector<int> low(MAXN);  // timpul minim de discoperire
vector<int> timp(MAXN);     // timpul de discoperire pentru fiecare nod
vector<int> pct_art;
int viz[10000];

int timer = 0;  // contor pentru timp
int nr_articulatie = 0;   // nr puncte de articulatie gasite

// dfs, complex: O(n + m)
void dfs_articulatie(int nod, int parinte) {
    int nr_fii = 0; bool este_punct = false;

    viz[nod] = 1;
    timp[nod] = low[nod] = timer++;     // actualizare timp

    for (int vecin : graf[nod])
    {
        if (vecin == parinte)  // dc vecinul este acelasi nod il omit
            continue;

        if (!viz[vecin])
        {
            nr_fii++;  // atunci vecinul este fiu

            dfs_articulatie(vecin, nod);
            low[nod] = min(low[nod], low[vecin]);   // gradul sau devine minimul dintre (grad vecin , propriul grad)

            if (low[vecin] >= timp[nod])   // dc timpul care am descoperit vecinul fiu > timpul descoperirii parinte
                este_punct = true;
        }
        else
        {
            low[nod] = min(low[nod], timp[vecin]);  // atltfel, reinitializez valoarea timpului min de descoperire a nodului
        }
    }

    if ((parinte == -1 && nr_fii > 1) || (parinte != -1 && este_punct))  // parinte neviz vs parinte viz
    {
        pct_art.push_back(nod);
        nr_articulatie++; // maresc nr de pct de articulatie
    }
}

void dfs_cycle(int u, int p)
{
    // nod complet vizitat
    if (color[u] == 2) {    // negru = vizitat
        return;
    }

    // nodul gri -> posibil ciclu , adica muchie de intoarcere
    // backtrack pe tata pentru a gasi toate nodurile
    if (color[u] == 1) {    // gri == in proces de explorare
        vector<int> tempv;
        nrCicluri++;

        int curent = p;
        tempv.push_back(curent);
        elem_cicluri.push_back(curent);
        // backtrack the vertex which are
        // in the current cycle thats found
        while (curent != u) {
            curent = tata[curent];
            tempv.push_back(curent);
            elem_cicluri.push_back(curent);
        }
        cicluri.push_back(tempv);
        return;
    }
    tata[u] = p;

    // partially visited.
    color[u] = 1;

    // simple dfs on graph
    for (int v : graf[u]) {

        // if it has not been visited previously
        if (v == tata[u]) {
            continue;
        }
        dfs_cycle(v, u);
    }

    // finalizat
    color[u] = 2;
}


int main() {
    int N, M, Ui, Vi;   // nr noduri, nr muchii

    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        cin >> Ui >> Vi;
        graf[Ui].push_back(Vi);
        graf[Vi].push_back(Ui);
    }

    /**     Initializari    */
    for (int i = 1; i <= N; i++)
    {
        low[i] = 0;
        timp[i] = 0;
    }

    timer = 0;
    nr_articulatie = 0;


    /**     DFS  pct critice   */
    for (int i = 1; i <= N; i++)
    {
        if (!viz[i])
            dfs_articulatie(i, -1);
    }

    /**     DFS  muchii critice/cicluri   */
    dfs_cycle(1, 0);

    vector<int> vf_muchii_crt;

    for (int i=1; i<= N; i++)
    {
        for (int v : graf[i])
        {
            auto it = find(elem_cicluri.begin(), elem_cicluri.end(), v);
            if (it == elem_cicluri.end())
                vf_muchii_crt.push_back(i), vf_muchii_crt.push_back(v);

        }
    }

    /**     Afisare     */
    cout << "\nPuncte fara muchii critice incidente: " << endl;
    for (int pct : pct_art)
    {
        int c = 0;
        auto it = find(vf_muchii_crt.begin(), vf_muchii_crt.end(), pct);
        if (it == vf_muchii_crt.end())
        {
            cout << pct << endl;

            for (auto ciclu : cicluri)
            {
                auto it1 = find(ciclu.begin(), ciclu.end(), pct);
                if (it1 != ciclu.end())
                {
                    ++c;
                }
            }
            cout << "Nr componente biconexe: " << c << endl;
        }


    }

    cout << "\nNr total puncte: " << nr_articulatie << endl;   // nr punctelor de articulatie

    cout << "Toate punctele: " << endl;
    for (int pct : pct_art)
    {
        cout << pct << endl;
    }

    return 0;
}

/*
 *
11 14
 1 2
 1 3
 2 3
 1 4
 1 5
 4 5
 5 6
 1 7
 7 8
 1 8
 4 9
 9 10
 10 4
 9 11
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