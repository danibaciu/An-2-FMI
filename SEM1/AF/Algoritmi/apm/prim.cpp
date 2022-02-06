//
// Created by meadi on 11/20/2021.
//


#include <vector>
#include<fstream>
#include <utility>
#include <numeric>
#include <queue>

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

vector<Edge> prim(vector<vector<std::pair<int, int>>> const &graph, int vertexCount, int startVertex) {
    auto comp = [](PrimVertex const &a, PrimVertex const &b) { return b.cost < a.cost; };
    std::priority_queue<PrimVertex, std::vector<PrimVertex>, decltype(comp)> primVertexes(comp);
    primVertexes.push({startVertex, 0, 0});
    vector<bool> done(vertexCount + 1, false);
    vector<Edge> selectedEdges;
    while (selectedEdges.size() != vertexCount - 1 && vertexCount != 0) {
        auto currentVertex = primVertexes.top();
        primVertexes.pop();
        if (!done[currentVertex.vertex]) {
            if (currentVertex.parent != 0 ) {
                selectedEdges.push_back({currentVertex.parent, currentVertex.vertex, currentVertex.cost});
            }
            for (auto const&[rightVertex, cost]: graph[currentVertex.vertex]) {
                if(!done[rightVertex]) { primVertexes.push({rightVertex, currentVertex.vertex, cost}); }
            }
            done[currentVertex.vertex] = true;
        }
    }
    return selectedEdges;
}

vector<vector<std::pair<int, int>>> createGraphList(std::ifstream &input, bool isOriented) {
    int edges, vertexes;
    input >> vertexes >> edges;
    vector<vector<std::pair<int, int>>> list(vertexes + 1);
    for (int i = 0; i < edges; i++) {
        int a, b, c;
        input >> a >> b>>c;
        list[a].push_back({b, c});
        if (!isOriented) {
            list[b].push_back({a, c});
        }

    }
    return list;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream f(argv[1]);
    std::ofstream g(argv[2]);

    auto graph = createGraphList(f, false);

    auto apm = prim(graph, graph.size() - 1, 1);
    for (auto const &[left, right, _]: apm) {
        g << left << ' ' << right << "\n";
    }
    f.close();
    g.close();
    return 0;
}
