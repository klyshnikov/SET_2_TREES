#include <iostream>
#include <algorithm>
#include <vector>

struct Edge {
    int vertex1;
    int vertex2;
    double weight;
};

// Interface for UnionFind
class UnionFind {
public:
    void makeSet(int vertex) {
        return;
    }

    int find(int vertex) {
        return vertex;
    }

    void unionMethod(int vertex1, int vertex2) {
        return;
    }
};

std::vector<bool> visited;
std::vector<std::vector<std::pair<int, double>>> adjList;
std::vector<std::vector<std::pair<int, double>>> buildingAdjList;
std::vector<int> circle;

std::vector<int> dfs_circle(int vertex) {
    if (!visited[vertex]) {
        for (auto val : buildingAdjList[vertex]) {
            auto v = dfs_circle(val.first);
            if (!v.empty()) {
                // Find circle
                v.emplace_back(vertex);
                return v;
            }
        }
        return {};
    } else {
        return {vertex};
    }
}

std::vector<Edge> ALG_2(std::vector<Edge> edges, int V) {
    // Init
    std::vector<Edge> result;
    adjList = std::vector<std::vector<std::pair<int, double>>>(V);
    buildingAdjList = std::vector<std::vector<std::pair<int, double>>>(V);
    UnionFind unionFind;

    // Make AdjList
    for (Edge e : edges) {
        adjList[e.vertex1].emplace_back(e.vertex2, e.weight);
        adjList[e.vertex2].emplace_back(e.vertex1, e.weight);
    }

    //For all edges
    for (Edge e : edges) {
        visited = std::vector<bool>(V);
        circle = std::vector<int>();
        buildingAdjList[e.vertex1].emplace_back(e.vertex2, e.weight);
        buildingAdjList[e.vertex2].emplace_back(e.vertex1, e.weight);

        // Find circle
        if (unionFind.find(e.vertex1) == unionFind.find(e.vertex2)) {
            auto currentCircle = dfs_circle(e.vertex1);
            int maxVertex = -1;
            std::pair<int, int> maxEdge = {0, 0};
            for (int i = 0; i<currentCircle.size()-1; ++i) {
                if (buildingAdjList[currentCircle[i]][currentCircle[(i+1)%currentCircle.size()]].second > maxVertex) {
                    maxEdge = {i, (i+1)%currentCircle.size()};
                }
            }

            // Delete max from circle
            for (int i = 0; i<buildingAdjList[maxEdge.first].size(); ++i) {
                if (buildingAdjList[maxEdge.first][i].first == maxEdge.second) {
                    buildingAdjList[maxEdge.first].erase(buildingAdjList[maxEdge.first].begin()+i);
                }
            }

            for (int i = 0; i<buildingAdjList[maxEdge.second].size(); ++i) {
                if (buildingAdjList[maxEdge.second][i].first == maxEdge.first) {
                    buildingAdjList[maxEdge.second].erase(buildingAdjList[maxEdge.second].begin()+i);
                }
            }

        }
    }

    return result;
}
