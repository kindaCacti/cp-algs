#include <bits/stdc++.h>

using namespace std;

const int let = 26;
const int maxn = 1000007;

struct Node{
    int children[let];
};

struct Trie{
    Node nodes[maxn];
    int nnode = 1;

    void clear(){
        while(nnode > 0){
            nnode--;
            for(int j = 0; j<let; j++){
                nodes[nnode].children[j] = 0;
            }
        }
        nnode = 1;
    }

    void add_word(string word){
        int cn = 0;
        for(char ch : word){
            int clet = ch-'a';
            if(nodes[cn].children[clet] == 0){
                nodes[cn].children[clet] = nnode;
                nnode++;
            }
            cn = nodes[cn].children[clet];
        }
    }

    int get_min_distinct(string word){
        int cn = 0;
        int out = 1;
        while(out < word.size()){
            int clet = word[out-1]-'a';
            if(nodes[cn].children[clet] == 0) break;
            cn = nodes[cn].children[clet];
            out++;
        }
        return min(out, (int)word.size());
    }
} trie;

void solve(){
    trie.clear();
    int n;
    cin>>n;

    string word;
    int out = 0;
    for(int i = 0; i<n; i++){
        cin>>word;
        out += trie.get_min_distinct(word);
        trie.add_word(word);
    }

    cout<<out<<"\n";
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int t;
    cin>>t;

    for(int i = 1; i<=t; i++){
        cout<<"Case #"<<i<<": ";
        solve();
    }
}