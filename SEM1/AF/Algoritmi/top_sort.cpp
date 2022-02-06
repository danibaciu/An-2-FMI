#include <iostream>
#include <vector>

using namespace std;


void DFS(vector<vector<int>> &neighbours, vector<bool> &visited, vector<int> &nodes, int node) {
    visited[node] = true;
    for (auto &vecin : neighbours[node])
        if (!visited[vecin])
            DFS(neighbours, visited, nodes, vecin);
    nodes.push_back(node);
}

int main()
{
    int n, m;
    vector<bool> visited, grade;
    vector<vector<int>> neighbours;
    vector<int> nodes;
    int x,y,i;
    cin >> n >> m;
    neighbours.resize(n + 1);
    visited.resize(n + 1);
    grade.resize(n  + 1);
    for (i = 1; i <= m; ++i) {
        cin >> x >> y;
        neighbours[x].push_back(y);
        grade[y] = true;
    }
    for (i = 1; i <= n; ++i)
        if (!grade[i])
            DFS(neighbours, visited, nodes, i);


    for (i = nodes.size() - 1; i >= 0; i--)
        cout << nodes[i] << " ";
}