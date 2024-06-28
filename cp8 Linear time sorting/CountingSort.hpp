#include<vector>
using namespace std;


void CountingSortVector(vector<int>& A){
    vector<int> B(A.size(), 0);
    vector<int> C(A.size(), 0);

    for(int i = 0; i < A.size(); i++) { B[A[i]]++; }
    for(int i = 1; i < A.size(); i++) { B[i] = B[i] + B[i-1]; }
    for(int i = A.size() - 1; i >= 0; i--){
        C[B[A[i]]] = A[i];
        B[A[i]]--;
    }
}