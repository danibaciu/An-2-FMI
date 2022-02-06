//
// Created by danib on 2/5/2022.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

const int inf = 1 << 30;

vector<vector<int>>  citire( int &n, int &m, int &s, const string &filename) {
    ifstream in(filename);
    in >> n >> m;
    vector<vector<int>> v(n + 1);
    int x, y, cost;
    for (int i = 1; i <= m; i++) {
        in >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    in >> s;
    return v;
}

void dfs(vector<vector<int>> &neighbours, int node, vector<bool> &viz) {
    viz[node] = true;

    for (auto &vecin : neighbours[node]) {
        if (!viz[vecin]) {
            dfs(neighbours,vecin, viz);
        }
    }
}

int distance_bfs(vector<vector<int>> &vecini, int source) {
    vector<int> dist(vecini.size(), inf);
    vector<bool>visited(vecini.size(), false);

    queue<int> q;
    q.push(source);

    dist[source] = 0;

    while (!q.empty()) {
        int nod = q.front();
        q.pop();
        visited[nod] = true;

        for (auto &vecin : vecini[nod]) {
            if (!visited[vecin] && dist[nod] + 1 < dist[vecin]) {
                dist[vecin] = dist[nod]  +1;
                q.push(vecin);
            }
        }
    }
    int maxi = 0;

    for (int i = 1; i < dist.size(); i++) {
        if (dist[i] > maxi && i != source)
            maxi = dist[i];
    }
    return maxi;
}

int main() {
    int n, m, s;
    vector<vector<int>> vecini = citire(n,m,s,"input.in");
    vector<bool> visited(n, false);
    vector<int> noduri;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            noduri.push_back(i);
            dfs(vecini, i, visited);
        }
    }
    cout << "cerinta a ) : \n";
    for (int i = 1; i < noduri.size(); i++) {
        int u = noduri[i - 1];
        int v = noduri[i];
        cout << u << " " << v << "\n";
        vecini[u].push_back(v);
        vecini[v].push_back(u);
    }
    //acum facem un bfs pt distante
    cout << "dist ceruta la b) este : " << distance_bfs(vecini, s);
    return 0;
}

