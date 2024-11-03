#include <bits/stdc++.h>

using namespace std;

const int maxn = 2007;
const int mod = 1000000007;

long long dp[maxn][maxn];

pair<int, int> convert_to_integers(string s){
    string tmp = "";
    int i = 0;
    for(i = 0; i<s.size(); i++){
        if(s[i] == '-') break;
        tmp.push_back(s[i]);
    }

    int o1 = stoi(tmp);
    tmp.clear();
    i++;

    for(; i<s.size(); i++){
        tmp.push_back(s[i]);
    }

    int o2 = stoi(tmp);

    return {o1, o2};
}

void solve(){
    for(int i = 0; i < maxn; i++){
        for(int j = 0; j<maxn; j++){
            dp[i][j] = 0;
        }
    }

    dp[0][0] = 1;
    dp[1][0] = 1;

    string scores;
    cin>>scores;
    pair<int, int> score = convert_to_integers(scores);

    for(int i = 0; i<=score.first; i++){
        for(int j = 0; j<=score.second; j++){
            if(i > j and j > 0){
                dp[i][j] += dp[i][j-1];
            }

            if(i-1 > j){
                dp[i][j] += dp[i-1][j];
            }

            dp[i][j] %= mod;
        }
    }

    int out1 = dp[score.first][score.second];

    for(int i = 0; i < maxn; i++){
        for(int j = 0; j<maxn; j++){
            dp[i][j] = 0;
        }
    }

    dp[0][0] = 1;

    for(int i = 0; i<=score.second; i++){
        for(int j = 0; j<=score.second; j++){
            if(i <= j-1 and j > 0){
                dp[i][j] += dp[i][j-1];
            }

            if(i > 0 and j >= i){
                dp[i][j] += dp[i-1][j];
            }

            dp[i][j] %= mod;
        }
    }

    int out2 = dp[score.second][score.second];
    cout<<out1<<" "<<out2<<"\n";
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int t;
    cin>>t;

    for(int i = 1; i<=t; i++){
        cout<<"Case #"<<i<<": ";
        solve();
    }
}