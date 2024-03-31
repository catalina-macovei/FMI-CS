
#include <bits/stdc++.h>

using namespace std;
//Conectarea cu cost minim a nodurilor la mai multe  surse:

struct punct {      // Definirea structurii pentru un punct în plan
    long long x, y;
};
// retele si blocuri

punct centrala[2001], bloc[2001]; // Declarații ale vectorilor de puncte
long long d[2001], vis[2001]; // Vectori pentru stocarea distanțelor și marcarea vizitărilor

// Funcție pentru calculul distanței pătratice între două puncte
long long dist(punct bloc, punct centrala) {
    return (centrala.x - bloc.x) * (centrala.x - bloc.x) + (centrala.y - bloc.y) * (centrala.y - bloc.y);
}

int main() {
    int n, m;
    cin >> n >> m; // Citirea valorilor pentru n și m

    // Citirea și stocarea coordonatelor punctelor de tip "c"
    for(int i = 1; i <= n; i++) {
        cin >> centrala[i].x >> centrala[i].y;
    }
    // Citirea și inițializarea coordonatelor punctelor de tip "b" și a distanțelor cu o valoare mare
    for(int i = 1; i <= m; i++) {
        cin >> bloc[i].x >> bloc[i].y;
        d[i] = 1e18;
    }
    // Calculul distanței minime pentru fiecare punct de tip "b" față de orice punct de tip "c"
    for(int i = 1; i <= m; i++) {
        long long mn = 1e18;
        for(int j = 1; j <= n; j++) {
            mn = min(mn, dist(bloc[i], centrala[j]));
        }
        d[i] = mn;
    }
    // determinarea distanțelor minime între punctele de tip "b"
    for(int i = 1; i <= m; i++) {
        long long mn = 1e18;
        int pos = 0;
        for(int j = 1; j <= m; j++) {
            if(!vis[j] && d[j] < mn) {
                mn = d[j];
                pos = j;
            }
        }
        vis[pos] = 1;
        for(int j = 1; j <= m; j++) {
            if(!vis[j] && d[j] > dist(bloc[pos], bloc[j])) {
                d[j] = dist(bloc[pos], bloc[j]);
            }
        }
    }
    double sol = 0; // Variabilă pentru stocarea soluției

    // Calculul și adunarea sumei pătratelor distanțelor minime
    for(int i = 1; i <= m; i++) {
        sol += sqrt(d[i]);
    }

    // Afișarea rezultatului cu precizie fixă de 7 zecimale
    cout << fixed << setprecision(7) << sol;
    return 0;
}

/*INPUT
2 2
0 0
10 11
10 0
0 10
 */
// conditie: se va gasi un singur numar real, reprezentand costul minim
// pentru a transmite curent eletric blocurilor in modul descris in enunt.
