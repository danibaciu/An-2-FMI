#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

const int inf = 1<<25;

bool bfs(vector<vector<int>> rGraph, int source, int dest, vector<int> &dad) {
    vector<bool> visited(rGraph.size(), false);

    visited[source] = true, dad[source] = -1;

    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for ( int  i = 0; i < rGraph.size(); i++) {
            if (!visited[i] and rGraph[node][i] > 0) {
                if (i == dest) {
                    dad[i] = node;
                    return true;
                }
                q.push(i);
                dad[i] = node;
                visited[i] = true;
            }
        }
    }
    return false;
}


int ford_fulkerson(vector<vector<int>> &graph, int source, int dest) {
    vector<int> dad(graph.size(), inf);

    int max_flow = 0, u, v;

    while (bfs(graph, source, dest, dad)) {
        int path_flow = inf;

        for (v = dest; v != source; v = dad[v]) {
            u = dad[v];
            path_flow = min(path_flow, graph[u][v]);
        }//aici mergem pe calea gasita de bfs si facem minim de flux pe care il putem trimite


        for (v = dest; v != source; v = dad[v]) {
            u = dad[v];
            graph[u][v] -= path_flow;
            graph[v][u] += path_flow;
        }

        max_flow += path_flow;
        fill(dad.begin(), dad.end(), inf);
    }

    return max_flow;
}



int main() {
    vector<vector<int>> graph = { { 0, 16, 13, 0, 0, 0 }, { 0, 0, 10, 12, 0, 0 },
                                  { 0, 4, 0, 0, 14, 0 },  { 0, 0, 9, 0, 0, 20 },
                                  { 0, 0, 0, 7, 0, 4 },   { 0, 0, 0, 0, 0, 0 } };
    cout << "Max Flow: " << ford_fulkerson(graph, 0, 5);
    return 0;
}
