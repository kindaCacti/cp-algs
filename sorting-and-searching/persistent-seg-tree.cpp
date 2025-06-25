#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
struct PersistentSegTree{
    struct Node{
        Node* left = nullptr, *right = nullptr;
        pii range;
        long long value;
    };
    vector<Node*> roots;
    void propagate(Node* cn, pii range, vector<int>& values){
        cn->range = {range.first, range.second};
        if(range.first == range.second){
            if(range.first > values.size()) cn->value = 0;
            else cn->value = values[range.first - 1];
            return;
        }
        cn->left = new Node;
        propagate(cn->left, {range.first, (range.second + range.first) / 2}, values);
        cn->right = new Node;
        propagate(cn->right, {(range.second + range.first) / 2 + 1, range.second}, values);
        cn->value = cn->left->value + cn->right->value;
    }
    void setup(int size, vector<int>& values){
        int a = 1;
        while((a<<=1) < size);
        roots.clear();
        roots.push_back(new Node);
        propagate(roots[0], {1, a}, values);
    }
    long long getVal(int from, int to, Node* cn){
        if(cn->range.first >= from and cn->range.second <= to) return cn->value;
        if(cn->range.first > to or cn->range.second < from) return 0;
        long long out = getVal(from, to, cn->left);
        out += getVal(from, to, cn->right);
        return out;
    }
    long long getBetween(int from, int to, int time){
        return getVal(from, to, roots[time]);
    }
    void chVal(int val, int pos, Node* cn, Node* parent, bool wentLeft){
        if(pos < cn->range.first or pos > cn->range.second) return;
        Node* tmp = new Node{cn->left, cn->right, cn->range, 0};
        if(wentLeft) parent->left = tmp;
        else parent->right = tmp;
        if(tmp->left == nullptr){
            tmp->value = val;
            return;
        }else{
            chVal(val, pos, tmp->left, tmp, 1);
            chVal(val, pos, tmp->right, tmp, 0);
        }
        tmp->value = tmp->left->value + tmp->right->value;
    }
    void chVal(int val, int pos, int time){
        roots[time] = new Node{roots[time]->left, roots[time]->right, roots[time]->range, 0};
        chVal(val, pos, roots[time]->left, roots[time], 1);
        chVal(val, pos, roots[time]->right, roots[time], 0);
        roots[time]->value = roots[time]->left->value + roots[time]->right->value;
    }
    void copy(int time){
        roots.push_back(new Node{roots[time]->left, roots[time]->right, roots[time]->range, 0});
    }
};