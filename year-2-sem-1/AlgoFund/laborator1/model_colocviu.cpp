//
// Created by Catalina Macovei on 24.01.2024.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

using namespace std;

int oDegree[100], apcmDegree[100], vizOrig[100], vizAPCM[100];
vector<pair<int, int>> oGraph[100], apcmGraph[100];

void DFSorig(int node) {
    vizOrig[node] = 1;

    int neighbor;
    for (auto edge: oGraph[node]) {
        neighbor = edge.first;

        if(vizOrig[neighbor] == 0)
            DFSorig(neighbor);
    }
}

void DFSapcm(int node) // pt apcm
{
    vizAPCM[node] = 1;
    int neighbor;

    for (auto edge: apcmGraph[node]) {
        neighbor = edge.first;

        if (vizAPCM[neighbor] == 0)
            DFSapcm(neighbor);
    }
}

int tree[100], height[100];

void intialize(int n) {
    for (int i = 1; i <= n; i++)
        tree[i] = i;
}

int findRoot(int x) {
    if (x == tree[x])
        return x;
    return findRoot(tree[x]);
}

void unionTrees(int x, int y) {
    int rootA = findRoot(x);
    int rootB = findRoot(y);

    if (height[rootA] < height[rootB])
        tree[rootA] = rootB;
    else if (height[rootA] > height[rootB])
        tree[rootB] = rootA;
    else if (rootA != rootB) {
        tree[rootB] = rootA;
        height[rootA]++;
    }

}

int main () {
    int i , j, nodeX, nodeY, cost, countEdges = 0, totalCost = 0;

    vector<pair<int, pair<int, int>>> obligatoryEdges, remainingEdges;

    int nodes, edges, obligEdges;

    cin >> nodes >> edges >> obligEdges;

    for(i = 0; i < edges; i++) {
        cin >> nodeX >> nodeY >> cost;

        if (countEdges < obligEdges)
            obligatoryEdges.push_back({cost, {nodeX, nodeY}});
        else
            remainingEdges.push_back({cost, {nodeX, nodeY}});

        oGraph[nodeX].push_back({nodeY, cost});
        oGraph[nodeY].push_back({nodeX, cost});
        oDegree[nodeX]++;
        oDegree[nodeY]++;
        countEdges++;
    }
    // verific dc poate fi arbore
    countEdges = 0;

    for (i = 0; i < nodes; i++) {
        countEdges += oDegree[i];
    }

    if (countEdges != 2 * (nodes - 1) || edges != nodes - 1)
    {
        cout << "nu" << endl;
    }
    else
    {
        countEdges = 0;
        for (i = 0; i < nodes; i++) {
            if (vizOrig[i] == 0)
            {
                DFSorig(i);
                countEdges++;
            }
        }
        if (countEdges - 1 != 1) {
            cout << "nu conex!" << endl;
            return 0;
        }
    }

    list<pair<int, int>> apcmEdges;
    sort(remainingEdges.begin(), remainingEdges.end());
    intialize(nodes);
    countEdges = 0;   // nr muchii

    // muchii obligatorii
    for (i = 0; i < obligEdges; i++)
    {
        cost = obligatoryEdges[i].first;
        nodeX = obligatoryEdges[i].second.first;
        nodeY = obligatoryEdges[i].second.second;

        if (findRoot(nodeX) != findRoot(nodeY))
        {
            totalCost += cost;
            unionTrees(nodeX, nodeY);
            apcmEdges.push_back({nodeX, nodeY});

            apcmGraph[nodeX].push_back({nodeY, cost});
            apcmGraph[nodeY].push_back({nodeX, cost});

            apcmDegree[nodeX]++;
            apcmDegree[nodeY]++;
        }
        else
        {
            cout << "nu exista arbore!" << endl;
            return 0;
        }
    }

    countEdges = 0;

    // continui cu restul muchiilor
    for (i = 0; i < edges - obligEdges; i++)
    {
        cost = remainingEdges[i].first;
        nodeX = remainingEdges[i].second.first;
        nodeY = remainingEdges[i].second.second;

        if (findRoot(nodeX) != findRoot(nodeY))
        {
            totalCost += cost;

            unionTrees(nodeX, nodeY);

            apcmEdges.push_back({nodeX, nodeY});
            apcmGraph[nodeX].push_back({nodeY, cost});
            apcmGraph[nodeY].push_back({nodeX, cost});

            countEdges++;
            apcmDegree[nodeX]++;
            apcmDegree[nodeY]++;

        }

    }

    if (countEdges + obligEdges != nodes - 1)
    {
        cout << "nu exista apcm!" << endl;
        return 0;
    }

    cost = 0;
    countEdges = 0;

    for (i = 1; i <= nodes; i++)
        if (apcmDegree[i] != 0)
            cost += apcmDegree[i], countEdges++;

    if (cost != 2 * (countEdges - 1))
    {
        cout << "nu exista arbore!" << endl;
    }
    else
    {
        countEdges = 0;
        for (i = 0; i < nodes; i++)
            if (vizAPCM[i] == 0)
            {
                DFSapcm(i);
                countEdges++;
            }
        if (countEdges - 1 != 1)
        {
            cout << "nu conex!" << endl;
            return 0;
        }
    }


    cout << "costul: " << totalCost << endl;

    for (auto edge: apcmEdges)
        cout << edge.first << " " << edge.second << endl;


    return 0;
}