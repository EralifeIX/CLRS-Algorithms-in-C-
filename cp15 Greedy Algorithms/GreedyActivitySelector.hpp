#include<vector>

using namespace std;

vector<int> GreedyActivitySelector(const vector<int>& s, vector<int>& f){
    vector<int> res;
    int k = 0;
    for(int m = 1; m<s.size(); m++){
        if(s[m] >= f[m]){
            res.push_back(s[m]);
            k = m;
        }
    }
    return res;
}