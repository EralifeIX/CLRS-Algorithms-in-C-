#include<iostream>
#include<climits>
#include<vector>
using namespace std;

void IntSwap(int& x, int& y){
    int temp = x;
    x = y;
    y = temp;
}

class MinHeap{
    vector<int> harr; //array of elements in heap
    int capacity;
    int HeapSize;
public:

    MinHeap(int capacity);
        //heapify subtree at x index
    void MinHeapify(int x);

    int parent(int x) {return (x-1) / 2;}

    int LeftBranch(int x){return (2*x +1);}

    int RightBranch(int x){return (2*x +2);}

    int ExtractMin();

    void DecreaseKey(int x, int NewValue);

    int GetMin(){return harr[0];}

    void DeleteKey(int x);
    void InsertKey(int x);

};


MinHeap::MinHeap(int size){
    HeapSize = 0;
    capacity = size;
    harr.resize(size);
}

void MinHeap::InsertKey(int x) {
    if(HeapSize == capacity){
        cerr<<"Heap is full";
        return;
    }
    HeapSize++;
    int i = HeapSize-1;
    harr[i] = x;

    //insert the x to the right place
    while (i != 0 && harr[parent(i)] > harr[i]){
        swap(harr[parent(i)], harr[i]);
        i = parent(i);
    }

}

void MinHeap::DecreaseKey(int x, int NewValue) {
    harr[x] = NewValue;
    while (x != 0 && harr[parent(x)] > harr[x]){
        swap(harr[parent(x)], harr[x]);
        x = parent(x);
    }
}

int MinHeap::ExtractMin() {
    if(HeapSize == 1 ){
        return harr[0];
    }
    if(!HeapSize){
        return INT_MAX;
    }
    int root = harr[0];
    harr[0] = harr[HeapSize-1];
    HeapSize--;
    MinHeapify(0);

    return root;

}

void MinHeap::DeleteKey(int i)
{
    DecreaseKey(i, INT_MIN);
    ExtractMin();
}


void MinHeap::MinHeapify(int x) {
    int left = LeftBranch(x);
    int right = RightBranch(x);
    int smallest = x;
    if(left < HeapSize && harr[left] < harr[right] ) smallest = left;
    if (right < HeapSize && harr[right] < harr[smallest]) smallest = right;
    if (smallest != x){
        swap(harr[x], harr[smallest]);
        MinHeapify(smallest);
    }
}



















