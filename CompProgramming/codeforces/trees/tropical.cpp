#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif
// -------------------- Generic Lazy Segment Tree (inclusive [l..r]) --------------------
template <typename T>
class LazySegTree {
public:
    using CombineFn = function<T(const T&, const T&)>;

    int n;
    vector<T> tree, lazy;
    CombineFn combine;
    T identity;    // used when a query range is completely outside

    // Constructor:
    //   _n          = number of leaves
    //   init_val    = initial value for every leaf (here: 0)
    //   ident       = identity element for combine (e.g. LLONG_MIN/2 for max)
    //   _combine    = how to merge two children (e.g. max)
    LazySegTree(int _n, T init_val, T ident, CombineFn _combine)
      : n(_n),
        tree(4*_n, init_val),
        lazy(4*_n, T()),
        combine(_combine),
        identity(ident)
    {}

    // apply an additive tag to node v
    void apply(int v, T val) {
        tree[v] += val;
        lazy[v] += val;
    }

    // push tag at v down to its children
    void push(int v) {
        if (lazy[v] != T()) {
            apply(v*2+1, lazy[v]);
            apply(v*2+2, lazy[v]);
            lazy[v] = T();
        }
    }

    // internal update on [ql..qr] (inclusive)
    void update(int v, int l, int r, int ql, int qr, T val) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(v, val);
            return;
        }
        push(v);
        int m = (l+r)>>1;
        update(v*2+1, l,   m, ql, qr, val);
        update(v*2+2, m+1, r,   ql, qr, val);
        tree[v] = combine(tree[v*2+1], tree[v*2+2]);
    }

    // internal query on [ql..qr] (inclusive)
    T query(int v, int l, int r, int ql, int qr) const {
        if (qr < l || r < ql) return identity;
        if (ql <= l && r <= qr) return tree[v];
        const_cast<LazySegTree*>(this)->push(v);
        int m = (l+r)>>1;
        T left  = query(v*2+1, l,   m, ql, qr);
        T right = query(v*2+2, m+1, r,   ql, qr);
        return combine(left, right);
    }

    // public: add `val` to every position in [l..r]
    void range_add(int l, int r, T val) {
        update(0, 0, n-1, l, r, val);
    }

    // public: query merge (e.g. max) over [l..r]
    T range_query(int l, int r) const {
        return query(0, 0, n-1, l, r);
    }
};


