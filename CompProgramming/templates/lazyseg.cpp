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

    void apply(int v, T val) {
        tree[v] += val;
        lazy[v] += val;
    }

    void push(int v) {
        if (lazy[v] != T()) {
            apply(v*2+1, lazy[v]);
            apply(v*2+2, lazy[v]);
            lazy[v] = T();
        }
    }

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

    T query(int v, int l, int r, int ql, int qr) const {
        if (qr < l || r < ql) return identity;
        if (ql <= l && r <= qr) return tree[v];
        const_cast<LazySegTree*>(this)->push(v);
        int m = (l+r)>>1;
        T left  = query(v*2+1, l,   m, ql, qr);
        T right = query(v*2+2, m+1, r,   ql, qr);
        return combine(left, right);
    }

    void range_add(int l, int r, T val) {
        update(0, 0, n-1, l, r, val);
    }

    T range_query(int l, int r) const {
        return query(0, 0, n-1, l, r);
    }
};