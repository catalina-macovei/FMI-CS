#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <queue>

//Prim Algorithm        O (m) complexitate in practica

using namespace std;

//distanta la cel mai apropiat vecin de s, tata, vf vizitate
int d[100], t[100], viz[100];

int main ()
{
    int n, m, s, i, j, x, y, c;
    vector< pair<int, int>> Graf[100]; //liste de adiacenta

    cin>>n>>m;
    for(i=0; i<m; i++)
    {
        cin>>x>>y>>c;
        Graf[x].push_back({y, c});
        Graf[y].push_back({x, c});
    }

    for(i=0; i<=n; i++) d[i]=100000;
    cout << "Introduceti Nod Start: "; cin >> s; d[s]=0;

    priority_queue< pair<int, int>> Q;
    Q.push({-d[s], s});
    while(!Q.empty())
    {
        x=Q.top().second; //nod
        Q.pop(); viz[x]++;
        for(auto i: Graf[x]) //vecinii lui x
        {
            y=i.first;
            j=i.second;
            if(viz[y]==0 && d[y]>j)
            {
                t[y]=x;
                d[y]=j;
                Q.push({-d[y], y});
            }
        }
    }
    //Afisare
    for(i=1; i<=n; i++) cout<<d[i]<<" ";
    cout<<endl;
    //Perechi Muchii APCM
    for(i=1; i<=n; i++)
        if(t[i]!=0) cout<<t[i]<<" "<<i<<endl;
    cout<<endl;

//    // lant
//    int final = 7;
//    while (final)
//    {
//        cout << final << "\t";
//        final = t[final];
//    }

    return 0;
}