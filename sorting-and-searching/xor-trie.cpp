#include <bits/stdc++.h>

using namespace std;

struct Node{
    Node* left;
    Node* right;
    long long power;
};

struct XorTrie{
    const int depth = 60;
    vector<long long> nums;
    long long mxXor = 0;
    Node* root;

    void init(){
        root = new Node();
    }

    void getBits(long long num, vector<int>& out){
        long long pot = 1;
        for(int i = 1; i<depth; i++) pot *= 2;

        while(pot){
            if(num&pot){
                out.push_back(1);
                num -= pot;
            }else
                out.push_back(0);
            
            pot /= 2;
        }
    }

    long long getMaxXor(long long num){
        if(root->left == nullptr and root->right == nullptr) return 0;

        vector<int> bits;
        getBits(num, bits);

        Node* cn = root;
        long long out = 0;
        for(int bit : bits){
            if(bit == 1 and cn->left != nullptr){
                cn = cn->left;
                out += cn->power;
            }else if(bit==1){
                cn = cn->right;
            }else if(cn->right != nullptr){
                cn = cn->right;
                out += cn->power;
            }else{
                cn = cn->left;
            }
        }

        return out;
    }

    void insertNumber(long long num){
        nums.push_back(num);
        mxXor = max((long long)getMaxXor(num), mxXor);

        long long pot = 1;
        for(int i = 1; i<depth; i++) pot *= 2;

        vector<int> bits;
        getBits(num, bits);
        Node* cn = root;
        for(int bit : bits){
            if(bit == 0 and cn->left == nullptr){
                cn->left = new Node();
                cn->left->power = pot;
            }else if(bit == 1 and cn->right == nullptr){
                cn->right = new Node();
                cn->right->power = pot;
            }

            if(bit==0) cn = cn->left;
            else cn = cn->right;

            pot /= 2;
        }
    }

    long long maxXor(){
        return mxXor;
    }
};

int main(){
    XorTrie xtrie;
    xtrie.init();
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};

    for(int num : nums){
        xtrie.insertNumber(num);
    }

    cout<<xtrie.maxXor()<<" : max xor of given numbers\n";
    return 0;
}