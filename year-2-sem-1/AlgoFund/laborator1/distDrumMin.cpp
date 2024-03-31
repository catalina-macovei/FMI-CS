/// compelxitate : O(n + m)

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 100000;

vector<int> graf[MAXN];  // Lista de adiacență pentru graf
int distanta[MAXN];     // Vector pentru a stoca distanțele minime

void bfs(int start, int n) {
    vector<bool> vizitat(n + 1, false);  // Vector pentru a urmări nodurile vizitate
    queue<int> coada;  // Coada pentru parcurgerea în lățime (BFS)

    coada.push(start);  // Adăugăm nodul de start în coadă
    vizitat[start] = true;  // Marcam nodul de start ca vizitat
    distanta[start] = 0;  // Distanța de la nodul de start la el însuși este 0

    while (!coada.empty()) {  // Cat timp coada nu este goală
        int nod = coada.front();  // Luăm primul nod din coadă
        coada.pop();  // Ștergem nodul din coadă

        for (int vecin : graf[nod]) {  // Parcurgem toți vecinii nodului
            if (!vizitat[vecin]) {  // Dacă vecinul nu a fost vizitat
                coada.push(vecin);  // Adăugăm vecinul în coadă
                vizitat[vecin] = true;  // Marcam vecinul ca vizitat
                distanta[vecin] = distanta[nod] + 1;  // Actualizăm distanța până la vecin
            }
        }
    }
}

int main() {
    ifstream fin("laborator1/graf.in");  // Deschidem fișierul de intrare
    ofstream fout("laborator1/graf.out");  // Deschidem fișierul de ieșire

    int n, m;
    fin >> n >> m;  // Citim numărul de noduri și muchii din graf

    for (int i = 0; i < m; i++) {
        int u, v;
        fin >> u >> v;
        graf[u].push_back(v);  // Adăugăm o muchie între nodurile u și v
        graf[v].push_back(u);
    }

    int numar_puncte_de_control;
    fin >> numar_puncte_de_control;  // Citim puncte de control

    vector<int> puncte_de_control(numar_puncte_de_control);

    for (int i = 0; i < numar_puncte_de_control; i++) {
        fin >> puncte_de_control[i];
    }

    for (int punct_control : puncte_de_control) {
        bfs(punct_control, n);  // Aplicăm BFS pornind de la fiecare nod de control
    }

    for (int i = 1; i <= n; i++) {
        if (i != 1) {
            fout << " ";
        }
        fout << distanta[i];  // Scriem distanța minimă pentru fiecare nod în fișierul de ieșire
    }
    fout << endl;

    fin.close();  // Închidem fișierul de intrare
    fout.close();  // Închidem fișierul de ieșire

    return 0;
}
