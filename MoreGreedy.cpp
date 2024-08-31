#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <limits>
#include<string>

using namespace std;

void getNumInput(int& num){
    cin >> num;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void getStringInput(string& str){
    getline(cin,str);
}
size_t split(const string &txt, vector<string> &strs, char ch){
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}
bool contains(vector<int>& arr,int n){
    for(auto i:arr)if(n==i)return 1;
    return 0;
}
int ffCache(vector<int>& request,int cacheSize){
    vector<int> cache(cacheSize);
    unordered_map<int,int> cacheIndex;//value , index in the cache
    unordered_map<int,stack<int>> indexs;
    
    int res=0;

    for(int i=request.size()-1;i>=0;i--){
        indexs[request[i]].push(i);
    }
    //first add all numbers until cache is full
    int index=0;
    while(cacheSize && index < request.size()){
        indexs[request[index]].pop();
        if(cacheIndex.find(request[index])==cacheIndex.end()){
            cache[--cacheSize]=request[index]; res++;
            cacheIndex[request[index]]=cacheSize; 
        }
        index++;
    }
    //now the cache is possibly full
    //[2,1]
    //2: 0 , 1: 1
    for(int i=index; i<request.size(); i++){
        indexs[request[i]].pop();
        if(contains(cache,request[i]))continue;
        

        //find delete element
        int delElement=-1,maxIndex=0;
        for(auto n:cache){
            if(indexs[n].empty()){
                //no longer used
                delElement=n;
                break;
            }
            if(maxIndex < indexs[n].top()){
                maxIndex=indexs[n].top();
                delElement=request[maxIndex];
            }
        }
        cache[cacheIndex[delElement]]=request[i]; res++;
        cacheIndex[request[i]]=cacheIndex[delElement];
    }
    return res;
}

int main(){
    int totalRequests=0;
    getNumInput(totalRequests);
    vector<int> res;
    while(totalRequests--){
        
        int cacheSize;getNumInput(cacheSize);
        int size;getNumInput(size);
        vector<int> request(size);
        
        string str;
        getStringInput(str);
        vector<string> strs;
        split(str,strs,' ');
        
        for(int i=0;i<size;i++)request[i]=stoi(strs[i]);
        res.push_back(ffCache(request,cacheSize));
    }
    for(auto i:res){
        cout<< i << endl;
    }
}