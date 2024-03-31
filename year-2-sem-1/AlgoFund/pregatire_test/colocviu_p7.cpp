/*
 * adaugare nr minim de muchii p/u ca graful sa fie conex, calculul excentricitatii
 *
 */
#include <iostream> //DFS,
#include <vector>
#include <queue>
#include <algorithm>
#include<bits/stdc++.h>
#include <cassert>
using namespace std;

int viz[1000001];
int tata[1000001], distanta[1000001];
vector<int> G[1000001];
int i, x, y, gradX=0, gradY=0;    // var auxiliare p/u citirea datelor
int n, m, start;
queue<int> Q;   // o coada
int grade[1000001];


void DFS(int nod)   // parcurgerea in adancime DFS
{
    int i, nr_vecini = 0, vecin;  // declar variabilele si initializez, lim = nr vecini

    nr_vecini = G[nod].size();
    viz[nod] = 1;

    //cout << nod << " ";     // Afisarea noduri in timpul DFS

    for(i = 0; i < nr_vecini; i++)    // Pentru fiecare vecin nevizitat -> DFS
    {
        vecin = G[nod][i];
        if(viz[vecin] == 0)
        {
            tata[vecin] = nod;
            DFS(vecin);

        }

    }
}

pair<int, int> bfs(int u)
{
    //  mark all distance with -1
    int dis[n];
    memset(dis, -1, sizeof(dis));

    queue<int> q;
    q.push(u);

    //  distance of u from u will be 0
    dis[u] = 0;

    while (!q.empty())
    {
        int t = q.front();       q.pop();

        //  loop for all adjacent nodes of node-t
        for (auto it = G[t].begin(); it != G[t].end(); it++)
        {
            int v = *it;

            // push node into queue only if
            // it is not visited already
            if (dis[v] == -1)
            {
                q.push(v);

                // make distance of v, one more
                // than distance of t
                dis[v] = dis[t] + 1;
            }
        }
    }

    int maxDis = 0;
    int nodeIdx;

    //  get farthest node distance and its index
    for (int i = 0; i < n; i++)
    {
        if (dis[i] > maxDis)
        {
            maxDis = dis[i];
            nodeIdx = i;
        }
    }
    return make_pair(nodeIdx, maxDis);
}

//  method prints longest path of given tree
void longestPathLength()
{
    pair<int, int> t1, t2;

    // first bfs to find one end point of
    // longest path
    t1 = bfs(start);

    //  second bfs to find actual longest path
    //t2 = bfs(t1.first);

    cout << "Longest path is from " << start << " to "
         << t1.first << " of length " << t1.second;
}


int main () {


    /**     CITIRE INITIALIZARE     */
    cin >> n >> m;  // citesc nr noduri, muchii

    for (i = 0; i < m; i++) {
        cin >> x >> y;

        G[x].push_back(y);
        G[y].push_back(x);

        ++grade[x];
        ++grade[y];
    }

    // gestionarea limitelor
    assert(n >= 1 && n <= 100000);
    assert(m >= 1 && m <= min(n * (n - 1) / 2, 2 * 100000));

    cin >> start;

    //Initializez vectorul distanta, viz[start], dist[start]
    for (i = 0; i < n; i++)
    {
        distanta[i] = -1;
        viz[i] = 0;
    }

    for (i = 1; i <= n; i++)
    {
        if (!viz[i])
        {
            DFS(i);
            //cout <<  endl;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        //cout << tata[i] << "\t" ;
        if (tata[i] == 0 && grade[i] < 2)

            for (int j = 1; j <= n; j++)

                if (grade[j] > 1)
                {
                    tata[i] = j;
                    cout << j << " " << i << endl;
                    G[j].push_back(i);
                    G[i].push_back(j);
                    ++grade[i];
                    ++grade[j];
                    break;
                }
   }

    longestPathLength();
}

/*
 6 4
 1 3
 1 5
 3 5
 2 4
 6
 */