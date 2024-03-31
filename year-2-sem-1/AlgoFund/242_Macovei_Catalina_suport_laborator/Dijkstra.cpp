//
// Created by Catalina Macovei on 24.11.2023.

/// Dijkstra

#include <iostream>
#include <fstream>
#include <set>
#include <list>
#include <utility>
using namespace std;

int main ()
{
    int n, m, start, x, y, i, pondere, tata[100000], dist[100000];

    cin >> n >> m;
    list< pair<int, int>> graf[100000]; // graful cu liste de adiacenta - vecinii

    /**    CITIRE     **/
    for(i = 0; i < m; i++) {
        cin >> x >> y >> pondere;
        graf[x].push_back({pondere, y});
        graf[y].push_back({pondere, x});
    }

    cout << "Nod Start: ";
    cin >> start;

    /**    INITIALIZARE     **/
    for(i = 1; i <= n; i++)
    {
        dist[i] = 1000000;  // inf
        tata[i]=0;
    }
    dist[start] = 0;

    set< pair<int, int>> Q;     // distanta, nod
    Q.insert({dist[start], start});


    /**    BFS DIJKSTRA     **/
    while(Q.size() > 0)
    {
        x = Q.begin()->second;  // nod
        Q.erase(Q.begin());     // poate fi si pop

        for(pair<int, int> elem: graf[x])   // pentru fiecare vecin
        {
            y = elem.second;
            pondere = elem.first;

            if(dist[y] > dist[x] + pondere)     // dc distanta e mai mare, o sterg din coada
            {
                Q.erase({dist[y], y});

                dist[y] = dist[x] + pondere;    // actualizez noua distanta
                tata[y] = x;                    // noul tata

                Q.insert({dist[y], y}); // push pe stiva
            }
        }
    }

    cout<<"Vec Distante: ";
    for(i = 1; i <= n; i++) cout << dist[i] << " ";
    cout << endl;

    cout << "Vec Tati: ";
    for(i = 1; i <= n; i++) cout << tata[i] << " ";
    cout<<endl;

    return 0;
}

/* INPUT
9 14
1 2 10
1 3 11
2 4 11
2 5 11
5 6 13
3 4 10
4 6 12
4 7 5
3 7 4
3 8 5
8 7 5
8 9 4
9 7 3
6 7 11
 * */