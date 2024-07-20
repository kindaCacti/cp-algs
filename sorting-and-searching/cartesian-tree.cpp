#include <bits/stdc++.h>

using namespace std;

struct Node{
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    int val;
    int id;
};

struct CartestianTree{
    int size = 0;
    Node* root;
    vector<Node*> nodes;
    void init(vector<int>& nums){
        size = nums.size();
        Node* ln = nullptr;
        vector<Node*> stack;

        for(int i = 0; i<size; i++){
            int num = nums[i];
            while(stack.size() and stack.back()->val > num){
                ln = stack.back();
                stack.pop_back();
            }

            Node* tmp = new Node();
            nodes.push_back(tmp);
            tmp->val = num;
            tmp->id = i;
            if(ln != nullptr){
                tmp->left = ln;
                ln->parent = tmp;
            }
            if(stack.size()){
                tmp->parent = stack.back();
                stack.back()->right = tmp;
            }
            stack.push_back(tmp);
            ln = nullptr;
        }

        while(stack.size() != 1) stack.pop_back();
        root = stack.back();
    }
};