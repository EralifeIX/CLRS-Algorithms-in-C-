#include "../cp19 Graphs/WeightedDirectedGraph.h"

vector<Edge> ArrToEdgesCoverter(const vector<int>& dist, const vector<int>& prev,
                        const WeightedDirectedGraph& graph, int src) {
    vector<Edge> shortestPathEdges;
    for (int v = 0; v < graph.GetSize(); ++v) {
        if (v != src && prev[v] != -1) {
            int u = prev[v];
            int weight = dist[v] - dist[u]; // Calculate the weight of the edge
            shortestPathEdges.push_back({u, v, weight});
        }
    }

    return shortestPathEdges;
}