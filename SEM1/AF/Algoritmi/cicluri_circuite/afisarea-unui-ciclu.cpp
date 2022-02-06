//
// Created by meadi on 11/6/2021.
//

#include <vector>
#include<fstream>

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

void printCycle(vector<int> const &parrentTree, std::ofstream &output, int current, int endNode) {
    if (current == endNode) {
        output << current << " ";
    } else {
        printCycle(parrentTree, output, parrentTree[current], endNode);
        output << current << " ";
    }
}

bool findCycle(vector<vector<int>> const &graph, std::ofstream &output, int currentElement, vector<int> &checked) {
    for (auto const &vertex: graph[currentElement]) {
        //Check so that we don't go back into the parentIndex
        if (vertex != checked[currentElement]) {
            if (!checked[vertex]) {
                checked[vertex] = currentElement;
                auto res = findCycle(graph, output, vertex, checked);
                if (res) {
                    // Don't iterate further
                    return true;
                }
            } else {
                printCycle(checked, output, currentElement, vertex);
                output << vertex;
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream istream(argv[1]);
    std::ofstream ostream(argv[2]);
    auto graph = createGraphList(istream, false);
    vector<int> checked(graph.size());
    findCycle(graph, ostream, 1, checked);
    istream.close();
    ostream.close();
    return 0;
}
