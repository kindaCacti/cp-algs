#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    ll n, w, d;
    cin>>n>>w>>d;

    vector<ll> presum(n+1, 0);
    for(int i = 0; i<n; i++){
        ll a;
        cin>>a;
        presum[i+1] = presum[i] + a;
    }

    priority_queue<ll> greatest_removes;
    priority_queue<ll> to_remove;
    greatest_removes.push(0);

    ll ce = d-1;
    ll out = min(d, n);
    for(int i = 0; i<n-d+1; i++){
        while(ce+1<=n){
            ll tmp = max(greatest_removes.top(), presum[ce+1] - presum[ce+1-d]);
            if(presum[ce+1] - presum[i] - tmp <= w){
                greatest_removes.push(presum[ce+1] - presum[ce+1-d]);
                out = max(out, ce-i+1);
                ce++;
                continue;
            }
            break;
        }

        to_remove.push(presum[i+d] - presum[i]);

        while(to_remove.size() and to_remove.top() == greatest_removes.top()){
            to_remove.pop();
            greatest_removes.pop();
        }
    }

    cout<<out;
    return 0;
}