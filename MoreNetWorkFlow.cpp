#include <iostream>
#include <climits>
#include <string>
#include <sstream>
#include <deque>
#include <vector>

using namespace std;

#define graphAcess(u,v) graph[u * num_nodes + v]

void initGraph(int num_nodes, int numOfnodeA, int numOfEdges, vector<int>& graph) {
    int src, dest;
    for (int i = 0; i < numOfEdges; i++) {
        cin >> src >> dest;

        dest += numOfnodeA;

        graphAcess(src, dest) = 1;
    }

    for (int i = 1; i <= numOfnodeA; i++) {
        graphAcess(0, i) = 1;
    }

    for (int i = numOfnodeA + 1; i < num_nodes - 1; i++) {
        graphAcess(i, num_nodes - 1) = 1;
    }
}

bool BFS(int num_nodes, vector<int>& graph, vector<int>& path) {
    deque<int> que;
    vector<bool> vis(num_nodes, false);
    que.push_back(0);

    vis[0] = true;
    path[0] = -1;

    while (!que.empty()) {
        int current = que.front();

        que.pop_front();

        for (int next = 0; next < num_nodes; next++) {
            if (!vis[next] && graphAcess(current, next) > 0) {
                que.push_back(next);
                path[next] = current;
                vis[next] = true;
            }
        }
    }

    return vis[num_nodes - 1];
}

int getCapacity(int num_nodes, vector<int>& graph, vector<int>& path) {
    int flow = INT_MAX;

    for (int v = num_nodes - 1; path[v] != -1; v = path[v]) {
        int u = path[v];

        flow = min(flow, graphAcess(u, v));
    }

    for (int v = num_nodes - 1; path[v] != -1; v = path[v]) {
        int u = path[v];
        graphAcess(u, v) -= flow;
        graphAcess(v, u) += flow;
    }

    return flow;
}

int maxFlowFF(int num_nodes, vector<int>& graph) {
    vector<int> path(num_nodes);
    int max_flow = 0;

    while (BFS(num_nodes, graph, path)) {
        max_flow += getCapacity(num_nodes, graph, path);
    }

    return max_flow;
}

int main() {
    int total;
    cin >> total;
    vector<pair<int,char>> res;
    
    while (total--) {
        int numOfnodeA, numOfnodeB, numOfEdges;
        cin >> numOfnodeA >> numOfnodeB >> numOfEdges;
        int numOfNodes = numOfnodeA + numOfnodeB + 2;

        vector<int> graph(numOfNodes * numOfNodes, 0);

        initGraph(numOfNodes, numOfnodeA, numOfEdges, graph);

        int max_flow = maxFlowFF(numOfNodes, graph);
        res.push_back(make_pair(max_flow,((numOfnodeA == numOfnodeB && max_flow == numOfnodeB) ? 'Y' : 'N')));
    }
    for(auto p:res){
        cout<<p.first<<" "<<p.second<<endl;
    }
    return 0;
}