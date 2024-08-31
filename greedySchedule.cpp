#include <iostream>
#include <vector>
#include <limits>
#include<string>
#include<algorithm>

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
int greedySchedule(vector<pair<int,int>> schedule){
    int currentTime=0;
    int res=0;
    for(auto p:schedule){
        if(p.first>=currentTime){
            currentTime=p.second;
            res++;
        }
    }
    return res;
}
int main(){
    int totalSchedule=0;
    getNumInput(totalSchedule);

    vector<vector<pair<int,int>>> schedules(totalSchedule);
    for(int i=0;i<totalSchedule;i++){
        int numberOfElements=0;
        getNumInput(numberOfElements);
        vector<pair<int,int>> schedule;
        while(numberOfElements--){
            string str;
            getStringInput(str);
            vector<string> strs;
            split(str,strs,' ');
            schedule.push_back( make_pair( stoi(strs[0]), stoi(strs[1]) ) );
        }
        schedules[i]=schedule;
    }
    //sort each vector
    for(auto& v:schedules){
        sort(v.begin(), v.end(),[](auto& left,auto& right){
            return left.second < right.second;
        });
    }
    //get result for each vector
    for(auto v:schedules){
        cout<< greedySchedule(v) <<endl;
    }

}