// -------------------- fenwick template -------------------- //
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

  void modify(int x, int y, T v){
    modify(x, v);
    modify(y + 1, -v);
  }
 
  T get(int x) {
    T v{};
    while (x >= 0) {
      v += fenw[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }

  T getr(int x, int y){
    return get(y) - get(x - 1);
  }
};


// Generic segtree template.
template <typename T>
class SegmentTree {
 public:
  int n;
  vector<T> tree;
  T identity;  // Identity element (here, infinity for min)
  function<T(const T&, const T&)> combine;
 
  SegmentTree(int _n, T _identity, function<T(const T&, const T&)> _combine)
      : n(_n), identity(_identity), combine(_combine) {
    tree.resize(4 * n, identity);
  }
 
  void build(const vector<T>& arr, int idx, int l, int r) {
    if (l == r) {
      tree[idx] = arr[l];
      return;
    }
    int mid = (l + r) / 2;
    build(arr, 2 * idx + 1, l, mid);
    build(arr, 2 * idx + 2, mid + 1, r);
    tree[idx] = combine(tree[2 * idx + 1], tree[2 * idx + 2]);
  }
 
  void build(const vector<T>& arr) {
    build(arr, 0, 0, n - 1);
  }
 
  // Standard point update: sets the value at pos to 'value'.
  void update(int pos, T value, int idx, int l, int r) {
    if (l == r) {
      tree[idx] = value;
      return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
      update(pos, value, 2 * idx + 1, l, mid);
    else
      update(pos, value, 2 * idx + 2, mid + 1, r);
    tree[idx] = combine(tree[2 * idx + 1], tree[2 * idx + 2]);
  }
 
  void update(int pos, T value) {
    update(pos, value, 0, 0, n - 1);
  }
 
  // Range query: returns the combined value in the interval [ql, qr]
  T query(int ql, int qr, int idx, int l, int r) {
    if (qr < l || ql > r)
      return identity;
    if (ql <= l && r <= qr)
      return tree[idx];
    int mid = (l + r) / 2;
    T left = query(ql, qr, 2 * idx + 1, l, mid);
    T right = query(ql, qr, 2 * idx + 2, mid + 1, r);
    return combine(left, right);
  }
 
  T query(int ql, int qr) {
    return query(ql, qr, 0, 0, n - 1);
  }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> as(n);
    for (int i = 0; i < n; i++){
        cin >> as[i];
    }
    vector<int> types(q);
    vector<int> amts(q);
    for (int i = 0; i < q; i++){
        string sign;
        cin >> sign >> amts[i];
        types[i] = (sign == "+") ? 1 : -1;
    }
    auto a = as;
    a.insert(a.end(), amts.begin(), amts.end());//we store everything in the seg tree
    sort(a.begin(), a.end()); //how to find if there's more than 1 of something... if we have something already, we increase the count
    int sz = int(a.size());
    int M = a.back() + 5;
    vector<int> first(M, -1);
    for (int i = 0; i < sz; i++){
        if (first[a[i]] == -1){
            first[a[i]] = i;
        }
    }//we find the first occurrence 
    //we want to find the max amount of points in each location 
    vector<int> cnt(M);
    set<int> alive;
    vector<set<int>> by_diff(M);
    SegmentTree<int> whereat(M, -1, [](const int&a, const int& b){return max(a, b);});
    LazySegTree<int> st(sz, 0, -1, [](const int&a, const int& b){return max(a, b);});
    fenwick<int64_t> bit(sz + 1);
    auto AddDiff = [&](int gap, int on){ //the find should 
        int old_val = (by_diff[gap].empty() ? -1 : *prev(by_diff[gap].end()));
        by_diff[gap].insert(on);
        int new_val = (by_diff[gap].empty() ? -1 : *prev(by_diff[gap].end()));
        if (old_val != new_val) whereat.update(gap, new_val);
    };

    auto RemoveDiff = [&](int gap, int on){
        int old_val = (by_diff[gap].empty() ? -1 : *prev(by_diff[gap].end()));
        by_diff[gap].erase(on);
        int new_val = (by_diff[gap].empty() ? -1 : *prev(by_diff[gap].end()));
        if (old_val != new_val) whereat.update(gap, new_val);
    };
    auto add = [&](int x){
        int pos = first[x] + cnt[x];
        auto it = alive.insert(pos).first; //which position it's in 
        //because you insrted it, you need to break up the one before it
        int pr = (it == alive.begin() ? -1 : *prev(it));
        int nxt = (next(it) == alive.end() ? -1 : *next(it)); //you want to add something to the very end
        if (pr != -1 && nxt != -1){
            RemoveDiff(a[nxt] - a[pr], pr);
        }
        if (pr != -1){
            AddDiff(a[pos] - a[pr], pr);
        }
        if (nxt != -1){
            AddDiff(a[nxt] - a[pos], pos);
        }
        cnt[x] += 1;
        bit.modify(pos, x);
        st.range_add(pos, pos + 1, x); //it requires x for this...when you're before, there's po
        st.range_add(pos + 1, sz, -x);
    };
    auto remove = [&](int x){
      cnt[x] -= 1;
      int pos = first[x] + cnt[x];
      auto it = alive.find(pos);
      int pr = (it == alive.begin() ? -1 : *prev(it));
      int nxt = (next(it) == alive.end() ? -1 : *next(it));
      if (pr != -1){
        RemoveDiff(a[pos] - a[pr], pr); //good order for book keeping
      }
      if (nxt != -1){
        RemoveDiff(a[nxt] - a[pos], pos); //this is gone 
      }
      if (pr != -1 && nxt != -1){
        //we need to do some removing 
        AddDiff(a[nxt] - a[pr], pr);
      }
      alive.erase(it);
      bit.modify(pos, -x);
      st.range_add(pos, pos + 1, -x);
      st.range_add(pos + 1, sz, x);
    };
    auto print = [&]{
      assert(!alive.empty());
      //starting at the highest dupe 
      int water = 0;
      while (true){
        //I need to find the largest idx with a diff greater than st
        int i = int(upper_bound(a.begin(), a.end(), water) - a.begin()); //we want to find the last one to insert, the one after a valid one
        int64_t sum = (i == 0 ? 0 : bit.get(i - 1));
        if (sum >= M - 1){
          water = M;
          break;
        }
        //If not, we must continue
        if (sum != water){
          water = int(sum);
          continue;
        }
        //we must find a place where the numbers that sum up to that place doubles 
        //up until when the gap is too large, in which case we would double the next turn
        auto jmp = whereat.query(0, int(sum)); //this is the last index with such a gap
        if (jmp == -1 || a[jmp] <= water){ //a[jmp] must be greater than water, since the next greatest one is < water
          break;
        }
        water = a[jmp]; //let's just go ahead and double it
      }
      int i = int(upper_bound(a.begin(), a.end(), water) - a.begin()); //we can either get to the second to last one
      //imagine that you have water + 1 as the last, you cannot end at water
      int atleast = *prev(alive.end()); //you just need to get to the last one && st.range_query(i, atleast - 1) > 0
      cout << ((i < atleast && st.range_query(i, atleast - 1) > 0) ? "No" : "Yes") << endl;

    };
    for (int i = 0; i < n; i++){
        add(as[i]);
    }
    print();
    for (int i = 0; i < q; i++){
      if (types[i] == 1) {
        add(amts[i]);
      } 
      else{
        remove(amts[i]);
      }
      // debug(bit.fenw);
      // debug(whereat.tree);
      print();
    }

}