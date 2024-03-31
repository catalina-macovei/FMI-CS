//
// Created by Catalina Macovei on 24.01.2024.
//distanta intre 2 noduri u v:
// apel bfs(u), lant(v)
#include <iostream> //BFS
#include <vector>
#include <queue>

using namespace std;

int viz[1000];
int tata[1000], distanta[1000];
vector<int> G[1000];

int main ()
{
    int i, x, y;    // var auxiliare p/u citirea datelor
    int n, m, start;
    queue<int> Q;   // o coada
    int vecin, lim;  // vecin (nodului), lim - nr de vecini pentru iteratie

    /**     CITIRE INITIALIZARE     */
    cin >> n >> m;  // citesc nr noduri, muchii

    for(i = 0; i < m; i++) {
        cin >> x >> y;

        G[x].push_back(y);
        G[y].push_back(x);
    }

    cout << "Nod Start: ";
    cin >> start;

    //Initializez vectorul distanta, viz[start], dist[start]
    for(i = 0; i < n; i++) {
        distanta[i]=-1;
    }

    Q.push(start);
    viz[start] = 1;
    distanta[start] = 0;


    /**       BFS parcurgere        */
    cout << "Noduri BFS: " ;
    while(!Q.empty()) {

        x = Q.front(); Q.pop();     // x e radacina care o parcurg, sterg din coada

        cout << x << "\t";   //Afisare Noduri BFS

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

    cout<< "\nTata: ";
    for(i=1; i<=n; i++)
        cout << tata[i]<<" ";

    cout<< "\nDistanta: ";
    for(i=1; i<=n; i++)
        cout<<distanta[i]<<" ";

    return 0;
}

/*
INPUT
9 11
1 2
1 3
1 4
2 5
2 9
3 5
3 7
5 7
6 7
6 8
4 6
8 9
 * */