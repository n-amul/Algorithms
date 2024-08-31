#include <iostream>
#include<vector>
#include<algorithm>

using namespace std;

long long g_cnt = 0;
void merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;   
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            g_cnt += (mid - left + 1);
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
}

void mergeSort(vector<int> &arr, int low, int high) {
    if (low >= high) return;
    int mid = (low + high) / 2 ;
    mergeSort(arr, low, mid);  
    mergeSort(arr, mid + 1, high); 
    merge(arr, low, mid, high);  
}

void Line_intersection(vector<int>& p,vector<int>& q){
    int n=p.size();
    vector<pair<int,int>> pts(n);
    for(int i=0;i<n;i++){
        pts[i]=make_pair(p[i],q[i]);
    }
    sort(pts.begin(),pts.end());
    vector<int> arr(n);
    for(int i=0;i<n;i++)arr[i]=pts[i].second;

    mergeSort(arr,0,n-1);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int total; cin>>total;
    vector<long long> res;
    while(total--){
        int n; cin>>n;
        vector<int> p(n);
        vector<int> q(n);
        for (int j = 0; j < n; j++) {
            cin >> p[j];
        }

        for (int j = 0; j < n; j++) {
            cin >> q[j];
        }
        Line_intersection(p,q);
        res.push_back(g_cnt);
        g_cnt=0;
    }
    for(auto l:res){
        cout<<(long long)l<<endl;
    }
}