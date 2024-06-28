#include "../cp19 Graphs/WeightedDirectedGraph.h"
#include "ArrConverter.hpp"
#include "climits"
#include "algorithm"
#include "queue"
vector<int> Dijkstra(const WeightedDirectedGraph& graph, int src) {
    vector<int> dist(graph.GetSize(), INT_MAX);
    vector<int> prev(graph.GetSize(), -1); //previous node
    dist[src] = 0;
    using pdv = pair<int,int>; //pair of distance and vertex
    priority_queue<pdv, vector<pdv>, greater<pdv>> pq;
    pq.push({0,src});

    while (!pq.empty()) {
        int start = pq.top().second;
        int endDist = pq.top().first;
        pq.pop();

        if(endDist > dist[start]) continue;

        for(const auto& neighbour : graph.GetGraph().at(start)->verteces) {
            int end = neighbour.first->val;
            int weight = neighbour.second;
            if(dist[start] + weight < dist[end]) {
                dist[end] = dist[start] + weight;
                prev[end] = start;
                pq.push({dist[end], end});
            }
        }
    }
    // if you need vector<Edge>
    // return ArrToEdgesCoverter(dist,prev,graph,src);
    return dist;
}

//Dijkstra's algorithm as Johnson's subprogram
vector<int> Dijkstra(const WeightedDirectedGraph& graph, int source, const vector<int>& h) {
    int V = graph.GetSize();
    vector<int> dist(V, INT_MAX);
    dist[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& neighbor : graph.GetGraph().at(u)->verteces) {
            int v = neighbor.first->val;
            int weight = neighbor.second + h[u] - h[v];
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < V; ++i) {
        if (dist[i] != INT_MAX) {
            dist[i] = dist[i] + h[i] - h[source];
        }
    }

    return dist;
}
/*
int main() {
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

    // Perform Dijkstra's algorithm
    vector<Edge> shortestPathEdges = Dijkstra(graph, 0);

    // Print the shortest path edges
    cout << "Shortest path edges from vertex 0:" << endl;
    for (const auto& edge : shortestPathEdges) {
        cout << edge.StartVer << " -> " << edge.EndVer << " with weight " << edge.Weight << endl;
    }

    return 0;
}
*/