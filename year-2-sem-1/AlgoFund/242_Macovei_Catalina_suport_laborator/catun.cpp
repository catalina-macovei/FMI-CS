# include <vector>
# include <algorithm>
# include <queue>       /// DIJKSTRA O(mlogn)
# include <iostream>    /// CATUN Drumuri minime din surse multiple

using namespace std;


// Structura definind un element cu proprietatile 'y' si 'pond'
struct elem
{
    int y, pond;
} E;

// Lista de adiacenta pentru a reprezenta graful
vector<elem> v[100000];

// Coada pentru parcurgerea BFS
queue<int> Q;

int i, j, n, m, x, y, K, pondere;
int dist[100000], traseu[100000];
bool fortarete[100000];

// Functie pentru parcurgerea BFS
void BFS()
{
    int i, urm, cost, k;
    while (!Q.empty())
    {
        k = Q.front();
        Q.pop();
        for (i = 0; i < v[k].size(); ++i)
        {
            urm = v[k][i].y;
            cost = v[k][i].pond;
            // Actualizeaza informatiile despre distanta si traseu daca gaseste un traseu mai scurt, actualizeaza
            if (dist[urm] > dist[k] + cost || (dist[urm] == dist[k] + cost && traseu[k] < traseu[urm]))
            {
                dist[urm] = dist[k] + cost;
                traseu[urm] = traseu[k];
                Q.push(urm);
            }
        }
    }
}

int main()
{
    cin >> n >> m >> K;

    // Initializare fortarete si adaugare in coada pentru BFS
    for (i = 1; i <= K; ++i)
    {
        cin >> x;
        fortarete[x] = 1;
        Q.push(x);
    }

    // Initializare distante si trasee
    for (i = 1; i <= n; ++i)
        if (!fortarete[i])
        {
            dist[i] = 1000000;
            traseu[i] = 1000000;
        }
        else {
            traseu[i] = i;
        }


    // Citire muchii si construire graful
    for (i = 1; i <= m; ++i)
    {
        cin >> x >> y >> pondere;
        E.y = y;
        E.pond = pondere;
        v[x].push_back(E);
        E.y = x;
        E.pond = pondere;
        v[y].push_back(E);
    }

    // Apel BFS pentru calculul traseelor
    BFS();

    // Afisare rezultate
    for (i = 1; i <= n; ++i)
    {
        if (traseu[i] == i || traseu[i] == 1000000)
            cout << "0 ";
        else
            cout << traseu[i] << " ";
    }
    cout << "\n";

    return 0;
}

/*catun.in
8 9 2
2 5
1 3 6
1 5 3
1 6 1
2 3 9
5 6 5
6 8 7
3 6 2
4 7 1000
2 8 5
 */