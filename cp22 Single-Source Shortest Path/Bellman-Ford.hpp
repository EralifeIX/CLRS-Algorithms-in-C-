#include "../cp19 Graphs/WeightedDirectedGraph.h"
#include "climits"
#include <vector>

bool BellmanFord(const WeightedDirectedGraph& graph, int src,  vector<int>& dist) {
    const int size = graph.GetSize();
    dist[src] = 0;

    //Relax edges, give them their cost
    for(int i = 1; i < size; i++) {
        for(const Edge& edge : graph.GetEdges()) {
            int start = edge.StartVer;
            int end = edge.EndVer;
            int weight = edge.Weight;
            if(dist[start] != INT_MAX && dist[start] + weight < dist[end])
                dist[end] = dist[start] + weight;
        }
    }
    // Searching for negative-weight cycles
    for(const Edge& edge : graph.GetEdges()) {
        int start = edge.StartVer;
        int end = edge.EndVer;
        int weight = edge.Weight;
        if(dist[start] != INT_MAX && dist[start] + weight < dist[end])
            return false;
    }
    return true;
}


/*
int main() {
    vector<Edge> edges = {
        {0, 1, 5}, {0, 2, 3}, {1, 3, 6},
        {2, 3, 7}, {3, 4, 4}, {1, 2, 2}, {2, 4, 1}
    };

    int verticesNum = 5;
    WeightedDirectedGraph graph(edges, verticesNum);

    graph.printGraph();

    vector<int> distances = BellmanFord(graph, 0);

    if (!distances.empty()) {
        cout << "Vertex distances from start vertex 0:" << endl;
        for (int i = 0; i < distances.size(); ++i) {
            cout << "Vertex " << i << " : " << distances[i] << endl;
        }
    }

    return 0;
}
*/

