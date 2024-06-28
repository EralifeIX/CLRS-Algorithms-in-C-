#include "../cp19 Graphs/WeightedDirectedGraph.h"
#include "../cp20 ElementaryGraphAlgorithms/TopologicalSort.hpp"
#include "ArrConverter.hpp"
#include "climits"
#include <stack>
#include <vector>


//Shortest path in Directed Acyclic Graph
vector<Edge> DagShortestPaths(const WeightedDirectedGraph& graph, int src) {
    vector<bool> visited(graph.GetSize(), false);
    vector<int> dist(graph.GetSize(), INT_MAX); //previous node
    vector<int> prev(graph.GetSize(), -1);
    stack<int> Stack;
    dist[src] = 0;

    for(int i = 0; i < graph.GetSize(); i++)
        if(visited[i] == false)
            topologicalSortUtil(i, visited, Stack, graph.GetGraph());

    while (!Stack.empty()) {
        int start = Stack.top();
        Stack.pop();

        if(dist[start] != INT_MAX) {
            for(const auto& neighbour : graph.GetGraph().at(start)->verteces) {
                int end = neighbour.first->val;
                int weight = neighbour.second;
                if(dist[start] + weight < dist[end])
                    dist[end] = dist[start] + weight;
                    prev[end] = start;
            }
        }
    }
    return ArrToEdgesCoverter(dist,prev,graph,src);
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

    // Perform DAG shortest paths algorithm
    vector<Edge> shortestPathEdges = DagShortestPaths(graph, 0);

    // Print the shortest path edges
    cout << "Shortest path edges from vertex 0:" << endl;
    for (const auto& edge : shortestPathEdges) {
        cout << edge.StartVer << " -> " << edge.EndVer << " with weight " << edge.Weight << endl;
    }

    return 0;
}
*/