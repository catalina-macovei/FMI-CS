//
// Created by Catalina Macovei on 23.10.2023.
//
#include<iostream>
#include<list>
#include <fstream>
using namespace std;
void display(list<int> lista_adiacenta[], int v) {      // complexitate: v * e (varfuri * muchii), depinde de structura grafului
    for (int i = 0; i < v; i++) {
        cout << i << "--->";
        for (const int& vecin : lista_adiacenta[i]) {
            cout << vecin << " ";
        }
        cout << endl;
    }
}

void adauga_muchie(list<int> adj_list[], int u, int v) {
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
}
int main() {

    int n1 = 0;
    int n2 = 0;
    int nr_muchii = 0;
    int nr_varfuri = 0;

    // read from file:
    const char* filename = "laborator1/graf.in";
    ifstream inFile(filename);

    if(!inFile) {
        cout << "File failed to open!" << endl;
        return 1;
    }

    inFile >> nr_varfuri >> nr_muchii;
    cout << nr_varfuri << "\t" <<  nr_muchii << endl;

    list<int> adj_list[nr_varfuri];

    while(!inFile.eof()) {
        inFile >> n1 >> n2;
        adauga_muchie(adj_list, n1 - 1, n2 - 1);
    }

    display(adj_list, nr_varfuri);
    return 0;
}
