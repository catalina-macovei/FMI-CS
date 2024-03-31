//
// Created by Catalina Macovei on 24.11.2023.

//// DAG aciclic

#include <iostream>
#include <list>
#include <queue>
#include <utility>

using namespace std;

int dist[100000], tata[100000], start, grade[100000];

int main ()
{

    int i, n, m, x, y, pondere;
    list< pair<int, int>> graf[100000]; // graf[x]; 1 - y, 2 - pondere, xy -> muchie
    list<int> topologica;       // lista sortata topologic
    queue<int> Q;


    /**      CITIRE       **/
    cin >> n >> m; //n=nr noduri, m=nr muchii

    for(i = 0; i < m; i++)
    {
        cin >> x >> y >> pondere;
        graf[x].push_back({y, pondere});
        grade[y]++;
    }
    cout << "Nod Start: ";
    cin >> start;


    /**    INITIALIZARE     **/
    for(i = 1; i <= n; i++)
        dist[i] = 1000000, tata[i] = -1;

    tata[start] = 0;
    dist[start] = 0;

    for(i = 1; i <= n; i++)
        if( !grade[i] )
            Q.push(i);


    /** TOPOLOGICA + BFS **/
    while(!Q.empty())
    {
        x = Q.front();
        Q.pop();
        topologica.push_back(x);

        for(pair<int, int> p: graf[x]) //pt noduri adiacente
        {
            y = p.first;
            grade[y]--;

            if(!grade[y])
                Q.push(y);
        }
    }


    /**    Construim arborele -> distante , tata     **/
    for(int x: topologica)         // construim arborele -> distante , tata
        for(pair<int, int> p: graf[x])      // pentru fiecare vecin a lui -> x
        {
            y = p.first;
            pondere = p.second;

            if (dist[y] > dist[x] + pondere)
                dist[y] = dist[x] + pondere, tata[y] = x;
        }


    cout << "Vec Distante: ";
    for(i = 1; i <= n; i++)
        cout << dist[i] << "\t";

    cout << endl;

    cout << "Vec Tati: ";
    for(i = 1; i <= n; i++)
        cout << tata[i] << "\t";

    return 0;
}

/*  INPUT
7 9
1 2 8
1 3 1
1 4 2
3 2 4
2 6 3
3 5 6
4 5 5
6 5 2
5 7 6
 * */