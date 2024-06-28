#include <iostream>
#include <set>
#include <stack>
#include <iostream>
#include <memory>
#include <map>
#include "../cp19 Graphs/WeightedDirectedGraph.h"
using namespace std;


void DFS(int start, WeightedDirectedGraph& Graph){
    map<int,shared_ptr<Node>> graph = Graph.GetGraph();
    set<int> visited;
    stack<int> Stack;
    Stack.push(start);

    while (!Stack.empty()){
        int current = Stack.top();
        Stack.pop();

        if(visited.find(current) == visited.end()){
            visited.insert(current);
            cout << current << " ";
        }
        auto it = graph.find(current);
        if(it != graph.end()){
            shared_ptr<Node> node = it->second;
            for(const auto& elem : node->verteces ){
                    if (visited.find(elem.first->val) == visited.end()) {
                        Stack.push(elem.first->val);
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
    DFS(0,graph);

    return 0;
}
*/