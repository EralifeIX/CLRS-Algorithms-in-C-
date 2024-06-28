#include <set>
#include <map>
#include <memory>
#include <iostream>
#include "../cp19 Graphs/NonWeightedGraph.h"

void DFSHelper(int current, set<int>& visited, map<int,shared_ptr<NonWeightedNode>>& graph){
    visited.insert(current);
    cout << current << endl;
    shared_ptr<NonWeightedNode> ptr = graph[current];

    for (const auto& neighbor : ptr->verteces) {
        if (visited.find(neighbor->val) == visited.end()) {
            DFSHelper(neighbor->val, visited, graph);
        }
    }
}

void DFSNonWeighted(NonWeightedGraph& Graph, int start){
    set<int> visited;
    DFSHelper(start, visited, Graph.graph);
    cout << endl;
}
/*

int main() {
    vector<Edge> edges = {
            {0, 1}, {0, 2}, {1, 3},
            {2, 3}, {3, 4}
    };

    int verticesNum = 5;
    NonWeightedGraph graph(edges, verticesNum);

    graph.printGraph();


    cout << "DFS Traversal starting from vertex 0: ";
    DFSNonWeighted(graph, 0);

    return 0;
}
*/