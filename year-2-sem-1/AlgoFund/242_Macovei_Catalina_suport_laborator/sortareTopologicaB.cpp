#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_N = 100005;

int n, m;
vector<int> vecini[MAX_N];
vector<int> vizitat(MAX_N, 0); // Folosit pentru a ține evidența nodurilor vizitate în timpul parcurgerii DFS
vector<int> ciclu; // Folosit pentru a ține nodurile ciclului
vector<int> grad_intrare(MAX_N, 0);     // nr de muchii de intrare, adică numărul de muchii care se termină într-un nod  initial toate valorile sunt 0
vector<int> ordine_elem;
vector<int> stiva; // Folosit pentru a ține nodurile în timpul parcurgerii DFS

bool sortare_topologica() {
    queue<int> q;   //

    for (int i = 1; i <= n; i++) {  // numar de la 1 pana la nr de noduri n
        if (grad_intrare[i] == 0) { // daca e 0 inseamna ca nu am accesat nodul i
            q.push(i);  // il adaug in coada
        }
    }

    while (!q.empty()) {    // dc coada nu e goala
        int curs = q.front();   // folosesc ultimul element din coada,
        q.pop();    //  apoi il elimin
        ordine_elem.push_back(curs); // pastrez ordinea elementelor in vectorul ordine

        for (int curs_urmator : vecini[curs]) { // vizitez vecinii
            grad_intrare[curs_urmator]--;   // marchez gradul de intrare
            if (grad_intrare[curs_urmator] == 0) {  // dc gradul a devenit 0,
                q.push(curs_urmator);       // il adaug in coada
            }
        }
    }

    return ordine_elem.size() == n;  // daca am ordonat toate elementele
}

bool detecteaza_ciclu(int nod) { // am parcurs cu bfs pentru a detecta ciclu

    vizitat[nod] = 1;
    stiva.push_back(nod);

    for (int curs_urmator : vecini[nod]) {
        if (vizitat[curs_urmator] == 0) {
            if (detecteaza_ciclu(curs_urmator)) {
                return true;
            }
        } else if (vizitat[curs_urmator] == 1) {
            // Am găsit un ciclu
            ciclu.push_back(curs_urmator);
            while (stiva.back() != curs_urmator) {
                ciclu.push_back(stiva.back());
                stiva.pop_back();
            }
            ciclu.push_back(curs_urmator);
            return true;
        }
    }

    vizitat[nod] = 2;
    stiva.pop_back();
    return false;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        vecini[a].push_back(b);
    }

    for (int i = 1; i <= n; i++) {
        if (vizitat[i] == 0) {
            if (sortare_topologica()) {     // dc am ordonat  elementele
                for (int curs : ordine_elem) {   // le afisez
                    cout << curs << " ";
                }
                cout << endl;
            }  if (detecteaza_ciclu(i)) {
                cout << "Ciclu: ";
                for (int nod : ciclu) {
                    cout << nod << " ";
                }
                cout << endl;
                return 0;
            }
        }
    }

    return 0;
}
