#include <iostream>
#include <set>
#include <stack>
#include <memory>
#include "../cp19 Graphs/WeightedDirectedGraph.h"


void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& Stack, const map<int, shared_ptr<Node>>& graph) {
    visited[v] = true;

    for (const auto& neighbor : graph.at(v)->verteces) {
        if (!visited[neighbor.first->val]) {
            topologicalSortUtil(neighbor.first->val, visited, Stack, graph);
        }
    }

    Stack.push(v);
}

vector<Edge> topologicalSort(WeightedDirectedGraph& Graph) {
    stack<int> Stack;
    vector<bool> visited(Graph.GetSize(), false);
    const auto& graph = Graph.GetGraph();

    for (const auto& pair : graph) {
        int v = pair.first;
        if (!visited[v]) {
            topologicalSortUtil(v, visited, Stack, graph);
        }
    }

    vector<int> sortedNodes;
    while (!Stack.empty()) {
        sortedNodes.push_back(Stack.top());
        Stack.pop();
    }

    // Extract edges from the topologically sorted nodes
    vector<Edge> sortedEdges;
    for (int i = 0; i < sortedNodes.size(); ++i) {
        int u = sortedNodes[i];
        if (graph.find(u) != graph.end()) {
            for (const auto& neighbor : graph.at(u)->verteces) {
                sortedEdges.push_back({u, neighbor.first->val, neighbor.second});
            }
        }
    }

    return sortedEdges;
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

    // Perform topological sort
    vector<Edge> sortedEdges = topologicalSort(graph);

    // Print the sorted edges
    cout << "Topologically Sorted Edges:" << endl;
    for (const auto& edge : sortedEdges) {
        cout << "(" << edge.StartVer << " -> " << edge.EndVer << ", weight: " << edge.Weight << ")" << endl;
    }

    return 0;
}
*/