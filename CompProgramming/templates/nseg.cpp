template<typename T, typename Merge>
struct seg2 {
    int n, m; // grid dimensions
    vector<vector<T>> t; // 2D segment tree storage
    Merge merge;        // merge operation (e.g. addition)
    T identity;         // identity element for the merge operation

    // Constructor: initialize tree dimensions and allocate memory.
    seg2(int n, int m, Merge merge, T identity)
        : n(n), m(m), merge(merge), identity(identity) {
        t.assign(4 * n, vector<T>(4 * m, identity));
    }

    // Build the inner segment tree (over columns) for a given outer node.
    void build_y(int vx, int lx, int rx, int vy, int ly, int ry, const vector<vector<T>>& a) {
        if (ly == ry) {
            if (lx == rx)
                t[vx][vy] = a[lx][ly];
            else
                t[vx][vy] = merge(t[vx*2][vy], t[vx*2+1][vy]);
        } else {
            int my = (ly + ry) / 2;
            build_y(vx, lx, rx, vy*2, ly, my, a);
            build_y(vx, lx, rx, vy*2+1, my+1, ry, a);
            t[vx][vy] = merge(t[vx][vy*2], t[vx][vy*2+1]);
        }
    }

    // Build the outer segment tree (over rows), then build the corresponding inner trees.
    void build_x(int vx, int lx, int rx, const vector<vector<T>>& a) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            build_x(vx*2, lx, mx, a);
            build_x(vx*2+1, mx+1, rx, a);
        }
        build_y(vx, lx, rx, 1, 0, m-1, a); //at the vx index, which range of rows do you have 
    }

    // Query the inner segment tree (over columns) for the interval [ly, ry] in the node vx.
    T query_y(int vx, int vy, int tly, int try_, int ly, int ry) {
        if (ly > ry)
            return identity;
        if (ly == tly && try_ == ry)
            return t[vx][vy];
        int tmy = (tly + try_) / 2;
        return merge(query_y(vx, vy*2, tly, tmy, ly, min(ry, tmy)),
                     query_y(vx, vy*2+1, tmy+1, try_, max(ly, tmy+1), ry));
    }

    // Query the outer segment tree (over rows) for rows [lx, rx] and columns [ly, ry].
    T query_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
        if (lx > rx)
            return identity;
        if (lx == tlx && trx == rx)
            return query_y(vx, 1, 0, m-1, ly, ry);
        int tmx = (tlx + trx) / 2;
        return merge(query_x(vx*2, tlx, tmx, lx, min(rx, tmx), ly, ry),
                     query_x(vx*2+1, tmx+1, trx, max(lx, tmx+1), rx, ly, ry));
    }

    // Update the inner segment tree (over columns) at a fixed row range (represented by vx).
    void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, T new_val) {
        if (ly == ry) {
            if (lx == rx)
                t[vx][vy] = new_val;
            else
                t[vx][vy] = merge(t[vx*2][vy], t[vx*2+1][vy]);
        } else {
            int my = (ly + ry) / 2;
            if (y <= my)
                update_y(vx, lx, rx, vy*2, ly, my, x, y, new_val);
            else
                update_y(vx, lx, rx, vy*2+1, my+1, ry, x, y, new_val);
            t[vx][vy] = merge(t[vx][vy*2], t[vx][vy*2+1]);
        }
    }

    // Update the outer segment tree (over rows) for a single cell change at (x, y).
    void update_x(int vx, int lx, int rx, int x, int y, T new_val) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            if (x <= mx)
                update_x(vx*2, lx, mx, x, y, new_val);
            else
                update_x(vx*2+1, mx+1, rx, x, y, new_val);
        }
        update_y(vx, lx, rx, 1, 0, m-1, x, y, new_val);
    }
};