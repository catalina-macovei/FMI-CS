//
// Created by Catalina Macovei on 29.10.2023.
//
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

#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 100005;

vector<int> graf[MAXN];
vector<int> graf_invers[MAXN];
vector<int> etichete_regate(MAXN, -1);
vector<int> vizitat(MAXN, 0);
vector<int> ordine_post;
set<int> regat_curent;

void dfs1(int nod) {
    vizitat[nod] = 1;
    for (int vecin : graf[nod]) {
        if (!vizitat[vecin]) {
            dfs1(vecin);
        }
    }
    ordine_post.push_back(nod);
}

void dfs2(int nod, int regat) {
    vizitat[nod] = 0;
    etichete_regate[nod] = regat; // un fel de tata[nod] = regat/predecesor
    regat_curent.insert(nod);
    for (int vecin : graf_invers[nod]) {
        if (vizitat[vecin]) {
            dfs2(vecin, regat);
        }
    }
}

int main() {
    int n, m;
    int a, b;   // var auxiliare p/u citire
    cin >> n >> m;  // nr noduri, muchii

    /**    Initializare date     **/
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        graf[a].push_back(b);
        graf_invers[b].push_back(a);
    }

    /**  parcurgere ordine_post (postordine) pe graful original  **/
    for (int i = 1; i <= n; i++) {
        if (!vizitat[i]) {      // cu noduri nevizitate
            dfs1(i);
        }
    }

    /**   parcurg inca o data vectorul parcurs in postordine      **/
    int eticheta_regat_curent = 0;
    for (int i = n - 1; i >= 0; i--) {
        int nod = ordine_post[i];
        if (vizitat[nod]) {
            regat_curent.clear();   // in regat curent sunt nodurile componentei conexe
            eticheta_regat_curent++;    // exista o componenta conexa
            dfs2(nod, eticheta_regat_curent);  // explorez nodul DFS
        }
    }

    cout << eticheta_regat_curent << endl;
    for (int i = 1; i <= n; i++) {
        cout << etichete_regate[i] << " ";
    }
    cout << endl;

    return 0;
}