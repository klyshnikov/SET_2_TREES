#include <iostream>
#include <algorithm>
#include "vector"

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

std::vector<Edge> ALG_2(std::vector<Edge> edges, int V) {
    // Init
    std::vector<Edge> result;
    adjList = std::vector<std::vector<std::pair<int, double>>>(V);
    UnionFind unionFind;

    // Make AdjList
    for (Edge e : edges) {
        adjList[e.vertex1].emplace_back(e.vertex2, e.weight);
        adjList[e.vertex2].emplace_back(e.vertex1, e.weight);
    }

    for (Edge e : edges) {
        visited = std::vector<bool>(V);
        if (unionFind.find(e.vertex1) != unionFind.find(e.vertex2)) {
            result.emplace_back(e);
            unionFind.unionMethod(e.vertex1, e.vertex2);
        }
    }

    return result;
}
