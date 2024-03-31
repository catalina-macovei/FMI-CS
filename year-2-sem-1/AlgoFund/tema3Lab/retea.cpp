//
// Created by Catalina Macovei on 12.12.2023.
//


#include <iostream> //DAG
#include <list>
#include <queue>
#include <utility>

using namespace std;
int d[100], t[100], st, grad[100];
//d=distanta, t=tata, st=nod de start

int main ()
{
    list< pair<int, int>> L[100]; //L[x]; primul int=y, 2 int=pondere; xy=muchie
    int i, n, m, x, y, c;
    cin>>n>>m; //n=nr noduri, m=nr muchii
    for(i=0; i<m; i++)
    {
        cin>>x>>y>>c;
        L[x].push_back({y, c});
        grad[y]++;
    }

    list<int> TP; //sortare topologica
    queue<int> Q;

    for(i=1; i<=n; i++)
        if(!grad[i]) Q.push(i);
    while(!Q.empty())
    {
        x=Q.front(); Q.pop();
        TP.push_back(x);
        for(pair<int, int> p: L[x]) //pt noduri adiacente
        {
            y=p.first; grad[y]--;
            if(!grad[y]) Q.push(y);
        }
    }

    cout<<"Nod Start: "; cin>>st; //nod start

    //Initializare
    for(i=1; i<=n; i++) d[i]=1000, t[i]=-1;
    t[st]=d[st]=0;
    for(int x: TP)
        for(pair<int, int> p: L[x]) //fiecare vecin a lui x
        {
            y=p.first; c=p.second;
            if(d[y]<d[x]+c) d[y]=d[x]+c, t[y]=x;
        }
    cout<<"Vectorul de Distante: ";
    for(i=1; i<=n; i++) cout<<d[i]<<" ";
    cout<<endl;
    cout<<"Vectorul de Tati: ";
    for(i=1; i<=n; i++) cout<<t[i]<<" ";
    cout<<endl;

    int final = 7;
    cout << "\nlant: " << endl;
    while (final)
    {
        cout << final << "\t";
        final = t[final];
    }

    return 0;
}


/*
 * 7 9

1 2 8

1 3 1

1 4 2

3 2 4

2 6 3

3 5 6

4 5 5

6 5 2

5 7 6
 * */