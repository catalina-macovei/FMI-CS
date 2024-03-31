//
// Created by Catalina Macovei on 23.01.2024.
//
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

int viz[100001] = {0};
vector<int> graf[100001]; //graful neorientat

int counter = 0;

void DFS(int nod)
{
    int nr_vecini = 0, vecin = -1;
    counter++;
    viz[nod] = 1;
    nr_vecini = graf[nod].size();
    //cout << nod << " ";
    for(int i = 0; i < nr_vecini; i++) //pt toti vecinii nodului
    {
        vecin = graf[nod][i];

        if(viz[vecin] == 0)
            DFS(vecin);
    }

}

int main ()
{
    int n, m, k; //n=nr noduri, m=nr muchii, nr min noduri per componenta

    cin >> n >> m >> k; //citesc datele
    int i, x, y, nr_conexe=0;

    // gestionarea limitelor
    assert(n >= 1 && n <= 100000);
    assert(k >= 1 && k <= 100000);
    assert(m >= 1 && m <= min(n*(n-1)/2,2*100000));

    //Initializare graf neorientat
    for(i = 0; i < m; i++)
    {
        cin >> x>> y;
        graf[x].push_back(y);
        graf[y].push_back(x);
    }

    //cout << "componente: " << endl;
    //parcurgere
    for(i = 1; i <= n; i++)
        if(!viz[i])
        {
            if (counter >= k) {
                nr_conexe++;
            }
            counter = 0;
            DFS(i);
            //cout << endl;
        }

    cout << nr_conexe << endl;

    return 0;
}

/*CERINTA
 Se considera un graf neorientat cu N noduri si M muchii.
 Sa se determine cate componente conexe ale acestui graf au cel putin k noduri.

Input Format:
Programul citeste de la tastatura valorile lui N M K si apoi M perechi reprezentand muchiile grafului.
Nodurile grafului sunt numerotate de la 1 la N.


10 5 2
2 6
4 6
4 9
4 10
8 10
 */
