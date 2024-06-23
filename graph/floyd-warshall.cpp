//this is also a solution for CSES 1672
#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
 
const int SIZ = 500;
 
int32_t main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, q;
    cin>>n>>m>>q;
 
    int adjacencyMatrix[SIZ][SIZ];
 
    for(int i = 0; i<SIZ; i++){
        for(int j = 0; j<SIZ; j++){
            adjacencyMatrix[i][j] = -1;
            if(i == j) adjacencyMatrix[i][j] = 0;
        }
    }
 
    int from, to, val;
    for(int i = 0; i<m; i++){
        cin>>from>>to>>val;
        from--; to--; 
        if(adjacencyMatrix[from][to] == -1)
            adjacencyMatrix[from][to] = val;
 
        if(adjacencyMatrix[to][from] == -1)
            adjacencyMatrix[to][from] = val;
 
        adjacencyMatrix[from][to] = min(val, adjacencyMatrix[from][to]);
        adjacencyMatrix[to][from] = min(val, adjacencyMatrix[to][from]);
    }
 
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            for(int k = 0; k<n; k++){
                if(i == j or j == k or i == k) continue;
                if(adjacencyMatrix[j][i] == -1) continue;
                if(adjacencyMatrix[i][k] == -1) continue;
 
                int tmp = adjacencyMatrix[j][i] + adjacencyMatrix[i][k];
 
                if(adjacencyMatrix[j][k] == -1) adjacencyMatrix[j][k] = tmp;
                adjacencyMatrix[j][k] = min(adjacencyMatrix[j][k], tmp);
            }
        }
    }
 
    while(q--){
        cin>>from>>to;
        from--; to--;
        cout<<adjacencyMatrix[from][to]<<"\n";
    }
 
    return 0;
}