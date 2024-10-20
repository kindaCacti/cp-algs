#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<ll, ll>;


ll get_dist(ll x, ll y){
    return (ll)x *(ll)x + (ll)y * (ll)y;
}

int sgn(ll val){
    if(val < 0) return -1;
    if(val == 0) return 0;
    return 1;
}

int is_left(pii p1, pii p2){
    ll cross_product = (ll)p1.first * (ll)p2.second - (ll)p1.second * (ll)p2.first;
    return sgn(cross_product);
}

struct SortByAngle{
    bool operator()(pii& left, pii& right){
        if(sgn(left.second) != sgn(right.second)){
            if(sgn(left.second) < 0) return false;
            if(sgn(right.second) < 0) return true;
        }

        double cos1 = (double)left.first / sqrt(get_dist(left.first, left.second));
        double cos2 = (double)right.first / sqrt(get_dist(right.first, right.second));

        if(sgn(left.second) >= 0){
            if(cos1 >= cos2) return true;
            return false;
        }

        if(cos1 <= cos2) return true;
        return false;
    }
};

pii normalize_vector(pii vec){
    ll gcd = __gcd(vec.first, vec.second);
    gcd = abs(gcd);
    return {vec.first / gcd, vec.second / gcd};
}

int main(){
    cin.tie(0); ios_base::sync_with_stdio(0);
    int n;
    cin>>n;

    vector<pii> positions;
    map<pii, int> existing_vectors;
    for(int i = 0; i<n; i++){
        ll x, y;
        cin>>x>>y;
        if(x == 0 and y == 0) continue;
        pii normalized_vector = normalize_vector({x, y});
        if(existing_vectors.find(normalized_vector) == existing_vectors.end()){
            existing_vectors[normalized_vector] = positions.size();
            positions.push_back({0,0});
        }
        positions[existing_vectors[normalized_vector]].first += x;
        positions[existing_vectors[normalized_vector]].second += y;
    }

    sort(positions.begin(), positions.end(), SortByAngle());

    int ce = 0;
    pii going_to = {0,0};
    ll out = 0;
    n = positions.size();
    for(int i = 0; i<n; i++){
        while(is_left(positions[i], positions[ce]) >= 0){
            going_to.first += positions[ce].first;
            going_to.second += positions[ce].second;
            ce++;
            ce %= n;
            out = max(out, get_dist(going_to.first, going_to.second));
            if(ce == i) break;
        }
        going_to.first -= positions[i].first;
        going_to.second -= positions[i].second;
        out = max(out, get_dist(going_to.first, going_to.second));
    }

    for(pii& position : positions){
        position.second *= -1;
    }

    sort(positions.begin(), positions.end(), SortByAngle());
    ce = 0;
    going_to = {0,0};
    for(int i = 0; i<n; i++){
        while(is_left(positions[i], positions[ce]) >= 0){
            int tmp = (ce + 1)%n;
            if(tmp == i) break;
            going_to.first += positions[ce].first;
            going_to.second += positions[ce].second;
            ce = tmp;
            out = max(out, get_dist(going_to.first, going_to.second));
        }
        going_to.first -= positions[i].first;
        going_to.second -= positions[i].second;
    }

    cout<<out<<"\n";

    return 0;
}