#include <bits/stdc++.h>

using namespace std;

struct CHT{
    struct Line{
        long long a, b;
        long long sx;
    };

    vector<Line> lines;

    void insert(long long a, long long b){
        while(lines.size()){
            long long ta = a - lines.back().a;
            long long tb = lines.back().b - b;
            long long cp = tb / ta;
            if(tb % ta) cp++;
            if(lines.back().sx < cp){
                lines.push_back({a, b, cp});
                return;
            }
            lines.pop_back();
        }
        lines.push_back({a, b, LLONG_MIN});
    }

    long long query(long long x){
        int mn = 0, mx = lines.size()-1, mid;
        while(mn < mx){
            mid = (mn+mx)/2 + 1;
            if(lines[mid].sx <= x) mn = mid;
            else mx = mid-1;
        }
        long long out = lines[mn].a * x + lines[mn].b;
        return out;
    }
};