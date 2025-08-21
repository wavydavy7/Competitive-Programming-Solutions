#include <bits/stdc++.h>
using namespace std;

// Generic segtree template.
template <typename T>
class segtree {
 public:
  int n;
  vector<T> tree;
  T identity;  // Identity element (here, infinity for min)
  function<T(const T&, const T&)> combine;
 
  segtree(int _n, T _identity, function<T(const T&, const T&)> _combine)
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

struct Point {
  int x, y;
  int i;
  bool is_start;
  Point(int x, int y, int i, bool is_start) : x(x), y(y), i(i), is_start(is_start) {}
  bool operator<(const Point &p) const {
    if (x == p.x) return y < p.y;
    return x < p.x;
  }
};

vector<int> distinct_y;
int y_index(int y) {
  return lower_bound(distinct_y.begin(), distinct_y.end(), y) - distinct_y.begin();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n, p;
  cin >> n >> p;
  
  vector<Point> events;
  for (int i = 0; i < p; ++i) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    // Record start and end events.
    events.emplace_back(x1, y1, i, true);
    events.emplace_back(x2, y2, i, false);
    distinct_y.push_back(y1);
    distinct_y.push_back(y2);
  }
  
  sort(distinct_y.begin(), distinct_y.end());
  sort(events.begin(), events.end());
  
  vector<int> ans(p);
  int m = distinct_y.size();
  const int INF = 1e9;
  
  vector<int> init(m, INF);
  init[0] = 0;
  
  segtree<int> segt(m, INF, [](int a, int b) { return min(a, b); });
  segt.build(init);
  
  for (const Point &pt : events) {
    int yind = y_index(pt.y);
    if (pt.is_start) {
      // For a start point, answer is current x+y plus the minimum value for all indices up to yind.
      int best = segt.query(0, yind);
      ans[pt.i] = pt.x + pt.y + best; //you hafta do this since you don't know that all starting things end before you start new one
    } else {
      // For an end point, update the segtree at yind.
      int new_val = ans[pt.i] - pt.x - pt.y;
      // Only update if the new value is lower than what is already stored.
      int cur = segt.query(yind, yind);
      if (new_val < cur) {
        segt.update(yind, new_val);
      }
    }
  }
  
  // The answer is the minimum value over the entire range plus 2*n.
  int final_min = segt.query(0, m - 1);
  cout << final_min + 2 * n;
  
  return 0;
}
