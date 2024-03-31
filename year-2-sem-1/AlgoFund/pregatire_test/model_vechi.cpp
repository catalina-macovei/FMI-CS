/*
Model input k - nr muchii obligatorii
9 14 2
1 2 10
1 3 11
2 4 11
2 5 11
5 6 13
3 4 10
4 6 12
4 7 5
3 7 4
3 8 5
8 7 5
8 9 4
9 7 3
6 7 11
 * */

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

using namespace std;

int originalDegree[100], apcmDegree[100], visitedOriginal[100], visitedAPCM[100];
vector<pair<int, int>> originalGraph[100], apcmGraph[100];

void DFSOriginal(int node) // pt graf initial
{
    visitedOriginal[node] = 1;
    int neighbor;
    for (auto edge : originalGraph[node])
    {
        neighbor = edge.first;
        if (visitedOriginal[neighbor] == 0)
            DFSOriginal(neighbor);
    }
}

void DFSAPCM(int node) // pt apcm
{
    visitedAPCM[node] = 1;
    int neighbor;
    for (auto edge : apcmGraph[node])
    {
        neighbor = edge.first;
        if (visitedAPCM[neighbor] == 0)
            DFSAPCM(neighbor);
    }
}

int tree[100], height[100];

void initialize(int n)
{
    for (int i = 1; i <= n; i++)
        tree[i] = i;
}

int findRoot(int x)
{
    if (x == tree[x])
        return x;
    return findRoot(tree[x]);
}

void unionTrees(int x, int y)
{
    int rootA = findRoot(x), rootB = findRoot(y);
    if (height[rootA] < height[rootB])
        tree[rootA] = rootB;
    else if (height[rootA] > height[rootB])
        tree[rootB] = rootA;
    else if (rootA != rootB)
    {
        tree[rootB] = rootA;
        height[rootA]++;
    }
}

int main()
{
    int i, j, nodeX, nodeY, cost, countEdges = 0, totalCost = 0;

    vector<pair<int, pair<int, int>>> obligatoryEdges, remainingEdges; // cost, nodeX, nodeY

    ifstream fin("pregatire_test/date.in");
    int numNodes, numEdges, numObligatoryEdges;
    fin >> numNodes >> numEdges >> numObligatoryEdges;

    for (i = 0; i < numEdges; i++)
    {
        fin >> nodeX >> nodeY >> cost;

        if (countEdges < numObligatoryEdges)
            obligatoryEdges.push_back({cost, {nodeX, nodeY}});
        else
            remainingEdges.push_back({cost, {nodeX, nodeY}});

        originalGraph[nodeX].push_back({nodeY, cost});
        originalGraph[nodeY].push_back({nodeX, cost});
        originalDegree[nodeX]++;
        originalDegree[nodeY]++;
        countEdges++;
    }
    fin.close();

    // pentru Graf initial, verific daca poate fi arbore
    countEdges = 0;
    for (i = 0; i < numNodes; i++)
        countEdges += originalDegree[i];

    if (countEdges != 2 * (numNodes - 1) || numEdges != numNodes - 1)
    {
        cout << "NU" << endl;
    }
    else
    {
        countEdges = 0;
        for (i = 0; i < numNodes; i++) // numar componente conexe
            if (visitedOriginal[i] == 0)
            {
                DFSOriginal(i);
                countEdges++;
            }
        if (countEdges - 1 != 1)
        {
            cout << "NU Conex" << endl;
            return 0;
        }
    }

    list<pair<int, int>> apcmEdges; // lista muchii APCM
    sort(remainingEdges.begin(), remainingEdges.end()); // sortez graful fara muchiile obligatorii
    initialize(numNodes);
    countEdges = 0; // in countEdges retin nr muchii

    // Incep cu muchiile obligatorii
    for (i = 0; i < numObligatoryEdges; i++)
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
            // Daca nu pot pune muchiile obligatorii, nu am arbore
        else
        {
            cout << "Nu exista Arbore";
            return 0;
        }
    }

    countEdges = 0; // nr muchii

    // Continui cu restul muchiilor
    for (i = 0; i < numEdges - numObligatoryEdges; i++)
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

    // Verific daca am obtinut arbore
    if (countEdges + numObligatoryEdges != numNodes - 1)
    {
        cout << "Nu exista Arbore";
        return 0;
    }

    cost = 0;
    countEdges = 0;
    for (i = 1; i <= numNodes; i++)
        if (apcmDegree[i] != 0)
            cost += apcmDegree[i], countEdges++;

    if (cost != 2 * (countEdges - 1))
    {
        cout << "Nu exista Arbore";
        return 0;
    }
    else
    {
        countEdges = 0;
        for (i = 0; i < numNodes; i++) // nr componente conexe
            if (visitedAPCM[i] == 0)
            {
                DFSAPCM(i);
                countEdges++;
            }
        if (countEdges - 1 != 1)
        {
            cout << "NU Conex" << endl;
            return 0;
        }
    }

    cout << "Costul: " << totalCost << endl;
    for (auto edge : apcmEdges)
        cout << edge.first << " " << edge.second << endl;

    return 0;
}
