#include <iostream>
#include <vector>
#include "queue"
using namespace std;

int n,m, viz[230];
vector<pair<int, int>> a;
vector<int> m1,m2;
void citire()
{
    cin>>n>>m;
    int i,x,y;
    for(i=1; i<=m; i++)
    {
        cin>>x>>y;
        a.push_back(make_pair(x,y));
    }
}
int bf(int x)
{
    int bip=1;
    queue<int> c;
    c.push(x);
    viz[x]=1;
    while(!c.empty() && bip)
    {
        x=c.front();
        c.pop();
        for(auto pereche : a)
            if(pereche.first==x)
                if(viz[pereche.second]==0)
                {
                    c.push(pereche.second);
                    viz[pereche.second]=3-viz[x];
                }
                else if(viz[pereche.second]==viz[x])bip=0;
    }
    for(int i=0; i<n; i++){
        if(viz[i]==1)m1.push_back(i);
        else m2.push_back(i);
    }

    return bip;
}
int bipartit()
{
    int i;
    for(i=0;i<n;i++)
        if(viz[i]==0)
            if(bf(i)==0)return 0;
    return 1;
}
int main()
{
    citire();
    if(bipartit())
        cout<<"DA"<<endl;
    else cout<<"NU";
    return 0;
}