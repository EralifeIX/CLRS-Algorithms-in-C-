#include <iostream>
#include <set>
#include <stack>
#include <memory>
#include "../cp19 Graphs/WeightedDirectedGraph.h"
using namespace std;

void BFS(int start, WeightedDirectedGraph& Graph){
    map<int,shared_ptr<Node>> graph = Graph.GetGraph();
    set<int> visited;
    queue<int> Queue;

    visited.insert(start);
    Queue.push(start);

    while (!Queue.empty()) {
        int current = Queue.front();
        Queue.pop();
        cout << current << " ";

        auto it = graph.find(current);
        if (it != graph.end()) {
            shared_ptr<Node> node = it->second;

            for(const auto& elem : node->verteces){
                if(visited.find(elem.first->val) == visited.end()){
                    visited.insert(elem.first->val);
                    Queue.push(elem.first->val);
                }
            }
        }
    }
    cout << endl;
}

/*
int main() {
    vector<Edge> edges = {
            {0, 1, 5}, {0, 2, 3}, {1, 3, 6},
            {2, 3, 7}, {3, 4, 4}
    };

    int verticesNum = 5;
    WeightedDirectedGraph graph(edges, verticesNum);

    graph.printGraph();

    cout << "BFS Traversal starting from vertex 0: ";
    BFS(0,graph);

    return 0;
}
*/