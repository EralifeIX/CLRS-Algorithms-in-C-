
#ifndef CLRSC___NONWEIGHTEDGRAPH_H
#define CLRSC___NONWEIGHTEDGRAPH_H


#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <queue>
#include <stack>

using namespace std;

struct NonWeightedNode {
    int val;
    vector<shared_ptr<NonWeightedNode>> verteces; //connected vertexes
    NonWeightedNode();
    NonWeightedNode(int val);
    NonWeightedNode(int val, shared_ptr<NonWeightedNode> next);
};

struct Edge {
    int StartVer;
    int EndVer;
};

class NonWeightedGraph {
    int VerNum;
    map<int, shared_ptr<NonWeightedNode>> graph;
    vector<Edge> edges;
public:

    NonWeightedGraph(vector<Edge> edges, int verticesNum);

    const int getSize() const;
    const map<int, shared_ptr<NonWeightedNode>>& getGraph() const;
    const vector<Edge>& GetEdges() const;
    void printGraph();
    void bfsTraversal(int start);
};


#endif //CLRSC___NONWEIGHTEDGRAPH_H
