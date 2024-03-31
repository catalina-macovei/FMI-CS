//
// Created by Catalina Macovei on 20.02.2024.
// DAG - graf orientat, fara circuite, implica costuri negative

// n m
// 3 nr - extremele  si ponderea
// ultima linnie - 2 noduri sursa
// determina dc exista un vf egal departat de s1 si s2
// dc exista mai multe , se afiseaza cel mai apropiat de cele 2 surse,
// cel cu d (s1, v) cea mai mica
// determina dc exista mai multe drumuri minime intre s1 si v
#include <iostream>
#include <list>
#include <queue>
#include <utility>

using namespace std;

int dists1[100000], tatas1[100000],dists2[100000], tatas2[100000], start, grade[100000];

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

    int s1, s2;
    cin >> s1 >> s2;

    /**    INITIALIZARE     **/
    for(i = 1; i <= n; i++)
    {

        dists1[i] = 1000000, tatas1[i] = -1;
        dists2[i]= 1000000, tatas2[i] = -1;
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


    /**    Construim arborele -> distante , tata     **/
    //
    int min = 10000000;
    int min_v = 1000;


    tatas1[s1] = 0;  // nodul de start curent
    dists1[s1] = 0;

    for(int x: topologica)         // construim arborele -> distante , tata
    {
        for(pair<int, int> p: graf[x])      // pentru fiecare vecin a lui -> x
        {
            y = p.first;
            pondere = p.second;

            if (dists1[y] > dists1[x] + pondere)
                dists1[y] = dists1[x] + pondere, tatas1[y] = x;
        }
    }

    tatas2[s2] = 0;  // nodul de start curent
    dists2[s2] = 0;


    for(int x: topologica)         // construim arborele -> distante , tata
    {
        for(pair<int, int> p: graf[x])      // pentru fiecare vecin a lui -> x
        {
            y = p.first;
            pondere = p.second;

            if (dists2[y] > dists2[x] + pondere)
                dists2[y] = dists2[x] + pondere, tatas2[y] = x;
        }
    }
    for(i = 1; i <= n; i++)
    {
        if (dists1[i] == dists2[i])
        {
            if (min > dists1[i])
            {
                min = dists1[i];
                min_v = i;
            }
        }
    }
    cout << "Vec Distante: ";

    if (min < 10000000)
        cout << s1 << " " << min_v << " = " << s2 << " " << min_v << "-->" << min << endl;
    else
        cout << "nu exista";
    cout << endl;
    // lant v - s1
    cout << "lant v - s1:" << endl;
    vector<int> min_drum1 ;
    int v = min_v;
    while(min_v)
    {
        min_drum1.push_back(min_v);
        cout << min_v << " ";
        min_v = tatas1[min_v];

    }
    for(i = 1; i <= n; i++) {

        dists1[i] = 1000000, tatas1[i] = -1;
    }
    // construim al 2-lea arbore
    tatas1[s1] = 0;  // nodul de start curent
    dists1[s1] = 0;


    for (int elem: min_drum1)
    {
        for(int x: topologica)         // construim arborele -> distante , tata
        {
            for(pair<int, int> p: graf[x])      // pentru fiecare vecin a lui -> x
            {

                y = p.first;
                pondere = p.second;

                if (y == elem)
                {
                    pondere = 1000000000; // infinit
                }

                if (dists1[y] > dists1[x] + pondere)
                    dists1[y] = dists1[x] + pondere, tatas1[y] = x;
            }
        }
    }
    cout << "min drum 2" << endl;
    while(v)
    {
        //min_drum1.push_back(min_v);
        cout << v << " ";
        v = tatas1[v];
    }



    cout << "Vec Tati: ";
    for(i = 1; i <= n; i++)
        cout << tatas1[i] << "\t";



    return 0;
}

/*
 8 11
 1 2 10
 2 3 -3
 1 3 7
 3 8 2
 3 4 1
 4 8 1
 5 1 1
 5 3 9
 5 6 3
 6 7 1
 7 4 4
 1 5
 */