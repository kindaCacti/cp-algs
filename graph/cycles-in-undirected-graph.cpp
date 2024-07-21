#include <bits/stdc++.h>

using namespace std;

#define int long long

vector<vector<int>> edges;
vector<vector<int>> cedges;
vector<vector<int>> ngraph;
vector<int> contains;
vector<int> depth;
vector<int> cc;
const int inf = 1000000;

int dfs(int cn, int ln, int d = 0){
    depth[cn] = d;

    int out = inf;
    for(int nn : edges[cn]){
        if(nn == ln) continue;
        if(depth[nn] != -1) out = min(out, depth[nn]);
        else out = min(out, dfs(nn, cn, d+1)); 
    }

    if(out < d){
        cedges[cn].push_back(ln);
        cedges[ln].push_back(cn);
    }

    return out;
}

void setCycles(int cn, int k){
    cc[cn] = k;

    for(int nn : cedges[cn]){
        if(cc[nn] != -1) continue;
        setCycles(nn, k);
    }
}

void solve(){
    int n, m; //number of nodes and edges
    cin>>n>>m;
    edges.assign(n, {});
    cedges.assign(n, {});
    depth.assign(n, -1);
    cc.assign(n, -1);

    int a, b;
    for(int i = 0; i<m; i++){
        cin>>a>>b;
        a--; b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    dfs(0, -1);
    int k = 0;
    for(int i = 0; i<n; i++){
        if(cc[i] != -1) continue;
        setCycles(i, k);
        k++;
    }

    contains.assign(k, 0);
    ngraph.assign(k, {});
    for(int i = 0; i<n; i++){
        contains[cc[i]]++;
        for(int node : edges[i]){
            if(cc[node] == cc[i] or node < i) continue;
            ngraph[cc[node]].push_back(cc[i]);
            ngraph[cc[i]].push_back(cc[node]);
        }
    }
}

signed main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int t; cin>>t;
    while(t--) solve();
    return 0;
}