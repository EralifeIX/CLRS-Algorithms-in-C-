#include <vector>
using namespace std;

#ifndef CLRSC___EDGEUNION_H
#define CLRSC___EDGEUNION_H


class EdgeUnion {
public:
    EdgeUnion(int n);
    int FindParent(int n);
    void UnionSets(int k, int j);
private:
    vector<int> parent;
    vector<int> rank;
};


#endif //CLRSC___EDGEUNION_H
