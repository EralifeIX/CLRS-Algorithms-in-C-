#include <set>
#include "../cp19 Graphs/NonWeightedGraph.h"
#include <stack>
#include <queue>
using namespace  std;

void BFSNonWeighted(int start, const NonWeightedGraph& Graph) {
    map<int, shared_ptr<NonWeightedNode>> graph = Graph.getGraph();
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
            shared_ptr<NonWeightedNode> node = it->second;
            for (const auto& elem : node->verteces) {
                if (visited.find(elem->val) == visited.end()) {
                    visited.insert(elem->val);
                    Queue.push(elem->val);
                }
            }
        }
    }
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

    cout << "BFS Traversal starting from vertex 0: ";
    BFSNonWeighted(0, graph);

    return 0;
}
*/