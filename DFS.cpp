#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <limits>
#include<string>

using namespace std;

void getNumInput(int* num){
    cin >> (*num);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void getStringInput(string& str){
    getline(cin,str);
}

//copied function from stackoveflow
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch){
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
void DFS(unordered_map<string,vector<string>>& graph,string& start,unordered_map<string,bool>& vis,string& record){
    stack<string> st;
    st.push(start);
    while(!st.empty()){
        string top=st.top();
        st.pop();
        if(vis[top]==true)continue;
        
        vis[top]=true;
        record += top +" ";
        
        for(int i=graph[top].size()-1;i>-1;i--){
            if(vis.find(graph[top][i])==vis.end()){
                st.push(graph[top][i]);
            }
        }
    }
}
int main() {

    int totalGraph=0;
    getNumInput(&totalGraph);
    vector<unordered_map<string,vector<string>>> graphs;
    unordered_map<int,vector<string>> inputOrder;//graph#, inputorder

    //build # of totalGraphs
    for(int i=0;i<totalGraph;i++){
        int j=0;
        //build graph
        unordered_map<string,vector<string>> graph;
        getNumInput(&j);//# of j instances
       
        while(j--){
            string adjs;
            getStringInput(adjs);
            vector<string> strs;
            split(adjs,strs,' ');
            //if first time adding node
            if(graph.find(strs[0])==graph.end()){
                inputOrder[i].push_back(strs[0]);

                if(strs.size()==1)graph[strs[0]]=vector<string>(0);
                else graph[strs[0]]=vector<string>(strs.begin()+1,strs.end());
            }else{
                //if node already exsist ??
                for(int k=1;k<strs.size();k++)graph[strs[k]].push_back(strs[k]);
            }
        }
        //add a graph
        graphs.push_back(graph);
    }
    
    //travers each graph
    for(int i=0;i<graphs.size();i++){

        unordered_map<string,bool> vis;
        string record="";
        for(string str:inputOrder[i]){
            if(vis.find(str)==vis.end()){
                DFS(graphs[i],str,vis,record);
            }
        }
        cout << record.substr(0,record.size()-1) << endl;
    }
}