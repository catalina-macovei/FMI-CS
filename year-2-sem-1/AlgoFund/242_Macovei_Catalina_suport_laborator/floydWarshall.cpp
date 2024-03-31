/*

 testare ciclu negativ:
4  4
1 2 1
4 2 -7
2 3 2
3 4 3
 fara ciclu negativ:
 4 4
 1 2 1
 4 2 7
 2 3 2
 3 4 3
 */

#include<bits/stdc++.h>
using namespace std;
// O n3
long long graph[100][100]; // Matricea de adiacență pentru graful ponderat

void  warshall(int node)
{
    int k,i,j;
    // Algoritmul Warshall pentru actualizarea drumurilor minime
    for(k=1; k<=node; k++)
        for(i=1; i<=node; i++)
            for(j=1; j<=node; j++)
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}

void print(int n)
{
    cout<<"Toate drumurile cele mai scurte dintre perechi sunt: "<< endl;
    int i,j;
    // Afișarea tuturor drumurilor minime dintre perechi
    for(i=1; i<=n; i++){
        for(j=1; j<=n; j++)
            cout<< ((graph[i][j] >= INT_MAX) ? 0 : graph[i][j]) << " ";
        cout<<endl;
    }
}

bool detect_negative_cycle(int nodes) {
    // Detectarea ciclurilor negative în graful ponderat
    bool is_negative = false;
    for (int i = 1; i <= nodes; i++)
        if (graph[i][i] < 0) {
            is_negative = true;
            break;
        }

    return is_negative;
}

void print_neg_cycle(int nodes) {
    // Afișarea nodurilor implicate în ciclurile negative
    for (int i = 1; i <= nodes; i++)
        if (graph[i][i] < 0) {
            cout << i << "\t";
        }
}

int main()
{
    int i,j,e,n,u,v,w;
    // Inițializarea matricei de adiacență cu distanțe inițiale
    for(i=0; i<100; i++)
        for(j=0; j<100; j++)
            if(i==j)
                graph[i][j]=0;
            else
                graph[i][j]=INT_MAX;

    cout<<"Introduceți numărul de noduri și muchii: ";
    cin>>n>>e;

    // Citirea muchiilor și ponderilor lor
    while(e--){
        cin>>u>>v>>w;
        graph[u][v]=w;
    }

    // Aplicarea algoritmului Warshall pentru găsirea drumurilor minime
    warshall(n);

    if (detect_negative_cycle(n)) {
        // Afișarea ciclurilor negative dacă există
        cout << "\n Ciclu de cost negativ " << endl;
        print_neg_cycle(n);
    }
    else {
        // Afișarea rezultatelor
        print(n);
    }

    return 0;
}