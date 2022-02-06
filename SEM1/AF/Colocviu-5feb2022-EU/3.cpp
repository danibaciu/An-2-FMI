//
// Created by danib on 2/5/2022.
//


#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<pair<int, int>>> citire(int &n, int &m, const string filename) {

    ifstream f(filename);
    f >> n;
    f >> m;
    vector<int> inDegree(n + 1), outDegree(m + 1);
    for (int i = 1; i <= n; i++) {
        f >> inDegree[i];
    }
    for (int i = 1; i <= m; i++) {
        f >> outDegree[i];
    }
    //construiesc graful si dupa adaug s si t
    vector<vector<pair<int, int>>> graph(n + m + 3, vector<pair<int, int>>(n + m + 3, {-1, -1}));
    for (int i = 1; i <= n; i++) {
        for (int j = n + 1; j <= n + m; j++) {
            if (i + m != j) {
                graph[i][j] = {0, 1};
            }
        }
    }
    //adaug s si t
    int s = m + n + 1, t = s + 1;
    for (int i = 1; i <= n; i++) {
        graph[s][i] = {0, outDegree[i]};
        graph[i + n][t] = {0, inDegree[i]};
    }
    return graph;
}



int EdmondsKarp(vector<vector<pair<int, int>>> &graph, int start, int end) {
    int flowValue = 0;

    for (int i = 1; i < graph.size(); i++) {
        if (graph[start][i].first != -1) {
            flowValue += graph[start][i].first;
        }
    }
    while (true) {
        vector<int> q;
        q.push_back(start);

        vector<int> dad(graph.size(), 0);
        vector<bool> visited(graph.size(), false);

        visited[start] = true;

        while (!q.empty()) {
            int current = q[0];
            q.erase(q.begin());
            for (int i = 1; i < graph.size(); i++) {

                if (graph[current][i].first < graph[current][i].second && !visited[i]) {
                    dad[i] = current;
                    visited[i] = true;
                    q.push_back(i);
                }

                if (graph[i][current].first > 0 && !visited[i]) {
                    dad[i] = -current;
                    visited[i] = true;
                    q.push_back(i);
                }

            }
        }

        if (!visited[end]) {
            return flowValue;
        }

        //mergem prin dad
        int current = end;
        int updateFlow = 9999;
        while (current != start) {
            int parent = dad[current];
            int residue;
            if (parent > 0) {
                residue = graph[parent][current].second - graph[parent][current].first;
                current = parent;
            } else {
                residue = graph[current][-parent].first;
                current = -parent;
            }

            if (residue < updateFlow) {
                updateFlow = residue;
            }
        }

        //actualizam
        current = end;
        while (current != start) {
            int parent = dad[current];
            if (parent > 0) {
                graph[parent][current].first += updateFlow;
                current = parent;
            } else {
                graph[current][-parent].first -= updateFlow;
                current = -parent;
            }
        }

        flowValue += updateFlow;
    }
}

int main() {
    int nrOspatari, vertexes;
    vector<vector<pair<int, int>>> g = citire(vertexes,nrOspatari,"input.in");
    int flowValue = EdmondsKarp(g, g.size() - 2, g.size() - 1);

    int k = 0;
    for (auto it = g.begin(); it != g.end(); it++) {
        int t1 = 0;
        for (auto t = it->begin(); t != it->end(); t++) {
            if (t1 == vertexes + nrOspatari + 2) {
                if (t->first < t->second) {
                    cout << "Imposibil";
                    return 0;
                }
            }
            t1++;
        }
        k++;
    }

    //afisarea de mese
    for (int i = 1; i <= vertexes; i++) {
        cout << "la masa " << i << " sunt ospatarii : ";
        for (int j = vertexes + 1; j <= nrOspatari + vertexes; j++) {
            if (g[i][j].first == 1) {
                cout << j - vertexes << " ";
            }
        }
        cout << endl;
    }
    return 0;
}