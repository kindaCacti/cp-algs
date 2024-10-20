#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, looking_for;
    cin>>n;

    vector<int> numbers(n);
    vector<pii> possible_first_half(1, {0, 0});
    vector<pii> possible_second_half(1, {0, 0});

    for(int i = 0; i<n; i++){
        cin>>numbers[i];
    }
    cin>>looking_for;

    int middle = min(20, n);
    int pot = 1;
    for(int i = 0; i<middle; i++){
        int size = possible_first_half.size();
        for(int j = 0; j<size; j++){
            pii tmp = possible_first_half[j];
            possible_first_half.push_back({tmp.first + numbers[i], tmp.second + pot});
        }
        pot *= 2;
    }

    pot = 1;
    unordered_set<int> poss_sums;
    poss_sums.insert(0);
    for(int i = middle; i<n; i++){
        int size = possible_second_half.size();
        for(int j = 0; j<size; j++){
            pii tmp = possible_second_half[j];
            possible_second_half.push_back({tmp.first + numbers[i], tmp.second + pot});
            poss_sums.insert(possible_second_half.back().first);
        }
        pot *= 2;
    }

    pii out = {0,0};
    for(pii first_half : possible_first_half){
        if(poss_sums.find(looking_for-first_half.first) != poss_sums.end()){
            out.first = first_half.second;
            for(int i = 0; i<possible_second_half.size(); i++){
                if(possible_second_half[i].first == looking_for-first_half.first) out.second = possible_first_half[i].second;
            }
            break;
        }
    }

    for(int i = 0; i<middle; i++){
        cout<<out.first%2;
        out.first/=2;
    }
    for(int i = middle; i<n; i++){
        cout<<out.second%2;
        out.second/=2;
    }
    return 0;
}