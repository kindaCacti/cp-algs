#include <bits/stdc++.h>
using namespace std;
#define int long long
struct CHT{
    struct Line{
        int a, b;
    };
    vector<Line> lines;
    deque<pair<double, int>> inter_points;
    double intersection_point(Line& a, Line& b){
        return (double)(b.b - a.b) / (double)(a.a - b.a);
    }
    void add_line(int a, int b){
        Line tmp{a, b};
        double inp = DBL_MIN;
        while(inter_points.size()){
            auto [pos, it] = inter_points.back();
            inp = intersection_point(tmp, lines[it]);
            if(pos < inp) break;
            inter_points.pop_back();
        }
        inter_points.push_back({inp, lines.size()});
        lines.push_back(tmp);
    }
    int getMinFor(int pos){
        if(lines.size() == 0) return 0;
        int mn = 0, mx = inter_points.size() - 1, mid;
        while(mn < mx){
            mid = (mn + mx) / 2 + 1;
            if(inter_points[mid].first <= pos) mn = mid;
            else mx = mid - 1;
        }
        int it = inter_points[mn].second;
        return lines[it].a * pos + lines[it].b;
    }
};