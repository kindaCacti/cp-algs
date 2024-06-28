#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pii pair<int,int>

bool isLeft(pii p1, pii p2, pii p3){
    pii v1, v2;
    v1 = {p1.first-p2.first, p1.second-p2.second};
    v2 = {p1.first-p3.first, p1.second-p3.second};
 
    return (v1.first*v2.second - v1.second*v2.first) >= 0; // replace >= with = to get the minimal number of points on the convex hull
}

int32_t main(){
    int n;
    cin>>n;

    vector<pii> points;
    pii minPoint;
    int x, y;
    for(int i = 0; i<n; i++){
        cin>>x>>y;
        points.push_back({x, y});
        if(i == 0) minPoint = {x, y};
        if(y < minPoint.second or (y==minPoint.second and x > minPoint.first)) minPoint = {x, y};
    }

    map<double, priority_queue<pii, vector<pii>, greater<pii>>> sortedPoints;
    vector<pii> onLine;
    for(int i = 0; i<n; i++){
        if(points[i].first == minPoint.first and points[i].second == minPoint.second) continue;
        if(points[i].second == minPoint.second){
            onLine.push_back(points[i]);
            continue;
        }

        pii vec = {points[i].first - minPoint.first, points[i].second - minPoint.second};

        double tan = (double)vec.first / (double)vec.second; // :c
        sortedPoints[tan].push(points[i]);
    }

    sort(onLine.begin(), onLine.end());

    vector<pii> hull;
    hull.push_back(minPoint);

    while(sortedPoints.size()){
        pii cp = sortedPoints.rbegin()->second.top();
        sortedPoints.rbegin()->second.pop();
        if(sortedPoints.rbegin()->second.size() == 0) sortedPoints.erase(sortedPoints.rbegin()->first);

        while(hull.size() >= 2){
            int it = hull.size() - 1;
            if(isLeft(hull[it-1], hull[it], cp)){
                hull.push_back(cp);
                break;
            }
            hull.pop_back();
        }
        if(hull.size() < 2) hull.push_back(cp);

        if(sortedPoints.size() == 0 and onLine.size() != 0){
            for(pii linePoint : onLine){
                sortedPoints[0].push(linePoint);
            }
            onLine.clear();
        }
    }

    cout<<hull.size()<<"\n";
    for(int i = 0; i<hull.size(); i++){
        cout<<hull[i].first<<" "<<hull[i].second<<"\n";
    }

    return 0;
}