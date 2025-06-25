#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
vector<vector<int>> edges;
vector<vector<pii>> parents;
vector<bool> used;
pii find_centroid(int cn, int ln, int subsize){
    int out = 1;
    for(int nn : edges[cn]){
        if(nn == ln) continue;
        if(used[nn]) continue;
        pii tmp = find_centroid(nn, cn, subsize);
        out += tmp.first;
        if(tmp.second >= 0) return {out, tmp.second};
    }
    if(out * 2 >= subsize) return {out, cn};
    return {out, -1};
}
int subtree_size(int cn, int ln){
    int out = 1;
    for(int nn : edges[cn]){
        if(nn == ln) continue;
        if(used[nn]) continue;
        out += subtree_size(nn, cn);
    }
    return out;
}
void update_parents(int cn, int ln, int c, int par, int cdist = 0){
    parents[cn][c] = {par, cdist};
    for(int nn : edges[cn]){
        if(nn == ln) continue;
        if(used[nn]) continue;
        update_parents(nn, cn, c, par, cdist + 1);
    }
}
void decompose(int sn, int dep){
    if(dep < 0) return;
    int subsize = subtree_size(sn, sn);
    int cent = find_centroid(sn, sn, subsize).second;
    update_parents(cent, cent, dep, cent);
    used[cent] = 1;
    for(int nn : edges[cent]){
        if(used[nn]) continue;
        decompose(nn, dep-1);
    }
}
void centroidal_decomposition(){
    int a = 1, it = 1;
    while((a<<=1) <= edges.size()) it++;
    parents.assign(edges.size(), vector<pii>(it, {0,0}));
    for(int i = 0; i<parents.size(); i++) for(int j = 0; j<it; j++) parents[i][j] = {i,0};
    decompose(0, it-1);
}