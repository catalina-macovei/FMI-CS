//
// Created by Catalina Macovei on 07.01.2024.
//
// Created by Catalina Macovei on 07.01.2024.
//
#include <algorithm>
#include <fstream>
#include <vector>
#include <cstring>
#define inf 0x3f3f3f3f

using namespace std;
ifstream fin("tema4Lab/hamilton.in");
ofstream fout("tema4Lab/hamilton.out");

vector<int> g[20];  // Lista de adiacență pentru graf
int n, m, x, y;
int dp[20][(1 << 18) + 1], cost[20][20];  // dp pentru stocarea rezultatelor parțiale, cost pentru matricea de costuri între noduri


// oricare 2 noduri adiacente -> exista o muchie
int main()
{
    fin >> n >> m;
    memset(cost, inf, sizeof(cost));  // Inițializare matrice cu valori mari
    for (int i = 1; i <= m; i++)
    {
        fin >> x >> y;
        fin >> cost[x][y];  // Citire cost între nodurile x și y
        g[y].push_back(x);  // Adăugare nod x în lista de adiacență a nodului y
    }
    memset(dp, inf, sizeof(dp));  // Inițializare dp cu valoarea infinit
    dp[0][1] = 0;  // Cazul de bază: costul de a ajunge la nodul 0 cu un singur nod vizitat este 0
    for (int conf = 1; conf < (1 << n); conf++)
    {
        for (int i = 0; i < n; i++)
        {
            if (conf & (1 << i))
            {
                for (vector<int>::iterator it = g[i].begin(); it < g[i].end(); it++)
                {
                    if (conf & (1 << (*it)))
                        dp[i][conf] = min(dp[i][conf], dp[*it][conf ^ (1 << i)] + cost[*it][i]);
                    // Actualizare cost pentru a ajunge la nodul i în configurația conf
                }
            }
        }
    }
    int sol = inf;
    for (vector<int>::iterator it = g[0].begin(); it < g[0].end(); it++)
        sol = min(sol, dp[*it][(1 << n) - 1] + cost[*it][0]);
    // Alegerea soluției minimale dintre costurile de a ajunge în nodul 0 plecând de la toate celelalte noduri
    if (sol == inf)
        fout << "There is no solution!";
    else
        fout << sol;
    fin.close();
    fout.close();
    return 0;
}
