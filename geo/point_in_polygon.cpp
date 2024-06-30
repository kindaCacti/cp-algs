#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pii pair<int,int>

vector<pii> points;
int n, m;

void normalizeVec(pii& vec){
    int tmp = abs(__gcd(vec.first, vec.second));
    vec.first /= tmp;
    vec.second /= tmp;
}

bool isLeft(pii p1, pii p2, pii p3){
    pii v1 = {p3.first - p1.first, p3.second - p1.second};
    pii v2 = {p2.first - p1.first, p2.second - p1.second};

    int tmp = (v2.first * v1.second - v2.second * v1.first);

    return tmp>0;
}

bool isOnTheSameLine(pii p1, pii p2, pii p3){
    if(p1.first == p3.first and p1.second == p3.second) return true;
    if(p2.first == p3.first and p2.second == p3.second) return true;

    pii v1 = {p1.first - p3.first, p1.second - p3.second};
    pii v2 = {p1.first - p2.first, p1.second - p2.second};

    normalizeVec(v1);
    normalizeVec(v2);

    return ((v1.first == v2.first) and (v1.second == v2.second));
}

bool isBetween(int p1, int p2, int p3){
    if(p1 > p3 and p2 <= p3) return true;
    if(p1 <= p3 and p2 > p3) return true;
    return false;
}

int checkPoint(pii point){
    int out = 0;
    for(int i = 0; i<n; i++){
        int np = (i+1) % n;
        if(isOnTheSameLine(points[i], points[np], point) and isOnTheSameLine(points[np], points[i], point)) return 0;

        if(!isBetween(points[i].second, points[np].second, point.second)) continue;
        if(points[i].first < point.first and points[np].first < point.first) continue;

        if(points[i].second == points[np].second){
            int lp = (i+(n-1))%n;
            int nnp = (np+1)%n;
            if(!isBetween(points[lp].second, points[nnp].second, point.second)) continue;
            out++;
            continue;
        }

        if(points[i].second < points[np].second and !isLeft(points[i], points[np], point)) continue;
        if(points[i].second >= points[np].second and !isLeft(points[np], points[i], point)) continue;
        out++;
    }
    return ((out%2)?1:-1);
}

int32_t main(){
    cin>>n>>m;

    int x, y;
    for(int i = 0; i<n; i++){
        cin>>x>>y;
        points.push_back({x, y});
    }

    for(int i = 0; i<m; i++){
        cin>>x>>y;
        int tmp = checkPoint({x, y});
        if(tmp == -1) cout<<"OUTSIDE\n";
        else if(tmp==0) cout<<"BOUNDARY\n";
        else cout<<"INSIDE\n";
    }

    return 0;
}