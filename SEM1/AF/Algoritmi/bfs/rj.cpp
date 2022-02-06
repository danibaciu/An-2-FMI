//
// Created by meadi on 11/6/2021.
//

//2 BFS-uri simultane
#include <vector>
#include <fstream>
#include <algorithm>

using std::vector;
using std::max;

struct Coord {
    int x;
    int y;
};

struct Graph {
    vector<vector<char>> graph;
    Coord romeo;
    Coord juliet;
};

struct BFSQueueEntry {
    int depth;
    Coord point;
    char inserter;
};

vector<Coord> getNeightbours(Coord p, int n, int m) {
    vector<Coord> res;
    if (p.x - 1 >= 1) {
        res.push_back({ p.x - 1,p.y});
    }
    if (p.x + 1 <= m) {
        res.push_back({p.x + 1,p.y});
    }
    if (p.y - 1 >= 1) {
        res.push_back({p.x,p.y - 1 });
    }
    if (p.y + 1 <= n) {
        res.push_back({ p.x,p.y + 1});
    }

    if (p.x - 1 >= 1 && p.y - 1 >= 1) {
        res.push_back({p.x - 1,p.y - 1,});
    }
    if (p.x + 1 <= m && p.y - 1 >= 1) {
        res.push_back({p.x + 1,p.y - 1});
    }
    if (p.x - 1 >= 1 && p.y + 1 <= n) {
        res.push_back({p.x - 1,p.y + 1 });
    }
    if (p.x + 1 <= m && p.y + 1 <= n) {
        res.push_back({p.x + 1,p.y + 1 });
    }

    return res;
}

void
findWay(Graph g, std::ofstream &output) {
    vector<BFSQueueEntry> bfsQueue;
    bfsQueue.push_back({1, g.romeo,'R'});
    bfsQueue.push_back({1, g.juliet,'J'});
    //When visiting a node, mark in this vector the node that discoverd it
    vector<vector<char>> found;
    for (int i = 0; i < g.graph.size(); i++) {
        found.push_back(vector<char>(g.graph.size()));
    }
    found[g.romeo.y][g.romeo.x] = 'R';
    found[g.juliet.y][g.juliet.x] = 'J';
    BFSQueueEntry foundPoint = {0, 0, 0};
    while (!bfsQueue.empty() && foundPoint.point.x == 0 && foundPoint.point.y == 0) {
        auto const current = bfsQueue.front();
        auto const neighbours = getNeightbours(current.point, g.graph.size() - 1, g.graph.size()  -1);
        for (auto const &neighbour: neighbours) {
            //Check if it's valid
            if (g.graph[neighbour.y][neighbour.x] != 'X') {
                if (found[neighbour.y][neighbour.x] == 0) {
                    found[neighbour.y][neighbour.x] = current.inserter;
                    bfsQueue.push_back({current.depth + 1, neighbour,current.inserter});
                } else if (found[neighbour.y][neighbour.x] != current.inserter) {
                    //First point that both of them find
                    foundPoint = {current.depth + 1, neighbour,current.inserter};
                }
            }
        }
        bfsQueue.erase(bfsQueue.begin());
    }

    output << foundPoint.depth << " " << foundPoint.point.y << " " << foundPoint.point.x;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return -1;
    }
    std::ifstream istream(argv[1]);
    std::ofstream ostream(argv[2]);
    int n, m;
    istream >> n >> m;
    vector<vector<char>> matrix(n + 1, vector<char>(m + 1));
    Coord romeo;
    Coord juliet;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            istream >> matrix[i][j];
            if (matrix[i][j] == 'R') {
                romeo = {j, i};
            } else if (matrix[i][j] == 'J') {
                juliet = {j, i};
            }
        }
    }

    findWay({matrix, romeo, juliet}, ostream);
    return 0;

}
