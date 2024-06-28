#include "WeightedDirectedGraph.h"

WeightedDirectedGraph::WeightedDirectedGraph(vector<Edge> edges, int verticesNum) {
    this->VerNum = verticesNum;

    for (int i = 0; i < edges.size(); i++) {
        int startVer = edges[i].StartVer;
        int endVer = edges[i].EndVer;
        int weight = edges[i].Weight;

        if (graph.find(startVer) == graph.end())
            graph[startVer] = make_shared<Node>(startVer);

        if (graph.find(endVer) == graph.end())
            graph[endVer] = make_shared<Node>(endVer);

        graph[startVer]->verteces.emplace_back(graph[endVer], weight);
    }
    this->Edges = edges;
}

const int WeightedDirectedGraph::GetSize() const {
    return VerNum;
}

const map<int, shared_ptr<Node>>& WeightedDirectedGraph::GetGraph() const {
    return graph;
}
const vector<Edge> WeightedDirectedGraph::GetEdges() const {
    return this->Edges;
}

void WeightedDirectedGraph::printGraph() {
    for (const auto& pair : graph) {
        int i = pair.first;
        shared_ptr<Node> ptr = pair.second;

        for (const auto& vertex : ptr->verteces) {
            cout << "point A: "<< ptr->val
            << " point B: " << vertex.first->val  << " Weight: " << vertex.second << endl;
        }
        cout << endl;
    }
}
/*
int main() {
    vector<Edge> edges = {
            {0, 1, 5}, {0, 2, 3}, {1, 3, 2},
            {2, 3, 7}, {3, 4, 4}
    };

    int verticesNum = 5;
    WeightedDirectedGraph graph(edges, verticesNum);

    graph.printGraph();

    return 0;
}
*/