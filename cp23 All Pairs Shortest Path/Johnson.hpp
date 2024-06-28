#include "../cp19 Graphs/WeightedDirectedGraph.h"
#include "../cp22 Single-Source Shortest Path/Dijkstra.hpp"
#include "../cp22 Single-Source Shortest Path/Bellman-Ford.hpp"
#include <climits>
#include <memory>

vector<vector<int>> Johnson(const WeightedDirectedGraph& graph) {
    int size = graph.GetSize();
    vector<int> dist(size+1, INT_MAX);
    vector<int> reweightingValues(size,0);
    WeightedDirectedGraph temp = graph;

    // Add a new vertex connected to all vertices with zero-weight edges
    temp.graph[size] = make_shared<Node>(size);
    for(int i = 0; i < size; i++)
        temp.graph[size]->verteces.push_back({graph.graph.at(i), 0});


    if(!BellmanFord(temp, size, dist))
        throw runtime_error("Negative-weight cycle detected!");

    for(int i = 0; i < size; i++)
        reweightingValues[i] = dist[i];

    vector<vector<int>> ShortestPaths(size, vector<int>(size, INT_MAX));
    for(int i = 0; i < size; i++)
        ShortestPaths[i] = Dijkstra(graph, i, reweightingValues);
    return ShortestPaths;
}

/*
int main() {
    // Test graph definition
    vector<Edge> edges = {
        {0, 1, 5}, {0, 2, 3}, {1, 3, 6},
        {2, 3, 7}, {3, 4, 4}
    };

    int verticesNum = 5;
    WeightedDirectedGraph graph(edges, verticesNum);

    // Print the original graph for reference
    cout << "Original Graph:" << endl;
    graph.printGraph();
    cout << endl;

    // Run Johnson's algorithm
    try {
        vector<vector<int>> shortestPaths = Johnson(graph);

        // Print the shortest path matrix
        cout << "Shortest Path Matrix:" << endl;
        for (const auto& row : shortestPaths) {
            for (int dist : row) {
                if (dist == INT_MAX) {
                    cout << "INF ";
                } else {
                    cout << dist << " ";
                }
            }
            cout << endl;
        }
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
*/