//
// Created by meadi on 11/13/2021.
//

//Nu merge pentru grafuri care nu sunt conexe. Trebuie adaugat un loop

#include <fstream>
#include <vector>
#include <utility>
#include <set>

using std::vector;
using std::set;

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

struct VertexInfo {
    int depth;
    int min_depth;
};

void dfs(vector<vector<int>> const &graph, int currentNode, int parent, int depth, vector<VertexInfo> &nodeInfo,
         vector<bool> &visited, set<int> &criticalNodes, vector<std::pair<int, int>> &criticalEdges) {
    visited[currentNode] = true;

    int dfsChildren = 0;

    int minDepth = depth;
    //Set this in the nodeInfo so that nodes further down can see this info
    nodeInfo[currentNode] = {depth,minDepth};
    for (auto const &rightEdge: graph[currentNode]) {
        if (!visited[rightEdge]) {
            dfsChildren++;
            dfs(graph, rightEdge, currentNode, depth + 1, nodeInfo, visited, criticalNodes, criticalEdges);
            if (minDepth > nodeInfo[rightEdge].min_depth) {
                minDepth = nodeInfo[rightEdge].min_depth;
            }
            if (depth < nodeInfo[rightEdge].min_depth) {
                criticalEdges.push_back({currentNode, rightEdge});
            }
            //Root treated separately
            if (depth <= nodeInfo[rightEdge].min_depth && parent != 0) {
                criticalNodes.insert(currentNode);
            }
        } else if (rightEdge != parent && nodeInfo[rightEdge].depth < minDepth) {
            minDepth = nodeInfo[rightEdge].depth;
        }
    }
    nodeInfo[currentNode] = {depth, minDepth};

    if(parent == 0 && dfsChildren > 1){
        criticalNodes.insert(currentNode);

    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream istream(argv[1]);
    std::ofstream ostream(argv[2]);
    auto graph = createGraphList(istream, false);
    vector<VertexInfo> vertexInfo(graph.size());
    vector<bool> visited(graph.size());
    set<int> criticalNodes;
    vector<std::pair<int, int>> criticalEdges;
    dfs(graph, 1, 0, 1, vertexInfo, visited, criticalNodes, criticalEdges);
    ostream << "Noduri critice:\n";
    for (auto const &node: criticalNodes) {
        ostream << node << " ";
    }
    ostream << "\n Muchii critice:\n";
    for (auto const&[left, right]: criticalEdges) {
        ostream << left << " " << right << "\n";
    }
    istream.close();
    ostream.close();
    return 0;
}

