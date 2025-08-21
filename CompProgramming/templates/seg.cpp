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