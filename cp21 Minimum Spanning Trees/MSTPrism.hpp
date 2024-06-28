#include <vector>
#include <set>
#include <queue>
#include "../cp19 Graphs/WeightedDirectedGraph.h"

vector<Edge> MSTPrim(WeightedDirectedGraph& graph){
    vector<Edge> res;
    int size = graph.GetSize();
    auto VerticeMap = graph.GetGraph();
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
    vector<bool> inMST(size, false);

    inMST[0] = true;

    for(const auto& edge : VerticeMap.at(0)->verteces){
        pq.push({edge.second, {0, edge.first->val}});
    }
    while (!pq.empty() && res.size() < size ){
        auto current = pq.top();
        pq.pop();
        int weight = current.first;
        int k = current.second.first;
        int j = current.second.second;

        if(inMST[j]) continue;

        inMST[j] = true;
        res.push_back({k,j,weight});
        for(const auto& edge : VerticeMap.at(j)->verteces){
            if(!inMST[edge.first->val])
                pq.push({edge.second, {j, edge.first->val}});
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

    vector<Edge> mst = MSTPrim(graph);

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (const auto& edge : mst) {
        cout << edge.StartVer << " -- " << edge.EndVer << " == " << edge.Weight << endl;
    }

    return 0;
}


*/