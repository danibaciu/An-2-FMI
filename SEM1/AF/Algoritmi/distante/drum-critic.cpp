//
// Created by meadi on 12/11/2021.
//

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
using std::pair;

// Returns the edge lists and the list of durations
pair<vector<vector<int>>, vector<int>> createGraphList(std::ifstream &input) {
    int edges, vertexes;
    input >> vertexes;
    vector<int> durations(vertexes + 1);
    for (int i = 1; i <= vertexes; i++) {
        input >> durations[i];
    }
    input >> edges;
    vector<vector<int>> list(vertexes + 1);
    for (int i = 0; i < edges; i++) {
        int a, b;
        input >> a >> b;
        list[a].push_back(b);

    }
    return {list, durations};
}

vector<int> sort(vector<vector<int>> graph) {
    vector<int> grade(graph.size(), 0);
    grade[0] = -1;
    for (int i = 1; i < graph.size(); i++) {
        for (auto const &rightVertex: graph[i]) {
            grade[rightVertex]++;
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
        for (auto const rightVertex: graph[nodeLabel]) {
            grade[rightVertex]--;
            if (grade[rightVertex] == 0) {
                sortingQueue.push_back(rightVertex);
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

// returns the distance array and the index of the longest distance
pair<int, vector<DistanceNode>>
getDistance(vector<vector<int>> const &graph, vector<int> const &sorted, vector<int> const &durations) {
    vector<DistanceNode> distances(graph.size());

    //Init the distances
    for (int i = 1; i < durations.size(); i++) {
        distances[i] = {durations[i], -1};
    }

    for (auto vertex: sorted) {
        for (auto rightVertex: graph[vertex]) {
            if (distances[vertex].distance + durations[rightVertex] > distances[rightVertex].distance) {
                distances[rightVertex] = {distances[vertex].distance + durations[rightVertex], vertex};
            }
        }
    }

    int maxIndex = 1;
    for (int i = 1; i < distances.size(); i++) {
        if (distances[i].distance > distances[maxIndex].distance) {
            maxIndex = i;
        }
    }
    return {maxIndex, distances};

}

// Add recursion to print the correct way
void findPath(int start, vector<DistanceNode> const &distances, std::ofstream &output) {
    int current = start;
    while (current != -1) {
        output << current << " ";
        current = distances[current].parent;
    }
    output<<"\n";
}

void printSchedule(vector<DistanceNode> const &distances, std::ofstream &output){
    for(int i=1;i<distances.size();i++){
        auto [cost,parent] =  distances[i];
        if(parent == -1){
            output<<i<<": [0,"<<cost<<"]\n";
        }else{
            output<<i<<": ["<<distances[parent].distance<<","<<cost<<"]\n";
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream istream(argv[1]);
    std::ofstream ostream(argv[2]);
    auto[graph, costs] = createGraphList(istream);

    try {
        auto sorted = sort(graph);
        auto[maxIndex, distances] = getDistance(graph, sorted, costs);
        ostream << distances[maxIndex].distance << '\n';
        findPath(maxIndex,distances,ostream);
        printSchedule(distances,ostream);
    } catch (char *e) {
        ostream << e;
    }
    istream.close();
    ostream.close();
    return 0;
}
