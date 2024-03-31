//
// Created by Catalina Macovei on 21.02.2024.
//
#include <iostream> //BFS
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

int viz[100001];
int tata[100001], distanta[100001];
vector<int> G[100001];
vector<int> descend;

int i, x, y;    // var auxiliare p/u citirea datelor
int n, m, start, nod;
queue<int> Q;   // o coada
int vecin, lim;  // vecin (nodului), lim - nr de vecini pentru iteratie

void BFS()
{
    while(!Q.empty()) {

        x = Q.front(); Q.pop();     // x e radacina care o parcurg, sterg din coada

        lim=G[x].size();     // stabilesc nr de vecini
        for(i = 0; i < lim; i++)
        {
            vecin = G[x][i];

            if(!viz[vecin])     // daca vecinul nu a fost viz, il vizitez (push in coada)
            {
                tata[vecin] = x;    // tata vecinului va fi x de acum
                viz[vecin] = 1;     // vecinul a fost viz
                distanta[vecin] = distanta[x]+1;    //incrementez distanta !!!!! GRAFURI NEPONDERATE
                Q.push(vecin);
            }
        }
    }
}

int Reprez(int x) // Cautam Radacina Arbore - Reprez
{
    if (x == tata[x])
        return x;
    return Reprez(tata[x]);
}

int main ()
{
    /**     CITIRE INITIALIZARE     */
    cin >> n >> start >> nod;
    m = n - 1;

    assert(n >= 1 && n <= 100000);
    assert(start >= 1 && start <= 100000);
    assert(nod >= 1 && nod <= 100000);

    for(i = 0; i < m; i++) {
        cin >> x >> y;
        assert(x >= 1 && x <= n);
        assert(y >= 1 && y <= n);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    //Initializez vectorul distanta, viz[start], dist[start]
    for(i = 0; i < n; i++) {
        distanta[i]=-1;
    }

    Q.push(start);
    viz[start] = 1;
    distanta[start] = 0;


    /**       BFS parcurgere        */
    BFS();

    int lant = nod;

    vector<int> ascend;

    while (lant)
    {
        lant = tata[lant];
        if (lant != 0)
            ascend.push_back(lant);     /// adaug ascendentii
    }

    if (start == nod)
    {
        for(i = 0; i <= n; i++) {
            distanta[i]=-1;
            viz[i] = 0;
            tata[i] = 0;
        }

        Q.push(start);
        viz[start] = 1;
        distanta[start] = 0;
        while(!Q.empty()) {

            x = Q.front(); Q.pop();     // x e radacina care o parcurg, sterg din coada
            lim=G[x].size();     // stabilesc nr de vecini
            for(i = 0; i < lim; i++)
            {
                vecin = G[x][i];
                if(!viz[vecin])     // daca vecinul nu a fost viz, il vizitez (push in coada)
                {
                    descend.push_back(vecin); /// adaug descendentii nodului
                    //cout << vecin << " ";
                    tata[vecin] = x;    // tata vecinului va fi x de acum
                    viz[vecin] = 1;     // vecinul a fost viz
                    distanta[vecin] = distanta[x]+1;    //incrementez distanta !!!!! GRAFURI NEPONDERATE
                    Q.push(vecin);
                }
            }
        }
    }
    else
    {
        for (i = 1; i <= n ; i++)
        {
            if (tata[i] == nod)
            {
                descend.push_back(i);
            }
        }
    }

    if (ascend.size())
        for (int asc : ascend)
        {
            cout << asc << " ";
        }
    else
        cout << 0;

    cout << endl;

    if (descend.size())
        for (int desc : descend)
        {
            cout << desc << " ";
        }
    else
        cout << 0;


    return 0;
}

/*Input
 8 1 3
 1 2
 1 3
 3 7
 3 8
 2 4
 2 5
 5 6
 */