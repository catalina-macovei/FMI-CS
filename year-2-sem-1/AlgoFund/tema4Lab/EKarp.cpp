//
// Created by Catalina Macovei on 04.01.2024.
//
#include <bits/stdc++.h>

using namespace std;

struct Graph {
    int n, src, dst;
    // edge is pair (neighbor, color)
    // color == 0 ==> BLACK (graph edge)
    // color == 1 ==> RED   (solution edge)
    vector<vector<long long>> cap;
    vector<vector<int>> adj;

    Graph(int n) : n(n), adj(n),
                   cap(n, vector<long long>(n, 0)) {}

    void AddEdge(int a, int b, int c) {
        adj[a].push_back(b);
        adj[b].push_back(a);
        cap[a][b] += c;
        // cap[b][a] == 0
    }

    int ek_iter() {
        vector<bool> vis(n, false);
        vector<int> parent(n, -1);

        vector<int> q;
        auto push = [&](int node, int par) {
            if (vis[node]) return;
            vis[node] = true;
            parent[node] = par;
            q.push_back(node);
        };

        push(src, -1);
        for (int i = 0; i < (int)q.size(); ++i) {
            int node = q[i];
            for (auto nei : adj[node]) {
                if (cap[node][nei] > 0)
                    push(nei, node);
            }
        }

        if (parent[dst] == -1)
            return 0;

        long long flow = 2e18;
        for (int node = dst; node != src; node = parent[node])
            flow = min(flow, cap[parent[node]][node]);
        assert(flow > 0);

        for (int node = dst; node != src; node = parent[node]) {
            cap[parent[node]][node] -= flow;
            cap[node][parent[node]] += flow;
        }
        return flow;
    }

    long long FordFulkerson(int src, int dst) {
        this->src = src; this->dst = dst;
        long long max_flow = 0;
        while (true) {
            long long curr_flow = ek_iter();
            if (curr_flow == 0) break;
            max_flow += curr_flow;
        }
        return max_flow;
    }
};

int main() {
    ifstream cin("tema4Lab/retea.in");
    ofstream cout("retea.out");

    int n, m; cin >> n >> m;
    Graph G(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c; --a; --b;
        G.AddEdge(a, b, c);
    }

    auto answer = G.FordFulkerson(0, n - 1);
    cout << answer << '\n';

    return 0;
}
//#include <bits/stdc++.h>
//
//using namespace std;
//
//const int NMAX = 100;
//int cap[NMAX][NMAX];
//int flux[NMAX][NMAX];
//int p[NMAX];
//vector<int> G[NMAX];
//
//int eKarp(int source, int dest) {
//    queue<int> q;
//    int vis[NMAX] = {0};
//    int flow = 1000000; // inf
//    q.push(source);
//    vis[source] = 1;
//
//    while(!q.empty()) {
//        int x = q.front();
//        q.pop();
//
//        for(auto next : G[x])
//            if (cap[x][next] - flux[x][next] > 0) {
//                p[next] = x;
//                flow = min(flow, cap[x][next] - flux[x][next]);
//                q.push(next);
//                vis[next] = 1;
//            }
//    }
//    return flow;
//}
//
//int maxFlow(int s, int d) {
//    int sum = 0;
//
//    while (true) {
//        int f = eKarp(s, d);
//
//        if (f == 0)
//            break;
//        else {
//            int current = d;
//            while (current != s) {
//                flux[p[current]][current] += f;
//                flux[current][p[current]] -= f;
//                current = p[current];
//            }
//
//            // Reset d to the original destination node after processing one augmenting path
//            d = current;
//            sum += f;
//
//            // Debug print statements
//            cout << "Augmenting path found: " << f << " units of flow\n";
//            cout << "Current flow: " << sum << "\n";
//        }
//    }
//
//    return sum;
//}
//
//
//
//int main() {
//    ifstream cin("tema4Lab/retea.in");
//    ofstream cout("retea.out");
//
//    int n, m;
//    int s, d;
//
//    cin >> n;
//    cin >> s >> d;
//    cin >> m;
//
//    for (int i = 0; i < m; ++i) {
//        int x, y, c;
//
//        cin >> x >> y;
//        cap[x][y] = c;
//
//        G[x].push_back(y);
//        G[y].push_back(x);
//    }
//    cout << maxFlow(s, d);
//
//    return 0;
//}