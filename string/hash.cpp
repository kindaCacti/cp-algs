#include <bits/stdc++.h>

using namespace std;

#define int long long
const int mod = 1000000007; //1000000009 998244353

int fastPow(int a, int b, int md){
    if(b==0) return 1;
    if(b==1) return a;
    int out = fastPow(a, b/2, md);
    out *= out;
    out %= md;
    if(b%2) out *= a;
    out %= md;
    return out;
}

struct HASH{
    int mul = 1000;
    vector<int> primes = {1000000007};
    vector<vector<int>> hashes;

    void add(char ch){
        if(hashes.size() == 0){
            hashes.push_back({});
            for(int i = 0; i<primes.size(); i++){
                hashes[0].push_back(0);
            }
        }
        hashes.push_back({});
        for(int i = 0; i<primes.size(); i++){
            int prime = primes[i];
            int tmp = fastPow(mul, hashes.size(), prime);
            tmp *= (long long)ch;
            tmp %= prime;
            hashes.back().push_back(hashes[hashes.size()-2][i] + tmp);
            hashes.back()[i] %= mod;
        }
    }

    bool compareBetween(int s1, int f1, int s2, int f2){
        if(s1 != s2) return false;
        
        f1++; f2++;
        vector<int> sub1 = vector<int>(hashes[f1]);
        for(int i = 0; i<primes.size(); i++){
            sub1[i] -= hashes[s1][i];
            sub1[i] %= primes[i];
            sub1[i] += primes[i];
            sub1[i] %= primes[i];
        }

        vector<int> sub2 = vector<int>(hashes[f2]);
        for(int i = 0; i<primes.size(); i++){
            sub2[i] -= hashes[s2][i];
            sub2[i] %= primes[i];
            sub2[i] += primes[i];
            sub2[i] %= primes[i];
        }

        for(int i = 0; i<primes.size(); i++){
            int prime = primes[i];
            int tmp = fastPow(fastPow(mul, s1+1, prime), prime-2, prime);
            int tmp2 = fastPow(fastPow(mul, s2+1, prime), prime-2, prime);

            sub1[i] *= tmp;
            sub1[i] %= prime;

            sub2[i] *= tmp2;
            sub2[i] %= prime;
        }

        for(int i = 0; i<primes.size(); i++){
            if(sub1[i] != sub2[i]) return false;
        }

        return true;
    }
};