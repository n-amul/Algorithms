#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <sstream>

using namespace std;

int updateResidualGraph(int numberOfNodes, vector<vector<int> >& graph, vector<int>& path) {
    int flow = INT_MAX;
    //get bottleneck edge capacity
    for (int v = numberOfNodes - 1; path[v] >= 0; v = path[v]) {
        int u = path[v];
        flow = min(flow, graph[u][v]);
    }
    //update remaining capacity of rGraph & Graph
    for (int v = numberOfNodes - 1; path[v] >= 0; v = path[v]) {
        int u = path[v];
        graph[u][v] -= flow;
        graph[v][u] += flow;
    }
    return flow;
}

int BFS(int numberOfNodes, vector<vector<int> >& graph, vector<int>& path) {
    fill(path.begin(), path.end(), -1);
    vector<bool> visited(numberOfNodes, false);
    queue<int> que;

    que.push(0);
    visited[0] = true;

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int v = 0; v < numberOfNodes; ++v) {
            if (graph[u][v] > 0 && !visited[v]) {
                path[v] = u;

                if (v == numberOfNodes - 1) {
                    return true;
                }

                que.push(v);

                visited[v] = true;
            }
        }
    }

    return false;
}


int calculateMaxFlow(int numberOfNodes, vector<vector<int> >& graph) {
    vector<int> path(numberOfNodes);
    int max_flow = 0;

    while (BFS(numberOfNodes, graph, path)) {
        max_flow += updateResidualGraph(numberOfNodes, graph, path);
    }

    return max_flow;
}

int main() {
    int n;
    cin >> n;
    vector<int> res;
    while (n--) {
        int numberOfNodes, numberOfEdges;
        cin >> numberOfNodes >> numberOfEdges;
        
        vector<vector<int>> graph(numberOfNodes, vector<int>(numberOfNodes, 0));

        for (int i = 0; i < numberOfEdges; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            graph[u - 1][v - 1] += c;
        }

        res.push_back(calculateMaxFlow(numberOfNodes, graph));
    }
    for(auto i:res){
        cout<<i<<endl;
    }

    return 0;
}