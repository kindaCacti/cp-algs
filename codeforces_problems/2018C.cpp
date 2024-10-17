#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> edges;
vector<int> max_up, cdepth;
const int maxn = 1000000;

int dfs(int cn, int ln, int depth = 0){
    int tmp = depth;
    cdepth[depth]++;
    for(int nn : edges[cn]){
        if(nn == ln) continue;
        tmp = max(tmp, dfs(nn, cn, depth+1));
    }
    max_up[tmp]++;
    return tmp;
}

void solve(){
    int n;
    cin>>n;

    edges.assign(n+1, {});
    max_up.assign(n+1, 0);
    cdepth.assign(n+1, 0);

    for(int i = 1; i<n; i++){
        int a, b;
        cin>>a>>b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    dfs(1, 1);

    vector<int> presum1(n+1, 0), presum2(n+1, 0);
    presum1[0] = max_up[0];
    presum2[n] = cdepth[n];
    for(int i = 1; i<n; i++){
        presum1[i] = max_up[i] + presum1[i-1];
        presum2[n-i] = presum2[n-i+1] + cdepth[n-i];
    }

    int out = maxn;
    for(int i = 1; i<n; i++){
        out = min(out, presum1[i-1] + presum2[i+1]);
    }

    cout<<out<<"\n";
}

int main(){
    cin.tie(0); ios_base::sync_with_stdio(0);
    int t; cin>>t;
    while(t--) solve();
    return 0;
}