#include "bits/stdc++.h"
using namespace std;

struct node {
    int pri, sz;
    char val;
    node *l, *r, *p;
    node(char c) {
        val = c;
        sz = 1;
        pri = rand();
        l = r = p = NULL;
    }
};

node* rt = NULL; // declare the root

int getSize(node* n) {
    return n ? n->sz : 0;
}

void updateSize(node* n) {
    if (n) n->sz = 1 + getSize(n->l) + getSize(n->r);
}

pair<node*, node*> split(node* root, int size) {
    if (!root) return {NULL, NULL};
    if (size <= getSize(root->l)) {
        auto p = split(root->l, size);
        root->l = p.second;
        updateSize(root);
        return {p.first, root};
    } else {
        auto p = split(root->r, size - getSize(root->l) - 1);
        root->r = p.first;
        updateSize(root);
        return {root, p.second};
    }
}

node* merge(node* left, node* right) {
    if (!left) return right;
    if (!right) return left;
    if (left->pri > right->pri) {
        left->r = merge(left->r, right);
        updateSize(left);
        return left;
    } else {
        right->l = merge(left, right->l);
        updateSize(right);
        return right;
    }
}

ostream &operator<<(ostream &os, node *n) { //pretty much an overloaded print method 
    if (!n) return os;
    os << n->l; //I will do it in dfs order 
    os << n->val;
    os << n->r;
    return os;
}

int main() {
    int N, O;
    string S;
    cin >> N >> O >> S;
    for (char c : S) {
        rt = merge(rt, new node(c)); // update root during merge
    }
    while (O--) {
        int l, r;
        cin >> l >> r;
        auto break1 = split(rt, l - 1);
        auto break2 = split(break1.second, r - l + 1);
        rt = merge(break1.first, break2.second); // update root during merge
        rt = merge(rt, break2.first); // update root during merge
    }
    cout << rt;
}
