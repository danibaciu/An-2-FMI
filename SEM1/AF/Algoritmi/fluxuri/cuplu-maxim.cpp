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
    int edges, vertexes;
    input >> edges >> vertexes;
    graph matrix;
    //Init the matrix
    for (int i = 0; i <= vertexes + 2; i++) {
        // Mark the lack of an edge with {-1,-1}
        //Add 2 extra nodes for the source and destination of the flow
        matrix.push_back(vector<pair<int, int>>(vertexes + 3, {-1, -1}));
    }
    for (int i = 0; i < edges; i++) {
        int a, b;
        input >> a >> b;
        matrix[a][b] = {0, 1};
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

//Perform a dfs to find a cycle
///Returns an odd length cycle
//If no odd length cycle found, return an empty vector
// Visited should be an empty list
vector<int> findCycle(graph const &g, int startNode, int currentNode, vector<int> &visited) {
    if (visited.empty()) {
        //Init the list
        visited = vector<int>(g.size() - 2, -1);
    }
    //Exclude the extra 2 nodes
    for (int i = 1; i < g.size() - 2; i++) {
        //Treat the graph as unordered
        if ((g[currentNode][i].first != -1 || g[i][currentNode].first != -1)
            //Don't go back to the parent
            && visited[currentNode] != i) {
            if (visited[i] == -1) {
                visited[i] = currentNode;
                auto cycle = findCycle(g, startNode,i, visited);
                if(!cycle.empty()){
                    return cycle;
                }

            }
                //Found a cycle
            else if(i == startNode){
                visited[i] = currentNode;
                //Find the cycle
                vector<int> cycle;
                int current = currentNode;
                while (current != i) {
                    cycle.push_back(current);
                    current = visited[current];
                }
                cycle.push_back(i);
                if (cycle.size() % 2 == 1) {
                    //It's odd length, return it
                    return cycle;
                }
            }
        }
    }
//No odd length cycle found
    return {
    };
}


// Check if the graph has an odd cycle
// If it has one, return a pair holding the cycle on the first position and an empty vector on the second
// If it does not have one, thus being bipartite, return the 2 partitions
pair<vector<int>, vector<int>> getPartitions(graph const &g) {
    //Ignore the extra 2 nodes at the end
    for (int i = 1; i < g.size() - 2; i++) {
        vector<int> visited;
        auto cycle = findCycle(g, i,i, visited);
        if (!cycle.empty()) {
            return {cycle, {}};
        }
    }
    //No odd length cycle found
    // Get the partitions

    //The first int is the node
    //The second is the partition number of the node
    vector<pair<int, int>> bfsQueue;
    vector<int> firstPartition;
    vector<int> secondPartition;
    vector<bool> visited(g.size() - 2, false);
    bfsQueue.push_back({1, 1});
    firstPartition.push_back(1);
    visited[1] = true;
    while (!bfsQueue.empty()) {
        auto[current, partition] = bfsQueue.front();
        bfsQueue.erase(bfsQueue.begin());
        for (int i = 1; i < g.size() - 2; i++) {
            //Treat the graph as unordered for the partitioning
            if ((g[current][i].first != -1 || g[i][current].first != -1) && !visited[i]) {
                visited[i] = true;
                if (partition == 1) {
                    bfsQueue.push_back({i, 2});
                    secondPartition.push_back(i);
                } else {
                    bfsQueue.push_back({i, 1});
                    firstPartition.push_back(i);
                }
            }
        }
    }

    return {firstPartition, secondPartition};
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream istream(argv[1]);
    std::ofstream ostream(argv[2]);
    auto g = createGraphMatrix(istream);
    auto[firstPartition, secondPartition] = getPartitions(g);
    if (secondPartition.empty()) {
        //This is not a bipartite graph
        //Print an odd length cycle from it
        for (int node: firstPartition) {
            ostream << node << " ";
        }
    } else {
        int start = g.size() - 2;
        int end = g.size() - 1;
        //Add the source and destination of the flow
        for (int node: firstPartition) {
            g[start][node] = {0, 1};
        }
        for (int node: secondPartition) {
            g[node][end] = {0, 1};
        }

        // If we have edges from the second partition to the first partition, those have to be flipped
        for (int y: secondPartition) {
            for (int x: firstPartition) {
                if (g[y][x].first != -1) {
                    g[y][x] = {-1, -1};
                    g[x][y] = {0, 1};
                }
            }
        }

        auto[flowValue, minCut] = makeMaxFlow(g, start, end);
        //Print all the edges with flow on them
        for (int i = 1; i < g.size() - 2; i++) {
            for (int j = 1; j < g.size() - 2; j++) {
                if (g[i][j].first == 1) {
                    ostream << i << " " << j << '\n';
                }
            }
        }
    }
    return 0;
}

