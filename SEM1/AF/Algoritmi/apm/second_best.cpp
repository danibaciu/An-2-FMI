//
// Created by meadi on 11/20/2021.
//


#include <vector>
#include<fstream>
#include <utility>
#include <numeric>
#include <queue>

using std::vector;
using Graph = vector<vector<std::pair<int, int>>>;

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
            if (currentVertex.parent != 0) {
                selectedEdges.push_back({currentVertex.parent, currentVertex.vertex, currentVertex.cost});
            }
            for (auto const&[rightVertex, cost]: graph[currentVertex.vertex]) {
                if (!done[rightVertex]) { primVertexes.push({rightVertex, currentVertex.vertex, cost}); }
            }
            done[currentVertex.vertex] = true;
        }
    }
    return selectedEdges;
}

Graph createGraphList(std::ifstream &input, bool isOriented) {
    int edges, vertexes;
    input >> vertexes >> edges;
    Graph list(vertexes + 1);
    for (int i = 0; i < edges; i++) {
        int a, b, c;
        input >> a >> b >> c;
        list[a].push_back({b, c});
        if (!isOriented) {
            list[b].push_back({a, c});
        }

    }
    return list;
}

Graph createGraphList(vector<Edge> const &edges, bool isOriented, int vertexCount) {
    Graph list(vertexCount + 1);
    for (auto[left, right, cost]: edges) {
        list[left].push_back({right, cost});
        if (!isOriented) {
            list[right].push_back({left, cost});
        }

    }
    return list;
}

Graph makeDiff(Graph const &graph, vector<Edge> const &apm) {
    auto diffGraph = Graph(graph);
    for (auto[leftNode, rightNode, _]: apm) {
        // Clone the ref into a var to use inside lambda
        auto leftNodeVar = leftNode;
        auto rightNodeVar = rightNode;
        // remove this edge from the original graph
        auto it = std::find_if(diffGraph[leftNode].begin(), diffGraph[leftNode].end(), [&](std::pair<int, int> el) {
            // Get the edge between these 2 nodes in the graph
            return el.first == rightNodeVar;
        });
        diffGraph[leftNode].erase(it);

        // Remove it from the other list as well
        it = std::find_if(diffGraph[rightNode].begin(), diffGraph[rightNode].end(), [&](std::pair<int, int> el) {
            return el.first == leftNodeVar;
        });
        diffGraph[rightNode].erase(it);
    }
    return diffGraph;
}

// Get the most expensive edge between any 2 nodes
vector<vector<Edge>> getMostExpensiveEdges(vector<Edge> const &apm, int vertexCount) {
    vector<vector<Edge>> expensiveEdges(vertexCount + 1);
    // init the matrix
    for (int i = 1; i <= vertexCount; i++) {
        expensiveEdges[i] = vector<Edge>(vertexCount + 1);
    }

    // Turn edge list in graph
    auto apmAsGraph = createGraphList(apm, false, vertexCount);

    //For each node, traverse the apm
    for (int leftNode = 1; leftNode <= vertexCount; leftNode++) {
        // The BFS queue
        // Hold the node we are visiting next as well as the most expensive edge seen so far on this path
        vector<std::pair<int, Edge>> bfsQueue;
        vector<bool> done(vertexCount + 1, false);

        //init the queue
        bfsQueue.push_back({leftNode, {-1, -1, INT_MIN}});
        while (!bfsQueue.empty()) {
            auto[currentNode, expensiveEdge] = bfsQueue.front();
            done[currentNode] = true;
            bfsQueue.erase(bfsQueue.begin());

            for (auto[rightNode, cost]: apmAsGraph[currentNode]) {
                if (!done[rightNode]) {
                    if (cost > expensiveEdge.cost) {
                        bfsQueue.push_back({rightNode, {currentNode, rightNode, cost}});
                        expensiveEdges[leftNode][rightNode] = {currentNode, rightNode, cost};
                    } else {
                        bfsQueue.push_back({rightNode, expensiveEdge});
                        expensiveEdges[leftNode][rightNode] = expensiveEdge;
                    }
                }
            }
        }
    }
    return expensiveEdges;
}

vector<Edge> getSecondBest(Graph const &diffGraph, vector<Edge> const &apm, int vertexCount) {
    auto expensiveEdges = getMostExpensiveEdges(apm, vertexCount);
    Edge bestChoice{};
    Edge removedEdge{};
    int bestChoiceCostDiff = INT_MAX;
    for (int leftNode = 1; leftNode < diffGraph.size(); leftNode++) {
        for (auto[rightNode, cost]: diffGraph[leftNode]) {
            auto expensiveEdge = expensiveEdges[leftNode][rightNode];
            // If the diff between what we are adding and what we are removing is the best so far, save this edge
            if (cost - expensiveEdge.cost < bestChoiceCostDiff) {
                bestChoiceCostDiff = cost - expensiveEdge.cost;
                bestChoice = {leftNode, rightNode, cost};
                removedEdge = expensiveEdge;
            }
        }
    }
    vector<Edge> secondBest = vector(apm);
    auto expensiveEdgeIt = std::find_if(secondBest.begin(), secondBest.end(), [&](Edge current) {
        return current.leftVertex = removedEdge.leftVertex && current.rightVertex == removedEdge.rightVertex;
    });
    secondBest.erase(expensiveEdgeIt);
    secondBest.push_back(bestChoice);

    return secondBest;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream f(argv[1]);
    std::ofstream g(argv[2]);

    auto graph = createGraphList(f, false);

    auto apm = prim(graph, graph.size() - 1, 1);
    auto diffGraph = makeDiff(graph, apm);
    auto secondBest = getSecondBest(diffGraph, apm, graph.size() - 1);
    // Get the max edge between any 2 vertexes in apm
    // Go to through the diff graph and find the best edge to add
    for (auto const &[left, right, _]: secondBest) {
        g << left << ' ' << right << "\n";
    }
    f.close();
    g.close();
    return 0;
}
