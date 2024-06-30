// also an answer to CSES 1684
#include <bits/stdc++.h>
 
using namespace std;
 
struct SCC{
    vector<int> order;
    vector<vector<int>> edges, redges;
    vector<bool> used;
    vector<int> scc;
    int MAXN = 1e6+8;
 
    void restart(){
        edges.clear();
        edges.assign(MAXN, {});
        redges.clear();
        redges.assign(MAXN, {});
        used.clear();
        used.assign(MAXN, 0);
        scc.clear();
        scc.assign(MAXN, 0);
        order.clear();
    }
 
    void addEdge(int a, int b){
        edges[a].push_back(b);
        redges[b].push_back(a);
    }
 
    void dfs1(int sp){
        used[sp] = 1;
        for(int edg : edges[sp]){
            if(used[edg]) continue;
            dfs1(edg);
        }
        order.push_back(sp);
    }
 
    void dfs2(int a, int k){
        scc[k] = a;
        for(int edg : redges[k]){
            if(scc[edg]) continue;
            dfs2(a, edg);
        }
    }
};
 
struct SAT{
    SCC s;
    vector<int> answ;
    int SIZ = 1e6+8;
    int maxScc = -1;
    int done = 0;
    vector<bool> sccUsed;
 
    void set(){
        s.restart();
        maxScc = -1;
        answ.clear();
        answ.assign(SIZ, 0);
        done = 0;
        sccUsed.assign(SIZ, 0);
    }
 
    void addEdge(int a, bool nga, int b, bool ngb){
        a *= 2;
        b *= 2;
        a ^= nga;
        b ^= ngb;
        int nega = a ^ 1;
        int negb = b ^ 1;
        s.addEdge(nega, b);
        s.addEdge(negb, a);
    }
 
    bool doSAT(){
        for(int i = 0; i<s.MAXN; i++){
            if(s.used[i]) continue;
            s.dfs1(i);
        }
 
        int k = 0;
        while(s.order.size()){
            int tmp = s.order.back();
            s.order.pop_back();
            if(s.scc[tmp]) continue;
            k++;
            s.dfs2(k, tmp);
        }
 
        for(int i = 0; i<SIZ; i+=2){
            maxScc = max(maxScc, s.scc[i]);
            if(s.scc[i] != 0 && s.scc[i] == s.scc[i+1]){
                return false;
            }
        }
        return true;
    }
 
    vector<vector<int>> sccEdges;
    vector<vector<int>> cont;
 
    void sccDfs(int a){
        for(int edg : sccEdges[a]){
            if(sccUsed[edg]) continue;
            sccDfs(edg);
        }
        if(answ[cont[a].back()]!=0) return;
        if(done==SIZ) return;
        for(int ct : cont[a]){
            done += 2;
            answ[ct] = 1;
            answ[ct^1] = -1;
        }
    }
 
    void getAnsw(){
        sccEdges.assign(maxScc+3, {});
        cont.assign(maxScc+3, {});
        for(int i = 0; i<SIZ; i++){
            if(s.scc[i]==0){
                answ[i] = 1;
                done++;
            }
            cont[s.scc[i]].push_back(i);
            for(int edg : s.edges[i]){
                if(s.scc[edg] == s.scc[i]) continue;
                sccEdges[s.scc[i]].push_back(s.scc[edg]);
            }
        }
 
        for(int i = 1; i<maxScc+1; i++){
            if(done >= SIZ) continue;
            if(sccUsed[i]) continue;
            if(answ[cont[i].back()]!=0) continue;
            sccDfs(i);
        }
    }
 
 
};
 
int main(){
    int n, m;
    cin>>n>>m;
 
    SAT sat;
    sat.set();
    char a, c; int b, d;
    for(int i = 0; i<n; i++){
        cin>>a>>b>>c>>d;
        sat.addEdge(b, (a=='-'), d, (c=='-'));
    }
 
    bool poss = sat.doSAT();
    if(!poss){
        cout<<"IMPOSSIBLE";
        return 0;
    }
 
    sat.getAnsw();
    for(int i = 1; i<=m; i++){
        cout<<((sat.answ[i*2] == 1)?"+ ":"- ");
    }
    return 0;
}