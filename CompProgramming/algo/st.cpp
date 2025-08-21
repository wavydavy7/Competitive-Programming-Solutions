#include "bits/stdc++.h"
using namespace std;

int N, Q;
struct ST{
    int sz;
    vector<int> tree;
    ST(vector<int> a){
        this->sz = a.size();
        tree.resize(4 * sz, 0);
        build(a, 1, 0, sz - 1); //inclusive
    }
    void build(vector<int> a, int node, int l, int r){
        if (l == r){
            tree[node] = a[l];
        }
        else{
            int m = (l + r) >> 1;
            build(a, 2 * node, l, m);
            build(a, 2 * node + 1, m + 1, r); //we do [l, m] //1 based indexing in seg tree, but everything else is in 0
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        } 
    }

    int sum(int node, int start, int end, int l, int r){
        //if l is after end, there are no overlaps 
        if (l > r) {
            return 0;
        }

        else if (l == start && end == r){ //so it's in between 
            return tree[node];
        }
        int m = (start + end) >> 1;
        return sum(2 * node, start, m, l, min(r, m)) + sum(2 * node + 1, m + 1, end, max(l, m + 1), r);

    }

    void update(int node, int start, int end, int idx, int val){
        if (start == end){
            tree[node] = val;
        }
        else{
            int m = (start + end) >> 1;
            if (idx <= m){
                update(2 * node, start, m, idx, val);
            }
            else {
                update(2 * node + 1, m + 1, end, idx, val);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

};

int main(){
    cin >> N >> Q;
    vector<int> p(N, 0);
    vector<int> print;
    for (int i = 0; i < N; i++){
        cin >> p[i];
    }
    ST tree(p);
    for (int i = 0; i < Q; i++){
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 1){
            tree.update(1, 0, N - 1, a - 1, b); //change @ a-1 to b 
        }
        else {
            int res = tree.sum(1, 0, N - 1, a - 1, b - 1);
            cout << res << endl;
        }
    }
}