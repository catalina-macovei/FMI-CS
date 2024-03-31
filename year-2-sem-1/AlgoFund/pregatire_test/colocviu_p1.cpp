//
// Created by Catalina Macovei on 18.02.2024.
//
/*
 * Se da un arbore cu n > 3 varfuri si varf s.
 * Informatiile se citesc cu structura:
 * prima linie este n
 * pe urmatoarele n linii - liste de adiacenta a lui G
 * linia i - incepe cu gradul, apoi vecinii urmati de cost
 * pe ultima linie varful s
 * pentru un lant p , capacitatea lant= cap minima unei muchii din p
 *p/u fecare varf capacitatea unui lant elemntar de la s la v , sub forma v: capacitate
 * */

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <queue>

//Prim Algorithm        O (m) complexitate in practica

using namespace std;

//distanta la cel mai apropiat vecin de s, tata, vf vizitate
int d[100], t[100], viz[100];

int main ()
{
    int n, m, s, i, j, x, y, c, nr_v;
    vector< pair<int, int>> Graf[100]; //liste de adiacenta

    cin>>n;
    for(i=1; i<=n; i++)
    {
        cin >> nr_v;
        while(nr_v)
        {
            cin >> x >> c;
            Graf[i].push_back({x, c});
            Graf[x].push_back({i, c});
            --nr_v;

            cout <<i <<"\t"<< x << " " << c << "\t";
        }
        cout << endl;
    }

    cin >> s;
    for(i = 0; i <= n; i++) d[i]=100000;    // initializare distanta
    d[s]=0;   // nod de start citit

    priority_queue< pair<int, int>> Q;
    Q.push({d[s], s});

    int minim = 100000;
    int index_min = 0;
    while(!Q.empty())
    {
        x=Q.top().second; //nod

        Q.pop();
        viz[x]++;
        for(auto i: Graf[x]) //vecinii lui x
        {
            y=i.first;
            j=i.second; // pondere/ capacit

            if(viz[y]==0)
            {
                t[y]=x;
                if (x != 1) {
                    d[y]= min ( d[y], min(j, d[x]));
                    if (minim > d[y])
                    {
                        minim = d[y];
                        index_min = y;
                    }

                } else
                {
                    d[y]= min ( d[y],j);
                }

                Q.push({d[y], y});
            }
        }
    }

    //Afisare
    for(i=1; i<=n; i++) cout<< i << ": " << d[i]<< endl;

    cout << "capacitate minima: " << d[index_min] << " ";
    cout << "pentru lantul: ";
    // afisare lant:
    while (index_min)
    {
        cout << index_min << " ";
        index_min = t[index_min];
    }
    return 0;
}

/*

6
2 2 3 3 2
2 1 3 4 6
3 1 2 5 1 6 3
1 2 6
1 3 1
1 3 3
1
 */