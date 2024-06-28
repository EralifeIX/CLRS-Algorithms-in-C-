
#ifndef CLRSC___WEIGHTEDDIRECTEDGRAPH_H
#define CLRSC___WEIGHTEDDIRECTEDGRAPH_H

#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <map>
#include <stack>

using namespace std;

struct Edge {
    int StartVer, EndVer, Weight;
};

struct Node {
    int val;
    vector<pair<shared_ptr<Node>, int>> verteces;
    Node(int val) : val(val){}
};


class WeightedDirectedGraph {
public:
    int VerNum;
    map<int, shared_ptr<Node>> graph;
    vector<Edge> Edges;

    WeightedDirectedGraph(vector<Edge> edges, int verticesNum);

    const map<int, shared_ptr<Node>>& GetGraph() const;
    const int GetSize() const;
    const vector<Edge> GetEdges() const;
    void printGraph();
};




#endif //CLRSC___WEIGHTEDDIRECTEDGRAPH_H
