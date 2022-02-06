#include <bits/stdc++.h>

using namespace std;
bool graph_exists(vector <int> &a)
{
    while(1)
    {
        sort(a.begin(), a.end(), greater<int>());
        if(a[0]==0)return true;
        int v=a[0];
        a.erase(a.begin()+0);
        if(v>a.size())return false;
        for(int i=0;i<v;i++)
        {
            a[i]--;

            if(a[i]<0)return false;
        }
    }
}
int main()
{
    vector<int> a;
    int n;
    cin>>n;
    a.resize(n);
    for(int i=0;i<n;i++)cin>>a[i];
    if(graph_exists(a))cout<<"se poate construi un graf din secventa data";
    else cout<<"no se puede";
    return 0;
}
