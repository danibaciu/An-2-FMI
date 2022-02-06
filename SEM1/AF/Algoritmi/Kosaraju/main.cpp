#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void dfs_save_stack (vector<vector<int>> &neighbours, vector<bool> &visited, int node, stack<int> &order) {
    visited[node] = true;
    for (int &vecin : neighbours[node]) {
        if (!visited[vecin])
            dfs_save_stack(neighbours, visited, vecin, order);
    }
    order.push(node);
}

void dfs_cout (vector<vector<int>> &neighbours, vector<bool> &visited, int node) {
    visited[node] = true;
    cout << node << " ";
    for (int &vecin : neighbours[node]) {
        if (!visited[vecin])
            dfs_cout(neighbours, visited, vecin);
    }
}

vector<vector<int>> transpose_graph (vector<vector<int>> &neighbours) {
    vector<vector<int>> graph_transpose(neighbours.size());
    for (int node = 0; node < neighbours.size(); node++) {
        for (int &vecin : neighbours[node])
            graph_transpose[vecin].push_back(node);
    }
    return graph_transpose;
}

void kosaraju (vector<vector<int>> &neighbours) {
    vector<bool> visited(neighbours.size(), false);
    stack<int> order;
    for (int node = 0; node < neighbours.size(); node++) {
        if (!visited[node])
            dfs_save_stack(neighbours, visited, node, order);
    }

    //now we reverse the graph
    vector<vector<int>> graph_transpose = transpose_graph(neighbours);

    visited.resize(neighbours.size(), false);

    while (!order.empty()) {
        int node = order.top();
        order.pop();

        if (!visited[node]) {
            dfs_cout(neighbours, visited, node);
            cout << "\n";
        }
    }

}

int main() {
    return 0;
}
