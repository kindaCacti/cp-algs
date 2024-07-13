#include <bits/stdc++.h>

using namespace std;

const int maxn = 1024;

struct Tree{
    int tree[maxn*2]{0};

    void chVal(int pos, int nval){
        pos += maxn;
        tree[pos] = nval;
        pos /= 2;
        while(pos){
            tree[pos] = tree[pos*2] + tree[pos*2+1];
            pos/=2;
        }
    }

    int getSum(int from, int to){
        int pot = 1;
        int out = 0;
        while(from<=to){
            int tmp = from + maxn;
            pot = 1;
            while(from + pot*2 <= to){
                if(tmp%2) break;
                tmp /= 2;
                pot *= 2;
            }
            out += tree[tmp];
            from += pot;
        }

        return out;
    }
}tree;

int main(){
    return 0;
}