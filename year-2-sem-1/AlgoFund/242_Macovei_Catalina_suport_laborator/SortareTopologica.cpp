//
// Created by Catalina Macovei on 24.11.2023.
//// Sortare Topologica

#include <iostream>
#include <list>
#include <queue>
#include <utility>

using namespace std;

int grad[100];

int main ()
{
    list< pair<int, int>> graf[100]; // 1 - y , 2 - pondere , xy -> muchie
    int i, n, m, x, y, pondere;

    list <int> topologica;
    queue <int> Q;

    /**   Citire    **/
    cin >> n >> m;
    for(i = 0; i < m; i++)
    {
        cin >> x >> y >> pondere;

        graf[x].push_back({y, pondere});
        grad[y]++;
    }


    /**     INITIALIZARE    **/
    for(i=1; i<=n; i++)     // grad intern = 0 -> push in coada
        if(!grad[i])
            Q.push(i);


    /**     BFS + topologica     **/
    while(!Q.empty())
    {
        x = Q.front();
        Q.pop();

        topologica.push_back(x);
        for(pair<int, int> p:graf[x])      // pentru fiecare vecin
        {
            y = p.first;
            grad[y]--;

            if(!grad[y])
                Q.push(y);
        }
    }


    if(topologica.size() != n)  {   // depinde de dimensiunea vectorului cu nr sortate
        cout << "\nGraful contine ciclu!!!" << endl;

        return 0;
    }

    for(int x: topologica)
        cout << x << "\t"; // afisare nr sortate

    return 0;
}

/*  INPUT
7 9
1 2 8
2 1 7
1 3 1
1 4 2
3 2 4
2 6 3
3 5 6
4 5 5
6 5 2
5 7 6
 * */