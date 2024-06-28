#include "../cp19 Graphs/WeightedDirectedGraph.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "EdgeUnion.h"
using namespace std;

vector<Edge> MSTKruskal(WeightedDirectedGraph& graph){
    vector<Edge> res;
    int VerticesNum = graph.GetSize();
    vector<Edge> edges = graph.GetEdges();

    //sort edges
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge&b){
        return a.Weight < b.Weight;
    });
    EdgeUnion eu(VerticesNum);
    //begin from the smallest Edge, if it forms a cycle, skip
    for(const Edge& edge : edges){
        int k = edge.StartVer;
        int j = edge.EndVer;

        int parentK = eu.FindParent(k);
        int parentJ = eu.FindParent(j);

        if(parentJ != parentK){
            res.push_back(edge);
            eu.UnionSets(parentK, parentJ);
        }
    }
    return res;
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

    vector<Edge> mst = MSTKruskal(graph);

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (const auto& edge : mst) {
        cout << edge.StartVer << " -- " << edge.EndVer << " == " << edge.Weight << endl;
    }

    return 0;
}

*/

