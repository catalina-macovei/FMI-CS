//
// Created by Catalina Macovei on 15.02.2024.
//
#include <bits/stdc++.h>
// sortare topologica graf neponderat
using namespace std;

// order va mentine sortarea topologica
vector<int> order;
void DFS(int node, vector<vector<int>>& graph, vector<int>& vis) {
    // vis[node] =
    // 0, daca nu e inca procesat
    // 1, daca e in procesare
    // 2, daca a fost terminat de procesat
    vis[node] = 1;
    cout << node << "\t";
    for (auto vecin : graph[node]) {
        if (vis[vecin] == 1) {
            // CICLUL: din parent in parent de la node la nei
            cerr << "ERROR: Exista ciclu" << endl;
            exit(42);
        }
        if (!vis[vecin]) {
            // parent[vec] = node;
            DFS(vecin, graph,  vis);
        }
    }
    vis[node] = 2;
    order.push_back(node);
}

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; ++i) {
        // pp 0 <= a, b < n
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
    }

    // vis va contoriza daca un nod e vizitat sau nu
    vector<int> vis(n, 0);

    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            DFS(i, graph, vis);
            cout << endl;
        }
    }

    reverse(order.begin(), order.end());

    for (auto node : order)
        cout << node << " ";
    cout << '\n';

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



5 5
1 3
1 4
1 2
4 5
2 4

10 10 7

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

 * */