//
// Created by meadi on 11/27/2021.
//


#include <vector>
#include<fstream>
#include <utility>
#include <queue>
#include <math.h>

using std::vector;

struct PrimVertex {
    int vertex;
    int parent;
    int cost;
};

struct Edge {
    int leftVertex;
    int rightVertex;
    int cost;
};

struct Coord {
    int x;
    int y;
};

vector<Edge> prim(vector<vector<std::pair<int, int>>> const &graph, int vertexCount, int noSurse) {
    auto comp = [](PrimVertex const &a, PrimVertex const &b) { return b.cost < a.cost; };
    std::priority_queue<PrimVertex, std::vector<PrimVertex>, decltype(comp)> primVertexes(comp);

    //Sources have indices from 1 to how many
    for (int i = 1; i <= noSurse; i++) {
        primVertexes.push({i, 0, 0});

    }
    vector<bool> done(vertexCount + 1, false);
    vector<Edge> selectedEdges;
    int selectedVertexes = noSurse;
    while (selectedVertexes != vertexCount && vertexCount != 0) {
        auto currentVertex = primVertexes.top();
        primVertexes.pop();
        if (!done[currentVertex.vertex]) {
            if (currentVertex.parent != 0) {
                selectedEdges.push_back({currentVertex.parent, currentVertex.vertex, currentVertex.cost});
                selectedVertexes++;
            }
            for (auto const&[rightVertex, cost]: graph[currentVertex.vertex]) {
                if (!done[rightVertex]) { primVertexes.push({rightVertex, currentVertex.vertex, cost}); }
            }
            done[currentVertex.vertex] = true;
        }
    }
    return selectedEdges;
}


vector<vector<std::pair<int, int>>>
createGraphList(std::ifstream &input, int vertexes, int edges, vector<Coord> const &cladiri) {
    vector<vector<std::pair<int, int>>> list(vertexes+1);
    for (int i = 0; i < edges; i++) {
        int a, b;
        input >> a >> b;
        int cost = std::abs(cladiri[b].y - cladiri[a].y) + std::abs(cladiri[b].x - cladiri[a].x);
        list[a].push_back({b, cost});
        list[b].push_back({a, cost});

    }
    return list;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream f(argv[1]);
    std::ofstream g(argv[2]);

    vector<Coord> cladiri;

    cladiri.push_back({0, 0});

    int nSurse, nBlocuri, edges;
    f >> nSurse >> nBlocuri >> edges;
    for (int i = 0; i < nSurse; i++) {
        int x, y;
        f >> x >> y;
        cladiri.push_back({x, y});
    }

    for (int i = 0; i < nBlocuri; i++) {
        int x, y;
        f >> x >> y;
        cladiri.push_back({x, y});
    }
    auto graph = createGraphList(f, nSurse + nBlocuri, edges, cladiri);

    auto apm = prim(graph, nBlocuri + nSurse, nSurse);
    int costTotal = 0;
    for (auto e: apm) {
        costTotal += e.cost;
    }
    g << costTotal << "\n";
    for (auto const &[left, right, _]: apm) {
        g << left << ' ' << right << "\n";
    }
    f.close();
    g.close();
    return 0;
}

