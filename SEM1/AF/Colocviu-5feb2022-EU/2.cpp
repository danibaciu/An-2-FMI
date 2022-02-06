//
// Created by danib on 2/5/2022.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

#define alb 0
#define gri 1
#define negru 2

using namespace std;

const int inf = 1 << 30;

vector<vector<pair<int,int>>>  citire( int &n, int &m, int &k, int &t1, int &t2, const string &filename) {
    ifstream in(filename);
    in >> n >> m;
    vector<vector<pair<int, int>>> v(n + 1);
    int x, y, cost;
    for (int i = 1; i <= m; i++) {
        in >> x >> y >> cost;
        v[x].push_back({y, cost});
    }
    in >> k;
    in >> t1 >> t2;
    return v;
}

bool dfs(vector<vector<pair<int,int>>> &vecini, int node, vector<int> &visited, vector<int> &topSort) {
    visited[node] = gri;
    for (auto &[vecin, cost] : vecini[node]) {
        if (visited[vecin] == alb) {
            dfs(vecini, vecin, visited, topSort);
        } else {
            if (visited[vecin] == gri) {
                return true; // avem ciclu
            }
        }
    }
    visited[node] = negru;
    topSort.push_back(node);
    return false;
}

void dags(vector<vector<pair<int,int>>> &vecini, int k, vector<int> &topsort, vector<int> &dist, vector<int> &dad) {

    for (int i = 1; i <= k; i++) {
        dist[i] = 0;
    }

    for (auto &nod : topsort) {
        for (auto &[vecin, cost] : vecini[nod]) {
            if (dist[nod] + cost < dist[vecin]) {
                dist[vecin] = dist[nod] + cost;
                dad[vecin] = nod;
            }
        }
    }
}


void getDistance(vector<vector<pair<int,int>>> graph, int start, int t1, int t2, vector<int>& distances, vector<int>& dad) {
    queue<int> q;

    for(int i = 1; i <= start; i++) {
        distances[i] = 0;
        dad[i] = 0;
        q.push(i);
    }
    while (!q.empty()) {
        auto nod = q.front();
        q.pop();
        for (auto &[vecin, cost]: graph[nod]) {
            if (distances[nod] + cost < distances[vecin]) {
                distances[vecin] = distances[nod] + cost;
                dad[vecin] = nod;
                q.push(vecin);
            }
        }
    }
}

int main() {
    int n, m, k, t1, t2;
    vector<vector<pair<int,int>>> vecini = citire(n, m, k, t1, t2,"input.in");
    vector<int> visited(n, alb), topsort;
    bool is_cycle = dfs(vecini, 1, visited, topsort);
    if (is_cycle)
    {
        cout << "avem ciclu !!!" << endl;
        return 0;
    }
    vector<int> dist(n  + 1, inf), dad(n + 1, 0);
    getDistance(vecini,k,t1,t2,dist,dad);
    int min_dist = inf, poz = -1;
    for (int i = 1; i <= k; i++) {
        if (dist[t1] < min_dist) {
            min_dist = dist[t1];
            poz = t1;
        }
        if (dist[t2] < min_dist) {
            min_dist = dist[t2];
            poz = t2;
        }
    }
    cout << "b) distanta de la S la T este " << min_dist << "\n";
    int t = poz;
    int s = t;
    while (s > k) {s = dad[s];}
    cout << "s="<<s <<" t ="<<t <<endl;
    cout << " drumul :";
    cout << poz << " ";
    while (poz > k) {
        poz = dad[poz];
        cout << poz << " ";
    }
    return 0;
}
/*
 * am facut dag uri dar n a iesit , deci trebuia bellman ford
 */