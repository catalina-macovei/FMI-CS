#include <iostream>
#include <list>
#include <queue>
#include <utility>
#include <cassert>

using namespace std;

int grad[100001];
int tati[100001];
list <int> lant;
list <int> topologica;
list <int> destinatii;
queue <int> Q;

list< pair<int, int>> graf[100001]; // 1 - y , 2 - pondere , xy -> muchie
int i, n, m, x, y, k;


void detectare_lant(int final)
{
    while (final != 0) {
        lant.push_back(final);
        final = tati[final];
    }
}

int main ()
{

    /**   Citire    **/
    cin >> n >> m >> k;

    assert(n >= 1 && n <= 100000);
    assert(k >= 1 && k <= n);
    assert(m >= 1 && m <= min(n*(n-1)/2,2*100000));

    for (i = 0; i < k; i++) // citire destinatii
    {
        cin >> x;
        if (x >= 1 && x <= n)
            (destinatii.push_back(x));
        else {
            return (42);
        }

    }

    for(i = 0; i < m; i++)  // citire graf
    {
        cin >> x >> y ;

        graf[x].push_back({y, 0});
        grad[y]++;
    }


    /**     INITIALIZARE    **/
    for(i = 1; i <= n; i++)     // grad intern = 0 -> push in coada
        if(!grad[i])        // dc gradul e 0
            Q.push(i);


    /**     BFS + topologica     **/
    while(!Q.empty())   // cat timp coada are elemente
    {
        x = Q.front();
        Q.pop();
        topologica.push_back(x);    // adaug nodul in sortare

        for(pair<int, int> p:graf[x])      // pentru fiecare vecin
        {
            y = p.first;    // y e vecin - copil
            tati[y] = x;
            grad[y]--;    // gradul scadem , deoarece x e deja examinat si eliminat din coada

            if(!grad[y])    // daca gradul lui y e 0
                Q.push(y);  // il adaug in coada
        }
    }


    if (topologica.size() != n)  {   // depinde de dimensiunea vectorului cu nr sortate
        cout << "\nGraful contine ciclu!!!" << endl;
        return 0;
    }


    /** Trebuie sa stabilesc care nodul final -> ultimul/penultimul din sortarea topologica */
   int final = 0;

   int lungimi[100001];

    // maxim lungimi
    int max = 0;
   for (int x : destinatii)
   {
       detectare_lant(x);
       lungimi[x] = lant.size();

       if (max < lungimi[x])
       {
           max = lungimi[x];
           final = x;
       }

       lant.clear();
   }



   detectare_lant(final);
   lant.reverse();
   cout << lungimi[final] - 1 << endl;

   for (int elem:lant)
   {
       cout << elem << " ";
   }

    return 0;
}

/*
5 5 2
4 5
1 3
1 4
1 2
4 5
2 4

10 10
2 5
4 5
4 8
6 10
7 1
7 2
7 4
7 5
7 6
8 5

 */