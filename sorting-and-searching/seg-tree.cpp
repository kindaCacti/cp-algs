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

    int getAmmFrom(int from, int amm){
        int ogf = from;
        from += size;
        long long out = 0;
        while(out < amm){
            int add = 1;
            int tmp = from;
            while(tmp){
                if(tmp % 2) break;
                int tf = tmp / 2;
                if(out + tree[tf] >= amm) break;
                if(from + add*2 >= tree.size()) return maxn;
                tmp /= 2;
                add *= 2;
            }
            if(tmp == 0) return maxn;
            out += tree[tmp];
            from += add;
            ogf += add;
        }

        return ogf-1;
    }
}tree;

int main(){
    return 0;
}