// Created by Catalina Macovei on 29.10.2023.
/// Complexitate liste de adiacenta- O(n + m) kosaraju
/// componenta tare conexa - dc nodurile pot forma un graf tare conex (oricare 2 noduri se gaeste un drum)
//
//Input:
//5 6
//1 2
//2 3
//3 1
//3 4
//4 5
//5 4
//
//Output:
//2
//1 1 1 2 2

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

ifstream in("laborator1/ctc.in");
ofstream out("laborator1/ctc.out");

vector<int> g[100002];
int desc[100002];
int lowTime[100002];
bool onStack[100002];
int timp;
stack<int> s;
vector<int> rasp[100000];   // un array de vectori ( vector = componenta)
int n, m, nr_componente, nr;

void dfs(int x)
{
    timp++;
    s.push(x);
    onStack[x] = true;
    desc[x] = lowTime[x] = timp;

    for (auto &to : g[x])
    {
        if (desc[to] == 0)  // nevizitat
        {
            dfs(to);
        }
        if (onStack[to])    // in explorare -> gri
        {
            lowTime[x] = min(lowTime[x], lowTime[to]);  // timp descoperire pentru radacina -> descoperire comonenta
        }
    }
    if (lowTime[x] == desc[x])  // este in ciclu -> componenta
    {
        while (s.top() != x)    // explorez toate nodurile din componenta
        {
            rasp[nr_componente].push_back(s.top());
            lowTime[s.top()] = min(lowTime[x], lowTime[s.top()]);
            onStack[s.top()] = false;
            s.pop();
        }
        rasp[nr_componente].push_back(s.top()); // dau push lui x , incheiem ciclu
        onStack[s.top()] = false;
        s.pop();
        ++nr_componente;    // finalizare componenta
    }
}
int main()
{
    int x, y;
    in >> n >> m ;
    for (int i = 0; i < m; i++)
    {
        in >> x >> y;
        g[x].push_back(y);
    }
    for (int i = 1; i <= n; i++)
    {
        if (desc[i] == 0)   // nevizitat
        {
            dfs(i);
        }
    }
    out << nr_componente << '\n';

    int counter = 0 ;
    for (int i = 0; i < nr_componente; i++)
    {

        for (auto &el : rasp[i])
        {
            out << el << ' ';
        }
        //if (rasp[i].size() >= nr) counter++;  daca vreau o componenta sa aiba un anumit nr de noduri
        out << endl;
    }
}