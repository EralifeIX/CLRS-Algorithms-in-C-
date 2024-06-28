#include<vector>
#include<iostream>
using namespace std;

int CutRod(const vector<int>& p, int n){
    if(n == 0)
        return 0;

    int calculatedData = 0;
    for(int i = 0; i <= n; i++){
        int temp;
        temp = p[i] + CutRod(p, n - i - 1);
        if(calculatedData < temp)
            calculatedData = temp;
    }
    return calculatedData;
}

int MemorizedCutRodAUX(const vector<int>& p, int size, vector<int>& results){
    if(results[size] > 0)
        return results[size];
    int res = 0;
    if(size){
        for(int i = 0; i < size; i++){
            int temp = p[i] + MemorizedCutRodAUX(p, size -i -1, results);
            if(temp > res)
                res = temp;
        }

    }
    results[size] = res;
    return res;
}


int MemorizedCutRod(const vector<int>& p, int n){
    vector<int> results(n, 0);
    return MemorizedCutRodAUX(p, n, results);
}



/*
int main(){
    vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20};
    int res = MemorizedCutRod(prices, prices.size());
    cout << "Maximum Obtainable Value is " << res << endl;

    return 0;
};
*/