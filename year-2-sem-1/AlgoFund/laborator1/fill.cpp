//
// Created by Catalina Macovei on 29.10.2023.
/// Compelxitate O (n*m)

/*Example Input:
5 8
########
#..#...#
####.#.#
#..#...#
########

Output:
3
 * */
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<vector<char>> cladire;   // matricea cladirii
vector<vector<bool>> vizitat;   // matricea nodurilor vizitate

// Definim cele patru directii posibile: sus, jos, stsnga si dreapta
const int dx[] = {-1, 1, 0, 0}; // stanga dr
const int dy[] = {0, 0, -1, 1}; // sus, jos

bool este_valid(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m);    // daca o pozitie este in interiorul matricii
}

void dfs(int x, int y) {
    vizitat[x][y] = true;   // nodul marchez ca vizitat
    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i];  // calculez poz noua pe axa orizontala
        int new_y = y + dy[i];  // calculez poz noua pe axa verticala

        // dc poz este valida, nevizitata si nu reprezinta un zid
        if (este_valid(new_x, new_y) && !vizitat[new_x][new_y] && cladire[new_x][new_y] == '.') {
            dfs(new_x, new_y);  // o parcurg recursiv
        }
    }
}

int numara_camere() {
    int numar_camere = 0;
    vizitat.assign(n, vector<bool>(m, false)); // initializez matr de vizitare cu vector interior cu val False

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vizitat[i][j] && cladire[i][j] == '.') {
                // dc pozitia nu e vizitata si este camera, o parcurg recursiv
                dfs(i, j);
                numar_camere++; // incrementez nr camere
            }
        }
    }

    return numar_camere;
}

int main() {
    cin >> n >> m;
    cladire.assign(n, vector<char>(m));  // initializez matricea cladire

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> cladire[i][j];   // citesc valorile de la tastatura
        }
    }

    int camere = numara_camere();
    cout << camere << endl; // afisez nr de camere

    return 0;
}




