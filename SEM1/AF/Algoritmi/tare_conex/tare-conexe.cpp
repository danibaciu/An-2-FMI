//
// Created by meadi on 11/13/2021.
//
#include <fstream>
#include <vector>

using std::vector;

vector<vector<int>> createGraphList(std::ifstream &input, bool isOriented) {
    int edges, vertexes;
    input >> vertexes >> edges;
    vector<vector<int>> list(vertexes + 1);
    for (int i = 0; i < edges; i++) {
        int a, b;
        input >> a >> b;
        list[a].push_back(b);
        if (!isOriented) {
            list[b].push_back(a);
        }

    }
    return list;
}

vector<vector<int>> invertGraphList(vector<vector<int>> const &graph) {
    vector<vector<int>> inverted(graph.size());
    for (int i = 1; i < graph.size(); i++) {
        for (auto const &rightEdge: graph[i]) {
            inverted[rightEdge].push_back(i);
        }
    }
    return inverted;
}

void dfs(vector<vector<int>> const &graph, int currentNode, vector<int> &returnStack, vector<bool> &visited) {
    visited[currentNode] = true;
    for (auto const &rightEdge: graph[currentNode]) {
        if (!visited[rightEdge]) { dfs(graph, rightEdge, returnStack, visited); }
    }
    returnStack.push_back(currentNode);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream istream(argv[1]);
    std::ofstream ostream(argv[2]);
    auto graph = createGraphList(istream, true);
    auto invertedGraph = invertGraphList(graph);
    vector<bool> visited(graph.size(), false);
    //Ignore this entry
    visited[0] = true;
    vector<int> doneOrder;
    auto startNode = std::find(visited.begin(), visited.end(), false);
    do {
        if (startNode != visited.end()) {
            auto startNodeValue = std::distance(visited.begin(), startNode);
            dfs(graph, startNodeValue, doneOrder, visited);
        }
        startNode = std::find(visited.begin(), visited.end(), false);
    } while (startNode != visited.end());
    std::fill(visited.begin(), visited.end(), false);
    visited[0] = true;

    do {
        auto beginNode = doneOrder[doneOrder.size() - 1];
        doneOrder.pop_back();
        if (!visited[beginNode]) {
            vector<int> connectedComponent;
            dfs(invertedGraph, beginNode, connectedComponent, visited);
            for (auto const &edge: connectedComponent) {
                ostream << edge << " ";
            }
            ostream << "\n";
        }
    } while (!doneOrder.empty());

    istream.close();
    ostream.close();
    return 0;
}