//
// Created by meadi on 12/28/2021.
//
#include <fstream>
#include <vector>
#include <utility>
#include <math.h>

using std::vector;
using std::pair;

using graph = vector<vector<pair<int, int>>>;

// The value of at index i and j mens that on the edge between i and j we have pair::first units of flow out of pair::second max capacity
graph createGraphMatrix(std::ifstream &input, int edges, int vertexes) {
    graph matrix;
    //Init the matrix
    for (int i = 0; i <= vertexes; i++) {
        // Mark the lack of an edge with {-1,-1}
        matrix.push_back(vector<pair<int, int>>(vertexes + 1, {-1, -1}));
    }
    for (int i = 0; i < edges; i++) {
        int a, b, curr, cap;
        input >> a >> b >> cap >> curr;
        matrix[a][b] = {curr, cap};
    }
    return matrix;
}

bool isValidFlow(graph const &g, int start, int end) {
    //For each node, check if the input flow = output flow
    for (int i = 1; i < g.size(); i++) {
        int input = 0;
        int output = 0;
        for (int j = 1; j < g.size(); j++) {
            if (g[i][j].first != -1 && g[i][j].second != -1) {
                output += g[i][j].first;
                //Check if the current flux value is greater than the capacity

                if (g[i][j].first > g[i][j].second) { return false; }
            }

            if (g[j][i].first != -1 && g[j][i].second != -1) {
                {
                    input += g[j][i].first;
                    //Check if the current flux value is greater than the capacity

                    if (g[j][i].first > g[j][i].second) {
                        return false;
                    }
                }
            }

        }

        //Special cases for start and end nodes
        if ((i == start && input != 0) || (i == end && output != 0) || (i != start && i != end && output != input)) {
            return false;
        }
    }
    return true;
}

// Returns the amount of flow and the min cut. and updates the input graph with the right amount of flow
pair<int, vector<pair<int, int>>> makeMaxFlow(graph &g, int start, int end) {
    // We know the flow is valid so the initial flow amount is all the flow leaving the start node
    int flowValue = 0;
    for (int i = 1; i < g.size(); i++) {
        if(g[start][i].first != -1) { flowValue += g[start][i].first; }
    }

    while (true) {
        vector<int> bfsQueue;
        bfsQueue.push_back(start);
        vector<int> parentArray(g.size(), 0);
        vector<bool> visited(g.size(), false);
        visited[start] = true;

        while (!bfsQueue.empty()) {
            int current = bfsQueue[0];
            bfsQueue.erase(bfsQueue.begin());
            for (int i = 1; i < g.size(); i++) {
                // Check for direct edge
                // A {-1,-1} pair aka no edge will fail the first condition and won't be considered
                if (g[current][i].first < g[current][i].second && !visited[i]) {
                    parentArray[i] = current;
                    visited[i] = true;
                    bfsQueue.push_back(i);
                }

                //Check for back edges
                // A {-1,-1} pair aka no edge will fail the first condition and won't be considered

                if (g[i][current].first > 0 && !visited[i]) {
                    //Set the parent as negative to know this was a back edge
                    parentArray[i] = -current;
                    visited[i] = true;
                    bfsQueue.push_back(i);
                }
            }
        }

        if (!visited[end]) {
            //We can't reach the end node anymore
            // Get the min cut and return
            vector<pair<int, int>> minCut;
            for (int i = 1; i < visited.size(); i++) {
                if (visited[i]) {
                    for (int j = 1; j < g.size(); j++) {
                        if (g[i][j].first != -1 && !visited[j]) {
                            //We have a direct edge from i to j
                            minCut.push_back({i, j});
                        }
                    }
                }
            }
            return {flowValue, minCut};
        }

        //Go back through the parentArray to determine the flow increment
        int current = end;
        int updateFlow = INT_MAX;
        while (current != start) {
            int parent = parentArray[current];
            int residue;
            if (parent > 0) {
                residue = g[parent][current].second - g[parent][current].first;
                current = parent;
            } else {
                residue = g[current][-parent].first;
                current = -parent;
            }

            if (residue < updateFlow) {
                updateFlow = residue;
            }
        }

        //Update the flow
        current = end;
        while (current != start) {
            int parent = parentArray[current];
            if (parent > 0) {
                g[parent][current].first += updateFlow;
                current = parent;
            } else {
                g[current][-parent].first -= updateFlow;
                current = -parent;
            }
        }

        flowValue += updateFlow;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream istream(argv[1]);
    std::ofstream ostream(argv[2]);
    int vertexes, start, end, edges;
    istream >> vertexes >> start >> end >> edges;
    auto g = createGraphMatrix(istream, edges, vertexes);
    auto isValid = isValidFlow(g, start, end);
    if (isValid) {
        ostream << "DA\n";
        auto[flowValue, minCut] = makeMaxFlow(g, start, end);
        ostream << flowValue << "\n";
        //Print the flow
        for (int i = 1; i < g.size(); i++) {
            for (int j = 1; j < g.size(); j++) {
                if (g[i][j].first != -1) {
                    ostream << i << " " << j << " " << g[i][j].first << "\n";
                }
            }
        }
        //Print the minCut
        ostream << flowValue << "\n";
        for (auto[left, right]: minCut) {
            ostream << left << " " << right << "\n";
        }

    } else {
        ostream << "NU\n";
    }
    return 0;
}

