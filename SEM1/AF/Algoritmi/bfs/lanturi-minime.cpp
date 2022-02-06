//
// Created by meadi on 11/6/2021.
//

// Toate bfs-urile intre 2 noduri
// Noduri cu mai multi parinti in parcurgere
#include <vector>
#include<fstream>
#include <iostream>
#include <numeric>
#include <algorithm>

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

struct Discovery {
    int node;
    int depth;
};

void
printWay(vector<vector<Discovery>> const &parrentTree, std::ofstream &output, int current, vector<int> &currentWay) {
    if (parrentTree[current][0].node == -1) {
        output << current << " ";
        std::for_each(currentWay.crbegin(), currentWay.crend(), [&](auto el) { output << el << " "; });
        output<<"\n";
    } else {
        currentWay.push_back(current);
        for (auto const &parent: parrentTree[current]) {
            printWay(parrentTree, output, parent.node, currentWay);
        }
        currentWay.pop_back();
    }
}

struct BFSQueueEntry {
    int depth;
    int node;
    int parent;
};


void
findWay(vector<vector<int>> const &adjecencyList, int startNode, int endNode,
        std::ofstream &output) {
    vector<BFSQueueEntry> bfsQueue;
    bfsQueue.push_back({0, startNode, -1});
    //When visiting a node, mark in this vector the node that discoverd it
    vector<vector<Discovery>> found(adjecencyList.size());
    found[startNode].push_back({-1, -1});
    while (!bfsQueue.empty()) {
        auto const current = bfsQueue.front();
        if (current.node == endNode) {
            //Print the way
            vector<int> currentWay;
            printWay(found, output, endNode,currentWay);
            break;
        }
        for (auto const &neighbour: adjecencyList[current.node]) {
            if (neighbour == current.parent) {
                continue;
            }
            if (found[neighbour].empty() ||
                (neighbour == endNode && current.depth == found[neighbour][0].depth)) {
                found[neighbour].push_back({current.node, current.depth});
                bfsQueue.push_back({current.depth + 1, neighbour, current.node});
            } else if (found[neighbour][0].depth == current.depth) {
                //We'll arrive in the neighbour with the same depth as the other nodes that discovered it so far
                found[neighbour].push_back({current.node, current.depth});
            }
        }
        bfsQueue.erase(bfsQueue.begin());
    }

}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream istream(argv[1]);
    std::ofstream ostream(argv[2]);
    auto graph = createGraphList(istream, false);
    vector<bool> controlPoints(graph.size());

    int startNode, endNode;
    std::cin >> startNode >> endNode;
    findWay(graph, startNode, endNode, ostream);
    istream.close();
    ostream.close();
    return 0;
}
