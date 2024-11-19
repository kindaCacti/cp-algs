#include <bits/stdc++.h>
using namespace std;

struct MinHull{
    struct Line{
        long long a, b;
        double sx;
    };

    vector<Line> lines;

    void insert(long long a, long long b){
        while(lines.size()){
            double cp = (lines.back().b - b)/(a - lines.back().a);

            if(lines.back().sx >= cp){
                lines.pop_back();
            }else{
                lines.push_back({a, b, cp});
                return;
            }
        }
        lines.push_back({a, b, LLONG_MIN});
    }

    long long query(long long pos){
        long long mn = 0, mx = lines.size()-1, mid;
        while(mn < mx){
            mid = (mn+mx)/2+1;
            if(lines[mid].sx <= pos) mn = mid;
            else mx = mid-1;
        }
        return lines[mx].a * pos + lines[mx].b;
    }
};