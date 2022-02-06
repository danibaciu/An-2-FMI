//
// Created by meadi on 11/23/2021.
//

#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <numeric>

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

vector<int> sort(vector<vector<Vertex>> graph) {
    vector<int> grade(graph.size(), 0);
    grade[0] = -1;
    for (int i = 1; i < graph.size(); i++) {
        for (auto const &rightEdge: graph[i]) {
            grade[rightEdge.node]++;
        }
    }


    vector<int> sorted;
    vector<int> sortingQueue;
    for (int i = 0; i < graph.size(); i++) {
        if (grade[i] == 0) {
            sortingQueue.push_back(i);
        }
    }

    while (!sortingQueue.empty()) {
        auto nodeLabel = sortingQueue[0];
        sortingQueue.erase(sortingQueue.begin());
        sorted.push_back(nodeLabel);
        for (auto const &[rightEdge, _]: graph[nodeLabel]) {
            grade[rightEdge]--;
            if (grade[rightEdge] == 0) {
                sortingQueue.push_back(rightEdge);
            }
        }
        grade[nodeLabel] = -1;
    }

    auto isDone = [](int el) { return el == -1; };
    if (std::find_if_not(grade.begin(), grade.end(), isDone) != grade.end()) {
        throw "Nu se poate";
    }
    return sorted;
}

struct DistanceNode {
    int distance;
    int parent;
};

int getDistance(vector<vector<Vertex>> graph, vector<int> sorted, int startNode, int endNode) {
    vector<DistanceNode> distances(graph.size(), {INT_MAX, -1});
    distances[startNode] = {0, 0};
    auto startIt = std::find(sorted.begin(), sorted.end(), startNode);
    for (auto it = startIt; it != sorted.end(); ++it) {
        if (*it == endNode) {
            return distances[endNode].distance;
        }
        for (auto[rightEdge, cost]: graph[*it]) {
            if (distances[*it].distance + cost < distances[rightEdge].distance) {
                distances[rightEdge] = {distances[*it].distance + cost, *it};
            }
        }
    }
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
    try {
        auto sorted = sort(graph);
        ostream << getDistance(graph, sorted, start, end);
    } catch (char *e) {
        ostream << e;
    }
    istream.close();
    ostream.close();
    return 0;
}
