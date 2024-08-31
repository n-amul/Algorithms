#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int nonConflict(vector<pair<int,pair<int,int>>>& jobs, int i){
    int l=0,r=i-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(jobs[mid].first <= jobs[i].second.first){//no conflict
            if(mid+1==i ||jobs[mid+1].first>jobs[i].second.first){
                return mid;
            }
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    return -1;//not found
}

long long findMaxWeight(vector<pair<int,pair<int,int>>>& jobs) {
    sort(jobs.begin(), jobs.end());
    int n = jobs.size();
    vector<long long> dp(n);

    dp[0] = jobs[0].second.second;
    for (int i = 1; i < n; ++i) {
        long long weight = jobs[i].second.second;
        int latestNonConflict = nonConflict(jobs, i);
        if (latestNonConflict != -1) {
            weight += dp[latestNonConflict];
        }
        dp[i] = max(weight,dp[i-1]);
    }
    return dp[n-1];
}

int main() {
    vector<long long> res;
    int instances;
    cin >> instances;
    while (instances--) {
        int numJobs;
        cin >> numJobs;
        vector<pair<int,pair<int,int>>> jobs(numJobs);//end, start, weight
        for (int i = 0; i < numJobs; ++i) {
            cin >> jobs[i].second.first >> jobs[i].first >> jobs[i].second.second;
        }
        res.push_back(findMaxWeight(jobs));
    }
    for(auto i:res){
        cout<<i<<endl;
    }
}
