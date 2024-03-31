////O n+m

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ifstream fin("laborator1/bfs.in");
    ofstream fout("laborator1/bfs.out");
    vector<int> rasp[100000];
    int N, M, S;
    fin >> N >> M >> S;

    vector<vector<int>> graf(N + 1);  // Graf reprezentat ca o listă de adiacență
    vector<int> distanta(N + 1, -1);  // Vector pentru distanțe, inițial setate la -1 (infinit)
    queue<int> coada;

    for (int i = 0; i < M; i++) {
        int x, y;
        fin >> x >> y;
        graf[x].push_back(y); // Adăugăm arcele în graf
    }

    // Pasul inițial: adăugăm nodul sursă în coadă
    coada.push(S);
    distanta[S] = 0;

    int componente = 0;
    while (!coada.empty()) {
        int curent = coada.front();
        coada.pop();
        componente++;
        // Parcurgem vecinii nodului curent
        for (int vecin : graf[curent]) {
            if (distanta[vecin] == -1) {  // Dacă nodul nu a fost vizitat încă
                componente++;
                distanta[vecin] = distanta[curent] + 1;
                coada.push(vecin);
                rasp[componente].push_back(vecin);
            }
        }
    }

    // Scriem rezultatul în fișierul de ieșire
    for (int i = 1; i <= N; i++) {
        if (distanta[i] == -1) {
            fout << "-1 ";
        } else {
            fout << distanta[i] << " ";
        }
    }
    fout << endl;

    fin.close();
    fout.close();
    int counter = 0;
    for (int i = 0; i < componente; i++)
    {

        for (auto &el : rasp[i])
        {
            cout << el << ' ';
        }
        cout << endl;
        if (rasp[i].size() >= S) counter++;
    }
    cout << counter;
    return 0;
}

// DFS algorithm in C++
//
//#include <iostream>
//#include <list>
//using namespace std;
//
//class Graph {
//    int numVertices;
//    list<int> *adjLists;
//    bool *visited;
//
//public:
//    Graph(int V);
//    void addEdge(int src, int dest);
//    void DFS(int vertex);
//};
//
//// Initialize graph
//Graph::Graph(int vertices) {
//    numVertices = vertices;
//    adjLists = new list<int>[vertices];
//    visited = new bool[vertices];
//}
//
//// Add edges
//void Graph::addEdge(int src, int dest) {
//    adjLists[src].push_front(dest);
//}
//
//// DFS algorithm
//void Graph::DFS(int vertex) {
//    visited[vertex] = true;
//    list<int> adjList = adjLists[vertex];
//
//    cout << vertex << " ";
//
//    list<int>::iterator i;
//    for (i = adjList.begin(); i != adjList.end(); ++i)
//        if (!visited[*i])
//            DFS(*i);
//}
//
//int main() {
//    Graph g(4);
//    g.addEdge(100, 1);
//    g.addEdge(100, 2);
//    g.addEdge(1, 2);
//    g.addEdge(2, 3);
//
//    g.DFS(0);
//
//    return 0;
//}