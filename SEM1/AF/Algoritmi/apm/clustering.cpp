//
// Created by meadi on 11/20/2021.
//


//
// Created by meadi on 11/9/2021.
//

//Kruskal cu k muchii date

#include <vector>
#include<fstream>
#include <utility>
#include <algorithm>
#include <string>
#include<iostream>
#include <map>


using std::vector;
using std::string;

struct ConnectedComponentVertex {
    int parentIndex;
    int componentDepth;
};

// First is the vertex, second is the depth
std::pair<int, int> getRootVertex(vector<ConnectedComponentVertex> const &componentVertex, int vertex) {
    int current = vertex;
    int parent = componentVertex[vertex].parentIndex;
    while (parent != -1) {
        current = parent;
        parent = componentVertex[current].parentIndex;
    }

    return {current, componentVertex[current].componentDepth};

}

struct Vertex {
    int index;
    string value;
};

struct Edge {
    Vertex leftVertex;
    Vertex rightVertex;
    unsigned int cost;
};


// Return the parentIndex array and the connected components
// A -1 will mean a node is not in the tree, a 0 means that is the root, anything else is the parentIndex
vector<ConnectedComponentVertex> kruskal(vector<Edge> const &edges, int vertexCount) {
    // A vector that tells us another vertex from the same connected component with a given vertex
    vector<ConnectedComponentVertex> componentVertex(vertexCount, {-1, 1});
    int k;
    std::cin >> k;

    int selectedEdgeCount = 0;

    if (vertexCount == 0) {
        return componentVertex;
    }
    for (auto const &edge: edges) {
        if (selectedEdgeCount == vertexCount - 1 - k) {
            return componentVertex;
        }
        auto[leftVertexConnectedRoot, leftDepth] = getRootVertex(componentVertex, edge.leftVertex.index);
        auto[rightVertexConnectedRoot, rightDepth] = getRootVertex(componentVertex, edge.rightVertex.index);
        if (leftVertexConnectedRoot != rightVertexConnectedRoot) {


            //Add this edge to the tree
            selectedEdgeCount++;

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
    return componentVertex;
}

unsigned int getEditDistance(string a, string b, std::map<std::pair<string, string>, unsigned int> &memo) {
    auto fromMemo = memo.find({a, b});
    if (fromMemo != memo.end()) {
        return fromMemo->second;
    }

    if (b.empty()) {
        memo.insert({{a, b}, a.size()});
        return a.size();
    } else if (a.empty()) {
        memo.insert({{a, b}, b.size()});
        return b.size();
    } else if (a[a.size() - 1] == b[b.size() - 1]) {
        auto res = getEditDistance(a.substr(0, a.size() - 1), b.substr(0, b.size() - 1), memo);
        memo.insert({{a, b}, res});
        return res;
    } else {
        int insert = getEditDistance(a, b.substr(0, b.size() - 1), memo);
        int remove = getEditDistance(a.substr(0, a.size() - 1), b, memo);
        int modify = getEditDistance(a.substr(0, a.size() - 1), b.substr(0, b.size() - 1), memo);
        unsigned int min = std::min({insert, remove, modify});
        memo.insert({{a, b}, min + 1});
        return min + 1;
    }
}

void printCluster(vector<ConnectedComponentVertex> const &componentVertex, vector<Vertex> const &vertexes,
                  int startVertexIndex,
                  std::ofstream &g) {
    vector<int> printQueue;
    printQueue.push_back(startVertexIndex);
    while (!printQueue.empty()) {
        int currentVertexIndex = printQueue.front();
        printQueue.erase(printQueue.begin());
        g << vertexes[currentVertexIndex].value << " ";
        for (int i = 0; i < componentVertex.size(); i++) {
            auto v = componentVertex[i];
            if (v.parentIndex == currentVertexIndex) {
                printQueue.push_back(i);
            }
        }
    }
    g << "\n";
}


int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream f(argv[1]);
    std::ofstream g(argv[2]);

    vector<Edge> graph;
    vector<Vertex> vertexes;
    // Index from 0 so add an empty vertex to fill the first pos
    vertexes.push_back({0, ""});
    int index = 1;
    vector<string> inputStrings;
    //Index from 1, put something on the first position
    inputStrings.push_back("");
    while (!f.eof()) {
        string a;
        f >> a;
        inputStrings.push_back(a);
        vertexes.push_back({index++, a});
    }
    //Get the edit duration between all strings
    for (int i = 1; i < inputStrings.size(); i++) {
        for (int j = i + 1; j < inputStrings.size(); j++) {
            std::map<std::pair<string, string>, unsigned int> memo;
            unsigned int editDistance = getEditDistance(inputStrings[i], inputStrings[j], memo);
            Vertex v = {i, inputStrings[i]};
            Vertex u = {j, inputStrings[j]};
            graph.push_back({v, u, editDistance});
        }
    }



    std::sort(graph.begin(), graph.end(), [](Edge const &a, Edge const &b) { return a.cost < b.cost; });

    auto cluster = kruskal(graph, inputStrings.size());


    for (int i = 1; i < cluster.size(); i++) {
        if (cluster[i].parentIndex == -1) {
            printCluster(cluster, vertexes, i, g);
        }
    }

    f.close();
    g.close();
    return 0;
}