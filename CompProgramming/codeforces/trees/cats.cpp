#include <bits/stdc++.h>
#define pb push_back
using namespace std;

#ifdef LOCAL
#include "../../algo/debug.h"
#else
#define debug(...) 42
#endif


template <typename T>
class fenwick {
 public:
  vector<T> fenw;
  int n;
 
  fenwick(int _n) : n(_n) {
    fenw.resize(n);
  }
 
  void modify(int x, T v) {
    while (x < n) {
      fenw[x] += v;
      x |= (x + 1);
    }
  }
 
  T get(int x) {
    T v{};
    while (x >= 0) {
      v += fenw[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
};
//fenwick<long long> fenw(n);

int main(){
    std::ios::sync_with_stdio(false);  // Disable C++ I/O synchronization
    std::cin.tie(nullptr); 
    int n, q;
    cin >> n >> q;
    vector<int> s;
    for (int i = 0; i < n; i++){
        char c;
        cin >> c;
        s.push_back(c);
    }
    //let's preprocess 
    vector<int> st;
    vector<int> p(n, -1);
    for (int i = 0; i < n; i++){
        if (s[i] == '(') st.push_back(i);
        else if (!st.empty()) {
            int match = st.back();
            st.pop_back();
            p[i] = match;
            p[match] = i;
        }
    }
    //debug(st);
    int beg = 0;
    //we need to construct the tree
    
    vector<vector<int>> chs(n); //let's have these be the nodes
    vector<int> idx(n, -1);
    vector<int> prior(n, -1);
    while (beg < n){
        if (p[beg] == -1){
            beg++;
            continue;
        }
        //from beg to end 
        int end = beg;
        while (end + 1 < n && p[end + 1] != -1){
            end++;
        }
        //now we have a range from beginning to end 
        st.assign(1, (int) chs.size()); //let's create a new tree 
        chs.emplace_back();
        for (int i = beg; i <= end; i++){
            if (s[i] == '('){
                int b = st.back();
                idx[i] = chs[b].size();
                chs[b].push_back(i);
                prior[i] = b;
                st.push_back(i);
            }
            if (s[i] == ')'){
                idx[i] = idx[st.back()];
                st.pop_back();
            }
        }
        beg = end + 1;
    }
    vector<fenwick<int>> ts(chs.size(), fenwick<int>(0));
    //I want to have a fenwick for each node in the tree
    for (int i = 0; i < chs.size(); i++){
        if (chs[i].empty()) continue;
        ts[i].n = chs[i].size();
        ts[i].fenw.resize(ts[i].n);
        for (int j = 0; j < ts[i].n; j++){
            ts[i].modify(j, 1);
        }
        //we add one
    }
    

    //now, we have a collection of tree nodes
    vector<int> deg(n);
    fenwick<long long> bit(n);
    vector<long long> vals(n);
    for (int i = 0; i < n; i++){
        deg[i] = chs[i].size();
        long long add = (long long) deg[i] * (deg[i] + 1) / 2;
        vals[i] = add;
        bit.modify(i, add);
    }

    while (q--){
        int t, l, r;
        cin >> t >> l >> r;
        l--;
        r--;
        if (t == 2){
            int x = prior[l];
            long long res = bit.get(r) - bit.get(l - 1); //inclusive 
            //for this, I could have a couple idx here
            long long chain = ts[x].get(idx[r]) - ts[x].get(idx[l] - 1);
            res += chain * (chain + 1) / 2;
            cout << res << endl;
        }
        else{
            //I need to remove the things in the middle  
            int x = prior[l];
            if (x < n){
                deg[x]--;
                long long nd = (long long) deg[x] * (deg[x] + 1) / 2;
                bit.modify(x, nd - vals[x]);
                vals[x] = nd;
            }
            ts[x].modify(idx[l], -1);
        }
    }
    return 0;

}
