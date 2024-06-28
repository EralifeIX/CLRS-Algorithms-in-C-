#include<vector>
#include <climits>
#include<iostream>

using namespace std;

int MatrixChainMultiplyAUX(const vector<int>& arr, int i, int j, vector<vector<int>>& dp){
    if(i == j)
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];
    int minval = INT_MAX;

    for(int k = i; k <= j-1; k++){
        int res = MatrixChainMultiplyAUX(arr,i,k,dp) +
                MatrixChainMultiplyAUX(arr, k+1, j, dp) +
                arr[i-1]*arr[k]*arr[j];
        minval = min(minval, res);
    }
    return minval;
}

int MatrixChainMultiply(const vector<int>& arr, int n){
    vector<vector<int>> dp(n,vector<int>(n, -1));
    return MatrixChainMultiplyAUX(arr, 1, n-1, dp);
}

/*
int main() {

    vector<int> arr = {10, 20, 30, 40, 50};

    int n = arr.size();

    cout<<"The minimum number of operations is "<< MatrixChainMultiply(arr,n);

    return 0;
}
*/