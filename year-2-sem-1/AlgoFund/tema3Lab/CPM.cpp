#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
// O (n+m)
using namespace std;

void dfs(int u, vector<vector<int>>& graph, stack<int>& stk, vector<int>& vis) {
    vis[u] = true;

    for (int v : graph[u]) {
        if (!vis[v]) {
            dfs(v, graph, stk, vis);
        }
    }

    stk.push(u);
}

int main() {
    ifstream fin("tema3Lab/activitati.in");
    int n, m;
    fin >> n;
    vector<int> d(n + 1), es(n + 1, 0), ef(n + 1); // durations, earliest starts, earliest finishes
    vector<vector<int>> adj(n + 1), pred(n + 1); // adjacency list and predecessor list

    for (int i = 1; i <= n; ++i) {
        fin >> d[i];
    }

    fin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        fin >> a >> b;
        adj[a].push_back(b);
        pred[b].push_back(a);
    }
    fin.close();

    stack<int> stk;
    vector<int> vis(n + 1, 0);

    // Step 2: le ordonez recursiv DFS
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            dfs(i, adj, stk, vis);
        }
    }

    // Step 3: Calculate earliest start (es) and earliest finish (ef) times
    while (!stk.empty()) {
        int u = stk.top();
        stk.pop();

        int max_ef = 0;
        for (int v : pred[u]) {  //pentru fiecare nod din vectorl de predecesori
            max_ef = max(max_ef, ef[v]);
        }

        es[u] = max_ef;
        ef[u] = es[u] + d[u];
    }

    int duration = ef[n];
    // Step 5: Print minimum time to complete activities
    cout << "Timp minim " << duration << endl;

    vector<int> criticalActivities;

    // Step 6: Find critical activities
    for (int i = 1; i <= n; ++i) {
        if (ef[i] == duration) {
            criticalActivities.push_back(i);
        }
    }

    if (criticalActivities.empty()) {
        cout << "Nu exista activitati critice." << endl;
    }
    else {
        cout << "Activitati critice: ";
        for (int i : criticalActivities) {
            cout << i << " ";
        }
        cout << endl;
    }

    cout << endl;

    // Step 7: Print start and finish times for each activity
    for (int i = 1; i <= n; ++i) {
        cout << i << ": " << es[i] << " " << ef[i] << endl;
    }

    return 0;
}

/**
 *
 * The Critical Path Method (CPM) algorithm has a time complexity of O(n + m), where n is the number of activities (or tasks) and m is the number of dependencies between the activities.

Here's a breakdown of the time complexity for each step of the CPM algorithm:

1. Reading input: Reading the values for n, durations, and dependencies takes O(n + m) time.

2. Building the adjacency list: Constructing the adjacency list takes O(m) time.

3. Topological sorting or DFS: Calculating the topological sorting (or performing DFS) takes O(n + m) time.

4. Calculating earliest start (ES) and earliest finish (EF) times: Calculating the ES and EF values for each activity takes O(n) time since we iterate over all activities once.

5. Calculating latest start (LS) and latest finish (LF) times: Calculating the LS and LF values for each activity takes O(n) time since we iterate over all activities once.

6. Finding the critical path: Identifying the critical path, which involves iterating over all activities to check if their ES and LS values are equal (or their EF and LF values are equal) takes O(n) time.

7. Printing the results: Printing the results, including the critical path and the total duration, takes O(n) time.

Overall, the CPM algorithm has a time complexity of O(n + m), making it a fairly efficient method for determining the schedule and critical path of a project.*/