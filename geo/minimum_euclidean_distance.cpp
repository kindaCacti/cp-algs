#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pii pair<int, int>

vector<pii> points;

int distBetween(pii p1, pii p2){
    pii vec = {p1.first - p2.first, p1.second - p2.second};
    return vec.first * vec.first + vec.second * vec.second;
}

int checkAcross(int from, int to, int delta){
    int out = LLONG_MAX;
    vector<pii> sortedByY;
    int tmp = (to+from)/2;
    for(int i = from; i <= to; i++){
        int xdist = points[i].first - points[tmp].first;
        if(xdist * xdist > delta) continue;
        sortedByY.push_back({points[i].second, points[i].first});
    }

    sort(sortedByY.rbegin(), sortedByY.rend());

    for(int i = 0; i<sortedByY.size(); i++){
        for(int j = 1; j<=7; j++){
            if(i+j >= sortedByY.size()) break;
            out = min(out, distBetween(sortedByY[i], sortedByY[i+j]));
        }
    }

    return out;
}

int minDistance(int from, int to){
    int tmp = to - from + 1;
    int out = LLONG_MAX;
    if(tmp > 3){
        out = min(out, minDistance(from, from + tmp/2 - 1));
        out = min(out, minDistance(from + tmp/2, to));
        out = min(out, checkAcross(from, to, out));
    }else if(tmp == 3){
        out = min(out, distBetween(points[from], points[from+1]));
        out = min(out, distBetween(points[from], points[from+2]));
        out = min(out, distBetween(points[from+1], points[from+2]));
    }else{
        out = min(out, distBetween(points[from], points[to]));
    }
    return out;
}

int32_t main(){
    int n;
    cin>>n;

    int x, y;
    for(int i = 0; i<n; i++){
        cin>>x>>y;
        points.push_back({x, y});
    }

    sort(points.begin(), points.end());

    cout<<minDistance(0, n-1); //returns the minimal distance squared
    return 0;
}
