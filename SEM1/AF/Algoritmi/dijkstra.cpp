#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const int inf = 1 << 30;

vector<vector<int>>  citire( int &n, int &m, const string &filename) {
    ifstream in(filename);
    in >> n >> m;
    vector<vector<int>> v(n + 1, vector<int>(n  +1, inf));
    int x, y, cost;
    for (int i = 1; i <= m; i++) {
        in >> x >> y >> cost;
        v[x][y] = cost;
        v[y][x] = cost;
    }
    return v;
}

int get_min_distance(vector<int> &dist, vector<bool> &visited) {
    int poz = -1, mini = inf;
    for(int i = 0; i < dist.size(); i++) {
        if (!visited[i] and dist[i] < mini) {// daca nu e vizitat si pozitia nu a fost actualizata sau distanta e mai mica, retinem poz
            poz = i;
            mini = dist[i];
        }
    }
    return poz;
}

void dijkstra(vector<vector<int>> &graph, int source) {
    vector<int> distance(graph.size(), inf);
    vector<bool> visited(graph.size(), false);

    distance[source] = 0;

    for (int i = 1; i < graph.size() ; i++) {

        int node = get_min_distance(distance, visited);
        visited[node] = true;

        for (int v = 1; v < graph.size(); v++) {
            if (!visited[v] and graph[node][v] and distance[node] != inf and distance[node] + graph[node][v] < distance[v]) {
                distance[v] = distance[node] + graph[node][v];
            }
        }
    }

    for (auto &x : distance)
        cout << x << " " ;
}

int main() {
    vector<vector<int>> graph;
    int n, m;
    graph = citire(n, m, "input.in");
    dijkstra(graph, 1);
}
