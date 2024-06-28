#include "../cp19 Graphs/WeightedDirectedGraph.h"
#include "../cp4 Divide and Conquer/MatrixMultiply.hpp"
#include <climits>


//negative edges can be preset, but not negative-weight cycles



vector<vector<int>> FloydWarshall(const WeightedDirectedGraph& graph) {
    const int size = graph.GetSize();
    vector<vector<int>> dist(size, vector<int>(size, INT_MAX));

    //adding vertices
    for(const auto& pair : graph.GetGraph()) {
        int start = pair.first;
        dist[start][start] = 0;
        for(const auto& neighbour : pair.second->verteces) {
            int end = neighbour.first->val;
            int weight = neighbour.second;
            dist[start][end] = weight;
        }
    }

    for(int k = 0; k < size; k++) {
        for(int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    return dist;
}


