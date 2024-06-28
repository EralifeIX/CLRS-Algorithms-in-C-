#include "NonWeightedGraph.h"

NonWeightedNode::NonWeightedNode() : val(0), verteces(0) {}
NonWeightedNode::NonWeightedNode(int val) : val(val), verteces(0) {}
NonWeightedNode::NonWeightedNode(int val, shared_ptr<NonWeightedNode> next) {
    val = val;
    verteces.push_back(next);
}

NonWeightedGraph::NonWeightedGraph(vector<Edge> edges, int verticesNum) {
    this->VerNum = verticesNum;

    for (int i = 0; i < edges.size(); i++) {
        int startVer = edges[i].StartVer;
        int endVer = edges[i].EndVer;

        if (graph.find(startVer) == graph.end()) {
            graph.insert(make_pair(startVer, make_shared<NonWeightedNode>(startVer)));
        }

        if (graph.find(endVer) == graph.end()) {
            graph.insert(make_pair(endVer, make_shared<NonWeightedNode>(endVer)));
        }

        graph.at(startVer)->verteces.push_back(graph[endVer]);
        graph.at(endVer)->verteces.push_back(graph[startVer]);
    }
    this->edges = edges;
}

const int NonWeightedGraph::getSize() const {
    return VerNum;
}

const map<int, shared_ptr<NonWeightedNode>>& NonWeightedGraph::getGraph() const {
    return graph;
}

const vector<Edge> &NonWeightedGraph::GetEdges() const {
    return edges;
}


void NonWeightedGraph::printGraph() {
    for (const auto& pair : graph) {
        int i = pair.first;
        shared_ptr<NonWeightedNode> node = pair.second;
        cout << i << " -> ";
        for (const auto& vertex : node->verteces) {
            cout << vertex->val << " ";
        }
        cout << endl;
    }
}
/*
void NonWeightedGraph::bfsTraversal(int start) {
    if (graph.find(start) == graph.end()) {
        cout << "Start vertex not found in the graph." << endl;
        return;
    }

    vector<bool> visited(VerNum, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        cout << current << " ";

        shared_ptr<Node> ptr = graph[current];
        while (ptr != nullptr) {
            int neighbor = ptr->val;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
            ptr = ptr->next;
        }
    }
    cout << endl;
}
*/