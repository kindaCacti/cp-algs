//also an answer to CSES 1673
#include <bits/stdc++.h>

using namespace std;

#define int long long

vector<vector<int>> edgesList;
vector<int> valTo;
vector<bool> isInf, beenTo;
int n, m;

void belmanFord(){
    beenTo[0] = 1;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<edgesList.size(); j++){
            int from = edgesList[j][0];
            int to = edgesList[j][1];
            int val = edgesList[j][2];

            if(!beenTo[from]) continue;
            if(!beenTo[to]) valTo[to] = valTo[from] + val;
            valTo[to] = min(valTo[to], valTo[from] + val);
            beenTo[to] = 1;
        }
    }

    vector<int> nval(valTo);

    for(int i = 0; i<n; i++){
        for(int j = 0; j<edgesList.size(); j++){
            int from = edgesList[j][0];
            int to = edgesList[j][1];
            int val = edgesList[j][2];

            if(!beenTo[from]) continue;
            nval[to] = min(nval[to], nval[from] + val);
            if(nval[to] != valTo[to]) isInf[to] = 1;
            if(isInf[from]) isInf[to] = 1;
        }
    }
}

int32_t main(){
    cin>>n>>m;

    beenTo.assign(n, 0);
    isInf.assign(n, 0);
    valTo.assign(n, 0);
    int from, to, val;
    for(int i = 0; i<m; i++){
        cin>>from>>to>>val;
        from--; to--;

        edgesList.push_back({from, to, -val});
    }

    belmanFord();

    if(isInf[n-1]){
        cout<<"-1";
    }else{
        cout<<-valTo[n-1];
    }
    return 0;
}