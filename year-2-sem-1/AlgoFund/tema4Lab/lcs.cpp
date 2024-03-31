//
// Created by Catalina Macovei on 07.01.2024.
//
/*testare
 aaabcd
agahbdert

 */
// O nm
#include <bits/stdc++.h>
using namespace std;

// Functia LCS calculeaza lungimea celui mai lung subsir comun (LCS) dintre doua siruri X si Y
string LCS(string X, string Y, int n, int m) {
    int dp[n + 1][m + 1]; // Matricea DP pentru programare dinamica

    // Cazul de baza al recurentei --> initializarea matricei dp
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            if (i == 0 || j == 0)
                dp[i][j] = 0;

    // Calculul matricei dp pentru fiecare subsir posibil
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (X[i - 1] == Y[j - 1]) // cand ultimul caracter este acelasi
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else // cand ultimul caracter nu este acelasi -> alegem maximul
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);

    int i = n, j = m;
    string lcs = ""; // retinem caracterele cand sunt egale in tabela
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs += X[i - 1]; // inseram in sir
            i--, j--;
        } else {
            if (dp[i][j - 1] > dp[i - 1][j])
                j--; // mutam la partea mai lunga
            else
                i--;
        }
    }
    reverse(lcs.begin(), lcs.end()); // la final inversam sirul pentru a obtine LCS

    return lcs;
}

int main() {
    string X, Y;
    cin >> X >> Y; // Citim cele doua siruri
    int n = X.length(), m = Y.length();

    cout << LCS(X, Y, n, m) << endl; // Afisam  continutul LCS
    return 0;
}



