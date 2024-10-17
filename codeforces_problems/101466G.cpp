#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000007;
int sieve[maxn];
const int mod = 1000000007;

void set_sieve(){
    for(int i = 2; i*i<=maxn; i++){
        if(sieve[i]) continue;
        for(int j = i*i; j<=maxn; j+=i){
            sieve[j] = i;
        }
    }
}

int possibilities(vector<int>& digits){
    vector<int> dp(digits.size()+1, 0);
    dp[0] = 1;
    for(int i = 0; i<digits.size(); i++){
        if(digits[i] != 0) dp[i+1] += dp[i];
        if(i > 0){
            int tmp = digits[i-1] * 10 + digits[i];
            if(tmp >= 10 and tmp <= 26) dp[i+1] += dp[i-1]; 
        }
        dp[i+1] %= mod;
    }

    return dp[digits.size()];
}

void solve(int num){
    vector<int> prime_divisors;
    while(num > 1){
        if(sieve[num] == 0) sieve[num] = num;
        prime_divisors.push_back(sieve[num]);
        num /= sieve[num];
    }

    sort(prime_divisors.begin(), prime_divisors.end());

    vector<int> digits;
    for(int number : prime_divisors){
        while(number){
            digits.push_back(number%10);
            number /= 10;
        }
    }

    sort(digits.begin(), digits.end());

    int out = 0;
    do{
        out += possibilities(digits);
        out %= mod;
    }while(next_permutation(digits.begin(), digits.end()));

    cout<<out<<endl;
}

int main(){
    set_sieve();
    int num;
    while(cin>>num) solve(num);
    return 0;
}