//
// Created by Catalina Macovei on 24.01.2024.
//
//DFS - utilizari: Nr Componente Conexe, detectarea muchiilor critice
#include <iostream>
#include <vector>

using namespace std;

int tata[1000];
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
        {
            tata[vecin] = nod;
            DFS(vecin);
        }

    }
}

int main ()
{
    int n, m,nod, i, x, y, nr_cc_conexe = 0;   // n = nr noduri, m = nr muchii

    /**   Initializarea datelor    **/
    cin >> n >> m >> nod;
    m = 7;
    for(i = 0; i < m; i++)
    {
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    /** Acest apel e pentru o singura parcurgere  **/
    //DFS(1);

    //nodurile numerotate de la 1
    for(i = 1; i <= n; i++)  // pentru fiecare nod nevizitat -> parcurgere DFS
        if(!viz[i])
        {
            nr_cc_conexe++;    // nr componente conexe + 1
            DFS(i);
            cout << endl;
        }
    cout << "Nr Componente Conexe: " << nr_cc_conexe << endl;

    cout << "muchii: " << endl;
    for (i = 2; i<= n; i++)
    {
        cout << tata[i] << " ";
    }
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