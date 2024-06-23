//this is also a solution to CSES 1671
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pii pair<int, int>

vector<vector<pii>> edges;
vector<bool> visited;
vector<int> valTo;

int32_t main(){
    int n, m;
    cin>>n>>m;

    int from, to, val;
    edges.assign(n, {});
    visited.assign(n, 0);
    valTo.assign(n, -1);

    for(int i = 0; i<m; i++){
        cin>>from>>to>>val;
        from--; to--;
        edges[from].push_back({to, val});
    }

    priority_queue<pii, vector<pii>, greater<pii>> nodeQueue;
    nodeQueue.push({0, 0});
    valTo[0] = 0;

    while(nodeQueue.size()){
        auto cn = nodeQueue.top();
        nodeQueue.pop();

        if(visited[cn.second]) continue;

        visited[cn.second] = 1;
        valTo[cn.second] = cn.first;
        for(auto nn : edges[cn.second]){
            if(visited[nn.first]) continue;
            nodeQueue.push({nn.second + cn.first, nn.first});
        }
    }

    for(int i = 0; i<n; i++){
        cout<<valTo[i]<<" ";
    }

    return 0;
}