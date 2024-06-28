
#include "EdgeUnion.h"
#include <algorithm>

EdgeUnion::EdgeUnion(int n) {
    parent.resize(n,0);
    rank.resize(n,0);
    for(int i = 0; i < n; i++){
        parent[i] = i;
    }
}

int EdgeUnion::FindParent(int n) {
    if (parent[n] != n) {
        parent[n] = FindParent(parent[n]); // Path compression
    }
    return parent[n];
}

void EdgeUnion::UnionSets(int k, int j) {
    int rootK = FindParent(k);
    int rootJ = FindParent(j);
    if(rootK != rootJ){
        if(rank[rootK] > rank[rootJ])
            parent[rootJ] = rootK;
        else if (rank[rootK] < rank[rootJ])
            parent[rootK] = rootJ;
        else{
            parent[rootJ] = rootK;
            rank[rootK]++;
        }
    }


}


