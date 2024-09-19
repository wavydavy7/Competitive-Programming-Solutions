
#include "bits/stdc++.h"
#define ll long long 
using namespace std;
int N, Q;
struct BIT{
    vector<ll> bit;
    int sz;
    BIT(int n){
        this->sz = n;
        bit.resize(n + 1, 0); //now with size n
    }

    BIT(vector<ll> &a){
        this->sz = a.size();
        bit.resize(sz + 1, 0);
        for (size_t i = 0; i < a.size(); i++){
            update(i, a[i]);
        }
    }

    ll sum(int i){
        ll res = 0;
        for (++i; i > 0; i -= i & -i){
            res += bit[i];
        }
        return res;
    }
    ll sum(int l, int r){
        return sum(r) - sum(l - 1); //index 0 is a dummy, 0 based indexing 
    }

    void update(int i, ll val){ //should be at index i
        for (++i; i <= sz; i += i & -i){ 
            bit[i] += val;
        }
    }


};

int main(){
    cin >> N >> Q;
    vector<ll> p(N, 0);
    for (int i = 0; i < N; i++){
        cin >> p[i];
    }
    BIT tree(p);
    for (int i = 0; i < Q; i++){
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 1){
            int to_add = b - p[a - 1];
            tree.update(a - 1, to_add);
            p[a - 1] = b;
        }
        else{
            cout << tree.sum(a - 1, b - 1) << endl;
        }
    }
}

//elevator algo: while in a given direction, go up till the end
//take a snap shop of those floors in that direction, remove 
//if there are n free elevators, all going in the up direction, label them l1 < l2 < l3 < ...
//have the first free elevator handle the highest amt / n, so on and so forth
//for a given floor, we need to know which ones above are going in the same direction
//we can store 2 seg trees, a down tree and an up tree
//for an up tree, if you go up from x, then all elements above it will revert to 0(range update) with lazy propagation
//for a down tree, if you go down from x, then all elements below it will revert to 0
//we need to store the leftmost and rightmost at any given time(just keep 2 pointers x2 total for each direction), when we run, clear it 