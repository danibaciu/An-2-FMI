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


//Returns the graph and the number of edges
std::pair<vector<vector<Vertex>>, int> createGraphList(std::ifstream &input, bool isOriented) {
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
    return {list, edges};
}


struct DistanceNode {
    int distance;
    int parent;
};


int getDistance(vector<vector<Vertex>> graph, int edgeCount, int startNode, int endNode, std::ofstream &output) {
    vector<DistanceNode> distances(graph.size(), {INT_MAX, -1});
    distances[startNode] = {0, 0};
    vector<int> updateQueue;
    int updateCount = 0;
    int lastUpdated = 0;
    updateQueue.push_back(startNode);
    // This should stop after we updated all the edges (the number of vertexes) times
    while (!updateQueue.empty() && updateCount <= (edgeCount * graph.size() - 1)) {
        auto leftEdge = updateQueue[0];
        updateQueue.erase(updateQueue.begin());
        for (auto[rightEdge, cost]: graph[leftEdge]) {
            if (distances[leftEdge].distance + cost < distances[rightEdge].distance) {
                distances[rightEdge] = {distances[leftEdge].distance + cost, leftEdge};
                lastUpdated = rightEdge;
                updateCount++;
                updateQueue.push_back(rightEdge);
            }
        }
    }
    if (!updateQueue.empty()) {
        output << "Negative cycle: ";
        // There is a negative cycle
        //We go back the number of vertexes times from the last updated node to find a node on the cycle
        int current = lastUpdated;
        for (int i = 1; i < graph.size(); i++) {
            current = distances[current].parent;
        }
        //Now go back on the parent references until we find this node again. That's when the cycle is done
        int end = current;
        do {
            output << current << " ";
            current = distances[current].parent;
        } while (end != current);

        output << "\n";
        //Throw an error so we know to not output anything else
        throw -1;
    }
    return distances[endNode].distance;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream istream(argv[1]);
    std::ofstream ostream(argv[2]);
    auto[graph, edges] = createGraphList(istream, true);
    int start, end;
    istream >> start >> end;
    try {
        ostream << getDistance(graph, edges, start, end, ostream);
    } catch (int e) {
        //Do nothing
    }
    istream.close();
    ostream.close();
    return 0;
}

