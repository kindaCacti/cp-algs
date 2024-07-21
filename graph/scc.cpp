#include <bits/stdc++.h>

using namespace std;

#define int long long

vector<vector<int>> edges;
vector<vector<int>> redges;
vector<bool> visited;
vector<int> stos;
vector<int> component;
vector<vector<int>> components;

void dfs(int cn){
    visited[cn] = true;
    for(int nn : edges[cn]){
        if(visited[nn]) continue;
        dfs(nn);
    }
    stos.push_back(cn);
}

void dfs2(int cn, int k){
    component[cn] = k;
    components[k].push_back(cn);
    for(int nn : redges[cn]){
        if(component[nn] != -1) continue;
        dfs2(nn, k);
    }
}

signed main(){
    int n, m;
    cin>>n>>m;

    edges.assign(n, {});
    redges.assign(n, {});
    int a, b;
    for(int i = 0; i<m; i++){
        cin>>a>>b;
        a--; b--;
        edges[a].push_back(b);
        redges[b].push_back(a);
    }

    visited.assign(n, 0);
    for(int i = 0; i<n; i++){
        if(visited[i]) continue;
        dfs(i);
    }

    component.assign(n, -1);
    int k = 0;
    while(stos.size()){
        int tmp = stos.back();
        stos.pop_back();
        if(component[tmp] != -1) continue;
        components.push_back({});
        dfs2(tmp, k);
        k++;
    }

    return 0;
}