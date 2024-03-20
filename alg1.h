#include <iostream>
#include <algorithm>
#include "vector"

struct Edge {
    int vertex1;
    int vertex2;
    double weight;
};

bool sorter(const Edge& e1, const Edge& e2) {
    return e1.weight >= e2.weight;
}

std::vector<bool> visited;
std::vector<std::vector<std::pair<int, double>>> adjList;

void dfs(int vertex) {
    visited[vertex] = true;
    for (auto value : adjList[vertex]) {
        if (!visited[value.first]) {
            dfs(value.first);
        }
    }
}

std::vector<Edge> ALG_1(std::vector<Edge> edges, int V) {
    std::sort(edges.begin(), edges.end(), sorter);

    adjList = std::vector<std::vector<std::pair<int, double>>>(V);
    std::vector<Edge> result;

    for (Edge e : edges) {
        adjList[e.vertex1].emplace_back(e.vertex2, e.weight);
        adjList[e.vertex2].emplace_back(e.vertex1, e.weight);
    }

    for (Edge e : edges) {
        // Delete e
        for (int i = 0; i<adjList[e.vertex1].size(); ++i) {
            if (adjList[e.vertex1][i].first == e.vertex2) {
                adjList[e.vertex1].erase(adjList[e.vertex1].begin()+i);
            }
        }

        for (int i = 0; i<adjList[e.vertex2].size(); ++i) {
            if (adjList[e.vertex2][i].first == e.vertex1) {
                adjList[e.vertex2].erase(adjList[e.vertex2].begin()+i);
            }
        }

        visited = std::vector<bool>(V);
        for (int i = 0; i<V; ++i) {
            if (!visited[i])
            dfs(i);
        }

        for (bool v : visited) {
            if (!v) {
                // Other component -> push back
                adjList[e.vertex1].emplace_back(e.vertex2, e.weight);
                adjList[e.vertex2].emplace_back(e.vertex1, e.weight);
                result.emplace_back(e);
                break;
            }
        }
    }

    return result;
}
