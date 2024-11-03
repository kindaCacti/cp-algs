#include <bits/stdc++.h>

using namespace std;

const int maxn = 10000007;
const int maxc = 20;

int sieve[maxn];
int presum[maxn][maxc];

void set_sieve(){
    for(int i = 2; i<maxn; i++){
        if(sieve[i] != 0) continue;
        for(int j = 2*i; j<maxn; j+=i){
            sieve[j]++;
        }
    }

    for(int i = 2; i<maxn; i++){
        if(sieve[i] == 0) sieve[i] = 1;
        for(int j = 0; j<maxc; j++){
            presum[i][j] = presum[i-1][j];
        }
        presum[i][sieve[i]]++;
    }
}

void solve(){
    int l, r, k;
    cin>>l>>r>>k;

    int out = presum[r][k] - presum[l-1][k];
    cout<<out<<"\n";
}

int main(){
    set_sieve();

    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int t;
    cin>>t;

    for(int i = 1; i<=t; i++){
        cout<<"Case #"<<i<<": ";
        solve();
    }
}