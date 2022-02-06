//
// Created by meadi on 11/6/2021.
//

// BFS

#include <vector>
#include<fstream>
#include <iostream>

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


void printWay(vector<int> const &parrentTree, std::ofstream &output, int current) {
    if (parrentTree[current] == -1) {
        output << current << " ";
    } else {
        printWay(parrentTree, output, parrentTree[current]);
        output << current << " ";
    }
}

void
findWay(vector<vector<int>> const &adjecencyList, vector<bool> const &controlPoints, int startNode,
        std::ofstream &output) {
    vector<int> bfsQueue;
    bfsQueue.push_back(startNode);
    //When visiting a node, mark in this vector the node that discoverd it
    vector<int> found(adjecencyList.size());
    found[startNode] = -1;
    int foundPoint = 0;
    while (!bfsQueue.empty() && foundPoint == 0) {
        auto const current = bfsQueue.front();
        for (auto const &neighbour: adjecencyList[current]) {
            if (found[neighbour] == 0) {
                found[neighbour] = current;
                if (controlPoints[neighbour]) {
                    foundPoint = neighbour;
                } else {
                    bfsQueue.push_back(neighbour);
                }
            }
        }
        bfsQueue.erase(bfsQueue.begin());
    }

    //Print the way
    printWay(found, output, foundPoint);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream istream(argv[1]);
    std::ofstream ostream(argv[2]);
    auto graph = createGraphList(istream, false);
    vector<bool> controlPoints(graph.size());
    while (!istream.eof()) {
        int a;
        istream >> a;
        controlPoints[a] = true;
    }

    int startNode;
    std::cin >> startNode;
    findWay(graph, controlPoints, startNode, ostream);
    istream.close();
    ostream.close();
    return 0;
}
