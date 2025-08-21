#include <bits/stdc++.h>
#define pb push_back
using namespace std;

#ifdef LOCAL
#include "../../algo/debug.h"
#else
#define debug(...) 42
#endif

template <typename T>
class segtree {
 public:
  int n;
  vector<T> tree;
  T identity;  // Identity element for the combine function (e.g., 0 for sum)
  // A combine function, e.g., for range sum it can be: [](T a, T b) { return a + b; }
  function<T(const T&, const T&)> combine;
 
  // Constructor: pass array size, identity element, and combine function.
  segtree(int _n, T _identity, function<T(const T&, const T&)> _combine)
      : n(_n), identity(_identity), combine(_combine) {
    tree.resize(4 * n, identity);
  }
 
  // Build the tree from an array.
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
 
  // Point update: set position pos to value.
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
 
  // Range query: returns the combined result for the interval [ql, qr].
  T query(int ql, int qr, int idx, int l, int r) {
    if (qr < l || ql > r)
      return identity;  // out of range, return identity element
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

  int find(int idx, int l, int r, T val){
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if(tree[2*idx + 1] >= val) return find(2*idx + 1, l, mid, val);
    return find(2*idx + 2, mid + 1, r, val);
  }

  int find(T val){
    if (tree[0] < val) return -1;
    return find(0, 0, n - 1, val);
  }
};
struct Frog{
    long long x;
    long long rch;
    int eaten;
    int idx;
};

struct Mosq{
    long long x;
    long long sz;
};

struct MosqCmp {
    bool operator()(const Mosq &a, const Mosq &b) const {
        return a.x < b.x || (a.x == b.x && a.sz < b.sz);
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    vector<Frog> ff;
    vector<Mosq> mm;

    for (int i = 0; i < n; i++){
        long long x, t;
        cin >> x >> t;
        ff.push_back({x, x + t, 0, i}); //this gets constructed
    }
    for (int i = 0; i < m; i++){
        long long p, b;
        cin >> p >> b;
        mm.push_back({p, b});
    }
    
    sort(ff.begin(), ff.end(), [&](Frog a, Frog b){return a.x < b.x;}); //you'll be querying for reach
    vector<long long> reach(n);
    for (int i = 0; i < n; i++){
        reach[i] = ff[i].rch;
    }
    segtree<long long> seg(n, -1, [&](long long a, long long b){return max(a, b);});
    seg.build(reach);
    multiset<Mosq, MosqCmp> ms; //priority queue doesn't work because you might insert a very small element and not be able to access the valid events after it

    for (int i = 0; i < m; i++){
        // Process a mosquito
        long long coor = mm[i].x;
        int which = seg.find(coor);
        // If no suitable frog is found (or the frog cannot catch the mosquito), add it to the multiset.
        if (which == -1 || ff[which].x > coor || ff[which].rch < coor) {
            ms.insert(mm[i]);
        }
        // If the frog can eat the mosquito
        else if (ff[which].x <= coor && ff[which].rch >= coor){
            ff[which].eaten++;
            ff[which].rch += mm[i].sz;
            // Process waiting mosquitoes that this frog can now catch.
            // We find the first waiting mosquito with coordinate >= frog's x.
            auto it = ms.lower_bound({ff[which].x, -1});
            while (!ms.empty() && it != ms.end() && it->x <= ff[which].rch) {
                ff[which].eaten++;
                ff[which].rch += it->sz;
                ms.erase(it);
                it = ms.lower_bound({ff[which].x, -1});
            }
            seg.update(which, ff[which].rch);
        }
    }


    vector<pair<int, long long>> res(n);
    for (int i = 0; i < n; i++){
        res[ff[i].idx] = {ff[i].eaten, ff[i].rch - ff[i].x};
    }
    for (auto f : res){
        cout << f.first << " " << f.second << endl;
    }
    return 0;
}