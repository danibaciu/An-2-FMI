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
graph createGraphMatrix(std::ifstream &input) {
    int vertexes;
    input >> vertexes;
    vector<int> inputDegrees(vertexes + 1);
    vector<int> outputDegrees(vertexes + 1);
    for (int i = 1; i <= vertexes; i++) {
        input >> inputDegrees[i];
    }
    for (int i = 1; i <= vertexes; i++) {
        input >> outputDegrees[i];
    }
    graph matrix;
    //Init the matrix
    for (int i = 0; i <= (vertexes * 2) + 2; i++) {
        // Mark the lack of an edge with {-1,-1}
        //Add 2 extra nodes for the source and destination of the flow
        matrix.push_back(vector<pair<int, int>>((vertexes * 2) + 3, {-1, -1}));
    }
    // The corresponding vertexes for input and output are k and k+vertex, indexed from 1
    for (int i = 1; i <= vertexes; i++) {
        for (int j = vertexes + 1; j <= vertexes * 2; j++) {
            if (i + vertexes != j) {
                matrix[i][j] = {0, 1};
            }
        }
    }

    //Add the source and destination
    int start = 2 * vertexes + 1;
    int end = start + 1;
    for (int i = 1; i <= vertexes; i++) {
        matrix[start][i] = {0, outputDegrees[i]};
        matrix[i + vertexes][end] = {0, inputDegrees[i]};
    }
    return matrix;
}


// Returns the amount of flow and the min cut. and updates the input graph with the right amount of flow
pair<int, vector<pair<int, int>>> makeMaxFlow(graph &g, int start, int end) {
    // We know the flow is valid so the initial flow amount is all the flow leaving the start node
    int flowValue = 0;
    for (int i = 1; i < g.size(); i++) {
        if (g[start][i].first != -1) { flowValue += g[start][i].first; }
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
    auto g = createGraphMatrix(istream);
    int vertexes = (g.size() - 3) / 2;
    auto[flowValue, minCut] = makeMaxFlow(g, g.size() - 2, g.size() - 1);
    //Print all the edges with flow on them
    for (int i = 1; i <= vertexes; i++) {
        for (int j = vertexes + 1; j <= 2 * vertexes; j++) {
            if (g[i][j].first == 1) {
                ostream << i << " " << j - vertexes << '\n';
            }
        }
    }
    return 0;
}

