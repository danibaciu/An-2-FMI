//
// Created by meadi on 11/23/2021.
//
//
// Created by meadi on 11/23/2021.
//

//
// Created by meadi on 11/23/2021.
//

#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <queue>

using std::vector;
using std::set;

struct Vertex {
    int node;
    int duration;
};


vector<vector<Vertex>> createGraphList(std::ifstream &input, bool isOriented) {
    int edges, vertexes;
    input >> vertexes >> edges;
    vector<vector<Vertex>> list(vertexes + 1);
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


struct DistanceNode {
    int distance;
    int parent;
};


int getDistance(vector<vector<Vertex>> graph, int startNode, int endNode) {
    vector<DistanceNode> distances(graph.size(), {INT_MAX, -1});
    distances[startNode] = {0, 0};
    vector<int> updateQueue;
    updateQueue.push_back(startNode);
    while (!updateQueue.empty()) {
        auto leftEdge = updateQueue[0];
        updateQueue.erase(updateQueue.begin());
        for (auto[rightEdge, cost]: graph[leftEdge]) {
            if (distances[leftEdge].distance + cost < distances[rightEdge].distance) {
                distances[rightEdge] = {distances[leftEdge].distance + cost, leftEdge};
                updateQueue.push_back(rightEdge);
            }
        }
    }
    return distances[endNode].distance;
    return -1;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream istream(argv[1]);
    std::ofstream ostream(argv[2]);
    auto graph = createGraphList(istream, true);
    int start, end;
    istream >> start >> end;
    ostream << getDistance(graph, start, end);
    istream.close();
    ostream.close();
    return 0;
}

