#include <iostream>
#include<vector>
#include<unordered_map>

using namespace std;
inline size_t key(int i,int j) {return (size_t) i << 32 | (unsigned int) j;}

size_t knapsack(int c,int n,vector<pair<int,int>>& items,unordered_map<size_t,size_t>& memo){
    size_t k=key(n,c);
    if(memo.find(k)!=memo.end()){
        return memo[k];
    }
    if(c==0||n==-1){
        return 0;
    }else if(items[n].first > c){
        return knapsack(c,n-1,items,memo);
    }else{
        int w=items[n].first, p=items[n].second;
        memo[k] = max( p + knapsack(c-w,n-1,items,memo), knapsack(c,n-1,items,memo));
        return memo[k];
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int total; cin>>total;
    vector<size_t> res;
    while(total--){
        int n,capacity;
        cin >> n >> capacity;
        vector<pair<int,int>> items(n);//weight,profit
        for(int i=0;i<n;i++){
            cin >> items[i].first >> items[i].second;
        }
        unordered_map<size_t,size_t> memo;
        res.push_back(knapsack(capacity,n-1,items,memo));
    }
    for(auto l:res){
        cout<<(long long)l<<endl;
    }
}