#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
const int maxn = 1007;
int edges[maxn][maxn];
bool used[maxn];
vector<vector<int>> edg;
int n, m, t, ln;
int dfs(int cn){
    if(cn == ln){
        return 1;
    }
    used[cn] = true;
    for(int i : edg[cn]){
        if(i == cn) continue;
        if(used[i]) continue;
        if(edges[cn][i] > 0){
            edges[cn][i] = 0;
            if(int tmp = dfs(i)){
                edges[i][cn] = 1;
                return tmp;
            }
            edges[cn][i] = 1;
        }
    }
    return 0;
}
int floyd_fulkerson(int sn){
    int out = 0;
    while(dfs(sn)){
        out++;
        fill(used, used+maxn, 0);
    }
    return out;
}