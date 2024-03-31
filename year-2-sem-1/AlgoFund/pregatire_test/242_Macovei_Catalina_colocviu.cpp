#include <iostream> //BFS
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

int viz[100000];
int tata[100000], distanta[100000];
vector<int> G[100000];
vector<int> apcm1[100000];
vector<int> apcm2[100000];

void DFS(int nod)   // parcurgerea in adancime DFS
{
    int i, nr_vecini = 0, vecin;  // declar variabilele si initializez, lim = nr vecini

    nr_vecini = G[nod].size();
    viz[nod] = 1;

    // cout << nod << " ";     // Afisarea noduri in timpul DFS

    for(i = 0; i < nr_vecini; i++)    // Pentru fiecare vecin nevizitat -> DFS
    {
        vecin = G[nod][i];
        if(viz[vecin] == 0)
        {
            apcm2[nod].push_back(vecin);
            apcm2[vecin].push_back(nod);
            DFS(vecin);

        }

    }
}


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

    // gestionarea limitelor
    assert(n >= 1 && n <= 100000);
    assert(m >= 1 && m <= min(n*(n-1)/2,2*100000));

    start = 1;

    //Initializez vectorul distanta, viz[start], dist[start]
    for(i = 0; i < n; i++) {
        distanta[i]=-1;
        viz[i] = 0;
    }

    Q.push(start);
    viz[start] = 1;
    distanta[start] = 0;


    /**       BFS parcurgere        */
    //cout << "Noduri BFS: " ;
    int count_muchii = 0;
    while(!Q.empty()) {

        x = Q.front(); Q.pop();     // x e radacina care o parcurg, sterg din coada

        //cout << x << "\t";   //Afisare Noduri BFS

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
                count_muchii++;
                apcm1[x].push_back(vecin);
                apcm1[vecin].push_back(x);
            }
        }
    }

    // reinitializare pentru dfs
    for(i = 0; i <= n; i++) {
        distanta[i]=-1;
        viz[i] = 0;
    }
    distanta[start] = 0;

    /// viz[start] = 1; nu mai este nevoie de marcarea start ca vizitat la dfs !!!!!!!!!

    // parcure
    for (i = 0; i <= n; i++)
    {
        if (!viz[i])
        {
            DFS(i);
        }
    }


    /// afisare
    if (count_muchii != n -1 ) {
        cout << "Nu" << endl;
    } else {
        cout << "Da" << endl;

        for (i = 0 ; i <= n; i++) {
            if (apcm2[i].size()) {
                for (int j = 0; j < apcm2[i].size(); j++) {
                    cout << apcm2[i][j] << " ";
                }
                cout << endl;
            }
        }
        for (i = 0 ; i <= n; i++) {
            if (apcm1[i].size()) {
                for (int j = 0; j < apcm1[i].size(); j++) {
                    cout << apcm1[i][j] << " ";
                }
                cout << endl;
            }
        }

    }

    return 0;
}

/*
10 10
1 6
1 8
1 10
2 5
2 9
3 5
3 6
4 5
7 9
9 10
 */