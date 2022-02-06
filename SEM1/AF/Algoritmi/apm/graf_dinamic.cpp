//
// Created by meadi on 11/9/2021.
//

// Inseram o noua muchie in APM
// Cautam muchia cu cost maxim din ciclul inchis de acea muchie si afisam costul
// Daca muchia aia are cost mai mare decat muchia inserata nou,
// o putem scoate si inlocui cu a doua muchie pentru a micsora costul appm-ului

#include <vector>
#include<fstream>
#include <utility>
#include <algorithm>
#include <iostream>
#include <math.h>


using std::vector;
using std::pair;

struct ConnectedComponentVertex {
    int parentIndex;
    int componentDepth;
};

// First is the vertex, second is the depth
pair<int, int> getRootVertex(vector<ConnectedComponentVertex> const &componentVertex, int vertex) {
    int current = vertex;
    int parent = componentVertex[vertex].parentIndex;
    while (parent != -1) {
        current = parent;
        parent = componentVertex[current].parentIndex;
    }

    return {current, componentVertex[current].componentDepth};

}

struct Edge {
    int leftVertex;
    int rightVertex;
    int cost;
};


// Return the parentIndex array and the connected components
// A -1 will mean a node is not in the tree, a 0 means that is the root, anything else is the parentIndex
pair<vector<Edge>, vector<ConnectedComponentVertex>> kruskal(vector<Edge> const &edges, int vertexCount,
                                                             vector<ConnectedComponentVertex> const &initialComponentVertex = {},
                                                             vector<Edge> const &initialSelectedEdges = {}) {
    // A vector that tells us another vertex from the same connected component with a given vertex
    vector<ConnectedComponentVertex> componentVertex = initialComponentVertex.empty()
                                                       ? vector<ConnectedComponentVertex>(vertexCount + 1, {-1, 1})
                                                       : vector<ConnectedComponentVertex>(
                    initialComponentVertex);
    vector<Edge> selectedEdges = initialSelectedEdges.empty() ? vector<Edge>() : vector<Edge>(initialSelectedEdges);
    if (vertexCount == 0) {
        return {selectedEdges, componentVertex};
    }
    for (auto const &edge: edges) {
        if (selectedEdges.size() == vertexCount - 1) {
            return {selectedEdges, componentVertex};
        }
        auto[leftVertexConnectedRoot, leftDepth] = getRootVertex(componentVertex, edge.leftVertex);
        auto[rightVertexConnectedRoot, rightDepth] = getRootVertex(componentVertex, edge.rightVertex);
        if (leftVertexConnectedRoot != rightVertexConnectedRoot) {


            //Add this edge to the tree
            selectedEdges.push_back(edge);

            //Merge the connected components
            if (leftDepth < rightDepth) {
                componentVertex[leftVertexConnectedRoot] = {rightVertexConnectedRoot, rightDepth};
            } else if (leftDepth > rightDepth) {
                componentVertex[rightVertexConnectedRoot] = {leftVertexConnectedRoot, leftDepth};
            } else {
                // The depth of the connected component increased
                componentVertex[rightVertexConnectedRoot] = {leftVertexConnectedRoot, leftDepth + 1};
                componentVertex[leftVertexConnectedRoot] = {-1, leftDepth + 1};
            }
        }

    }
    return {selectedEdges, componentVertex};
}


// From a list of edges that form a tree, make the parent array
vector<pair<int, int>> makeTree(vector<vector<pair<int, int>>> const &graph) {
    vector<pair<int, int>> parentArray(graph.size(), {-1, -1});
    vector<bool> done(graph.size());
    done[0] = true;
    done[1] = true;
    vector<Edge> bfsQueue;

    //Init the bfs queue
    for (auto[rightVertex, cost]: graph[1]) {
        bfsQueue.push_back({1, rightVertex, cost});
    }

    while (!bfsQueue.empty()) {
        auto currentEdge = bfsQueue.front();
        bfsQueue.erase(bfsQueue.begin());
        if (!done[currentEdge.rightVertex]) {
            done[currentEdge.rightVertex] = true;
            parentArray[currentEdge.rightVertex] = {currentEdge.leftVertex, currentEdge.cost};
            //Add all the edges of the rightVertex in the queue
            for (auto[rightVertex, cost]: graph[currentEdge.rightVertex]) {
                bfsQueue.push_back({currentEdge.rightVertex, rightVertex, cost});
            }
        }
    }

    return parentArray;

}


int findLCA(vector<pair<int, int>> const &tree, int a, int b) {
    vector<int> done(tree.size(), 0);

    int root;
    //See what nodes are between 'a' and the root
    int currentNode = a;
    while (currentNode != -1) {
        done[currentNode] = a;
        if (tree[currentNode].first == -1) {
            root = currentNode;
        }
        currentNode = tree[currentNode].first;
    }

    //The first node we encounter now will be LCA
    currentNode = b;
    while (currentNode != -1) {
        if (done[currentNode]) {
            return currentNode;
        }
        done[currentNode] = a;
        currentNode = tree[currentNode].first;
    }
    return root;
}

//Find max cost in tree between two nodes
int findMaxCost(vector<pair<int, int>> tree, int lowerNode, int higherNode) {
    int maxCost = INT_MIN;
    int currentNode = lowerNode;
    while (currentNode != higherNode) {
        auto[next, cost] = tree[currentNode];
        if (cost > maxCost) {
            maxCost = cost;
        }
        currentNode = next;
    }
    return maxCost;
}

vector<vector<pair<int, int>>> createGraphList(vector<Edge> const &edges, int vertexCount) {
    vector<vector<std::pair<int, int>>> list(vertexCount + 1);
    for (auto[leftNode, rightNode, cost]: edges) {
        list[rightNode].push_back({leftNode, cost});
        list[leftNode].push_back({rightNode, cost});
    }
    return list;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream f(argv[1]);
    std::ofstream g(argv[2]);

    vector<Edge> graph;
    int vertex, edgeCount;
    f >> vertex >> edgeCount;
    for (int i = 0; i < edgeCount; i++) {
        Edge edge;
        f >> edge.leftVertex >> edge.rightVertex >> edge.cost;
        graph.push_back(edge);
    }

    std::sort(graph.begin(), graph.end(), [](Edge a, Edge b) {
        return a.cost < b.cost;
    });
    auto[edges, _] = kruskal(graph, vertex);
    auto apmAsEdgeList = createGraphList(edges,vertex);
    auto apm = makeTree(apmAsEdgeList);

    Edge e;
    std::cin >> e.leftVertex >> e.rightVertex >> e.cost;
    int lca = findLCA(apm, e.leftVertex, e.rightVertex);
    int maxCost = std::max({e.cost, findMaxCost(apm, e.leftVertex, lca), findMaxCost(apm, e.rightVertex, lca)});

    g << "Max cost: " << maxCost << "\n";

    f.close();
    g.close();
    return 0;
}