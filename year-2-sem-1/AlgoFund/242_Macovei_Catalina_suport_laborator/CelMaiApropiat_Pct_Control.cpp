//
// Created by Catalina Macovei on 24.11.2023.
//
// Conditie: calculez distanta de la nod start la cel mai apropiat punct de control

#include <iostream>
#include <fstream>
#include <list>
#include <utility>
#include <queue>
using namespace std;

int pred[100000], dist[100000]; // predecesor, distanta
bool verificat[100000];     // vector care marcheaza punctele de control

int main()
{
    int n, m, x, y, i;  // nr noduri, muchii, var auxiliare x, y , i

    list< pair<int, int>> edges;
    list<int> graf[100000];

    /**    Initializare Date     **/
    cin >> n >> m;
    for(i = 0; i < m; i++)
    {
        cin >> x >> y;
        edges.push_back({x, y});
        graf[x].push_back(y);
    }

    /**    Puncte de control     **/
    cin >> x >> y;      // punctele de control pe ultima linie, citim si marcam
    verificat[x] = true;

    //Lista de Muchii - edges
   /* cout << "Lista de Muchii:\n";
    for(pair<int, int> p:E) cout << p.first<< " " << p.second << '\n';
    cout << endl; */

    int start;
    cout << "Nod Start: ";
    cin >> start;

    queue<int> Q;
    Q.push(start);      // singurul nod din coada
    pred[start] = -1;   // predecesor nu are -> -1
    dist[start] = 0;       // distanta -> 0


    /**    BFS     **/
    while(!Q.empty())   // parcurgere BFS
    {
        x = Q.front();
        Q.pop();

        if(verificat[x]) break;     // dc e punct de control, nu mai parcurg, nu ma intereseaza

        for(int j: graf[x])     // p/u fiecare vecin
            if( !pred[j] )    // dc nu i-am vizitat predecesorul, adica e 0
            {
                pred[j] = x;    // dau valoare predecesorului / tatalui
                dist[j] = dist[pred[j]]+1;      // actualizam distanta, de la predecesor + 1 nod
                Q.push(j);      // continui cu vizitarea vecinului
            }
    }

    cout << "Cel mai apropiat punct de control: " << x << endl; // din nodul de start

    cout << "Distanta: " << dist[x] << endl;

    list<int> distanta;
    while(x != -1) {
        distanta.push_front(x);  // distanta = nr de noduri prin care a trecut
        x = pred[x];
    }

    cout << "Drum: ";
    for(int j: distanta)
        cout<< j << " ";

    cout<<endl;

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