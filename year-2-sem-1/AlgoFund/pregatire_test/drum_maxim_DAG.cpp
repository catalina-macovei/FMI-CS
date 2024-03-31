//
// Created by Catalina Macovei on 24.11.2023.

//// DAG aciclic
/// pentru drum maxim

#include <iostream>
#include <list>
#include <queue>
#include <utility>

using namespace std;

int dist[100000], tata[100000], start, grade[100000];

int main ()
{

    int i, n, m, x, y, s,f, pondere;
    list< pair<int, int>> graf[100000]; // graf[x]; 1 - y, 2 - pondere, xy -> muchie
    list<int> topologica;       // lista sortata topologic
    queue<int> Q;
    list<int> starts, finals;


    /**      CITIRE       **/
    cin >> n >> m; //n=nr noduri, m=nr muchii

    for(i = 0; i < m; i++)
    {
        cin >> x >> y >> pondere;
        graf[x].push_back({y, pondere});
        grade[y]++;
    }

    cin >> s; // citesc nr de noduri start
    for (i =0 ; i < s; i++)
    {
        cin >> x;
        starts.push_back(x);
    }
    cin >> f; // nr noduri finale
    for ( i = 0; i< f; i++)
    {
        cin >> x;
        finals.push_back(x);
    }

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


    list <int> drum_final_final;
    int cost_f = 0;
    int fin;
    /**    Construim arborele -> distante , tata     **/
    for (int st : starts) {
        /**    INITIALIZARE     **/
        for(i = 1; i <= n; i++)
            dist[i] = -1000000, tata[i] = -1;

        tata[st] = 0;
        dist[st] = 0;


        for(int x: topologica)         // construim arborele -> distante , tata
            for(pair<int, int> p: graf[x])      // pentru fiecare vecin a lui -> x
            {
                y = p.first;
                pondere = p.second;

                if (dist[y] < dist[x] + pondere)
                    dist[y] = dist[x] + pondere, tata[y] = x;
            }

        for (int final : finals)
        {
            if (dist[final] > cost_f)
            {
                cost_f = dist[final];
                fin = final;
            }
        }

    }


    cout << dist[fin] << endl;
    while (fin && fin != -1)
    {
        drum_final_final.push_back(fin);
        fin = tata[fin];
    }

    drum_final_final.reverse();

    for ( int el :drum_final_final)
    {
        cout << el << " ";
    }
    return 0;
}

/*

7 9
5 1 9
3 1 7
3 2 15
1 2 11
1 6 1
6 4 16
6 7 8
2 7 4
7 4 2
2 3 5
2 6 7
 * */