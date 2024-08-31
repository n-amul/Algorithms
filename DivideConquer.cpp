#include <iostream>
#include<vector>

using namespace std;

long long merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;   
    long long cnt = 0;
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            cnt += (mid - left + 1);
            right++;
        }
    }
    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
    return cnt;
}

long long mergeSort(vector<int> &arr, int low, int high) {
    long long cnt = 0;
    if (low >= high) return cnt;
    int mid = (low + high) / 2 ;
    cnt += mergeSort(arr, low, mid);  
    cnt += mergeSort(arr, mid + 1, high); 
    cnt += merge(arr, low, mid, high);  
    return cnt;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int total; cin>>total;
    vector<long long> res;
    while(total--){
        int size; cin>>size;
        vector<int> v(size); 
        vector<int> tmp(size);
        for(int i=0;i<size;i++){
            int num; cin>>num;
            v[i]=num;
        }
        res.push_back(mergeSort(v,0,size-1));
    }
    for(auto l:res){
        cout<< (long long)l<<endl;
    }
}

