//
// Created by Catalina Macovei on 24.01.2024.
//
//DFS - utilizari: Nr Componente Conexe, detectarea muchiilor critice
#include <iostream>
#include <vector>

using namespace std;


int viz[1000]; //nodurile vizitate
vector<int> G[1000]; //graful neorientat


void DFS(int nod)   // parcurgerea in adancime DFS
{
    int i, lim = 0, vecin;  // declar variabilele si initializez, lim = nr vecini
    lim = G[nod].size();
    viz[nod] = 1;

    cout << nod << "\t";     // Afisarea noduri in timpul DFS

    for(i = 0; i < lim; i++)    // Pentru fiecare vecin nevizitat -> DFS
    {
        vecin = G[nod][i];
        if(viz[vecin] == 0)
            DFS(vecin);
    }
}

int main ()
{
    int n, m, i, x, y, nr_cc_conexe = 0;   // n = nr noduri, m = nr muchii

    /**   Initializarea datelor    **/
    cin >> n >> m;
    for(i = 0; i < m; i++)
    {
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    /** Acest apel e pentru o singura parcurgere  **/
    //DFS(nod_start);

    //nodurile numerotate de la 1
    for(i = 1; i <= n; i++)  // pentru fiecare nod nevizitat -> parcurgere DFS
        if(!viz[i])
        {
            nr_cc_conexe++;    // nr componente conexe + 1
            DFS(i);
            cout << endl;
        }
    cout << "Nr Componente Conexe: " << nr_cc_conexe << endl;

    return 0;
}
/*
10 5 2
2 6
4 6
4 9
4 10
8 10

 */