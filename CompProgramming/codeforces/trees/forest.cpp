#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Generic 2D Segment Tree with a customizable merge operation.
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
            build_x(vx*2, lx, mx, a); //we build a range for the first dimension first, then the second
            build_x(vx*2+1, mx+1, rx, a);
        }
        build_y(vx, lx, rx, 1, 0, m-1, a); 
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    
    // Read the grid. We'll use 1 for tree and 0 for empty.
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++)
            grid[i][j] = (s[j] == '*' ? 1 : 0);
    }
    
    // Define the merge operation: here we use addition.
    auto add = [](int a, int b) { return a + b; };
    
    // Build a 2D segment tree using the generic merge operation.
    seg2<int, decltype(add)> seg(n, n, add, 0); 
    seg.build_x(1, 0, n-1, grid); 
    
    while(q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int y, x;
            cin >> y >> x;
            y--; x--;  // Convert to 0-indexed.
            int new_val = (grid[y][x] == 1 ? 0 : 1);
            grid[y][x] = new_val;
            seg.update_x(1, 0, n-1, y, x, new_val); //the whole range
        } else if (type == 2) {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            y1--; x1--; y2--; x2--;  // Convert to 0-indexed.
            cout << seg.query_x(1, 0, n-1, y1, y2, x1, x2) << "\n"; 
        }
    }
    
    return 0;
}
