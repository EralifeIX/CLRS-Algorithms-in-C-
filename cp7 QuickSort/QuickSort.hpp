#include<vector>
using namespace std;


void QsordVector(vector<int>& arr,int left, int right){
    int i = left, j = right;
    int temp;
    int mid = arr[(left + right) / 2];

    while (i <= j){
        while(arr[i] < mid) i++;
        while(arr[j] > mid) j--;
        if(i<=j){
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    if(left < j) QsordVector(arr, left, j);
    if(right > i) QsordVector(arr, i, right);

}