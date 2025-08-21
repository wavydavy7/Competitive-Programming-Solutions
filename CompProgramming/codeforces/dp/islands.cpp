#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_N = 10000;
constexpr int MD = 1000000007;

// -------------------- mint Class -------------------- //
template <int MOD, int RT> 
struct mint {
    static const int mod = MOD;
    static constexpr mint rt() { return RT; }  // primitive root for FFT
    int v;
    explicit operator int() const { return v; }  // explicit conversion to int
    mint() : v(0) {}
    mint(long long _v) {
        v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
        if(v < 0) v += MOD;
    }
    bool operator==(const mint &o) const { return v == o.v; }
    friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
    friend bool operator<(const mint &a, const mint &b) { return a.v < b.v; }
    friend istream &operator>>(istream &is, mint &a) {
        long long x; is >> x; a = mint(x); return is;
    }
    friend ostream &operator<<(ostream &os, mint a) {
        os << int(a);
        return os;
    }
    
    mint &operator+=(const mint &o) {
        if ((v += o.v) >= MOD) v -= MOD;
        return *this;
    }
    mint &operator-=(const mint &o) {
        if ((v -= o.v) < 0) v += MOD;
        return *this;
    }
    mint &operator*=(const mint &o) {
        v = int((long long)v * o.v % MOD);
        return *this;
    }
    mint &operator/=(const mint &o) { return *this *= inv(o); }
    friend mint pow(mint a, long long p) {
        mint ans = 1;
        assert(p >= 0);
        for(; p; p /= 2, a *= a)
            if (p & 1) ans *= a;
        return ans;
    }
    friend mint inv(const mint &a) {
        assert(a.v != 0);
        return pow(a, MOD - 2);
    }
    mint operator-() const { return mint(-v); }
    mint &operator++() { return *this += 1; }
    mint &operator--() { return *this -= 1; }
    friend mint operator+(mint a, const mint &b) { return a += b; }
    friend mint operator-(mint a, const mint &b) { return a -= b; }
    friend mint operator*(mint a, const mint &b) { return a *= b; }
    friend mint operator/(mint a, const mint &b) { return a /= b; }
};

using Mint = mint<MD, 5>;  // Use mod=1000000007, primitive root 5

// -------------------- Global Variables -------------------- //
// All quantities meant to be computed modulo MD will be of type Mint.
vector<Mint> vv(MAX_N + 1);  // Precomputed helper array

vector<Mint> xx(MAX_N), yy(MAX_N), zz(MAX_N), ans(MAX_N);
vector<Mint> jj(MAX_N), zz_(MAX_N), ww(MAX_N), dp(MAX_N);

vector<int> dd(MAX_N), pp(MAX_N), qq(MAX_N);
vector<int> marked(MAX_N, 0);

// The graph: neighbors remain ints.
vector<vector<int>> graph;

// -------------------- Graph Utilities -------------------- //
void append(int i, int j) {
    graph[i].push_back(j);
}
void detach(int i, int j) {
    auto &vec = graph[i];
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (*it == j) {
            vec.erase(it);
            return;
        }
    }
    assert(false);
}

// -------------------- DFS1 -------------------- //
// Build a DFS tree and process cycle (back) edges.
void dfs1(int p, int i, int d) {
    pp[i] = p;
    dd[i] = d;
    if (p != -1)
        detach(i, p);  // remove the (i,p) edge

    // Process neighbors in reverse order.
    for (int o = int(graph[i].size()) - 1; o >= 0; o--) {
        int j = graph[i][o];
        if (dd[j] == 0)
            dfs1(i, j, d + 1);
        else if (dd[j] > dd[i]) {
            detach(j, i);
            int k = j;
            while (pp[k] != i) {
                detach(pp[k], k);
                qq[pp[k]] = k;
                k = pp[k];
            }
            marked[k] = 1;
            qq[j] = k;
        }
    }
    // Filter neighbor list: remove marked ones.
    vector<int> newList;
    for (int j : graph[i]) {
        if (!marked[j])
            newList.push_back(j);
        else
            marked[j] = 0;
    }
    graph[i] = move(newList);
}

// -------------------- DFS2 -------------------- //
// Post-order DFS computing intermediate values yy and zz.
void dfs2(int i, int escape) {
    // Process children (neighbors) in reverse order.
    for (int o = int(graph[i].size()) - 1; o >= 0; o--) {
        int j = graph[i][o];
        if (pp[j] == i)
            dfs2(j, 0);
        else {
            for (int k = j; k != i; k = pp[k])
                dfs2(k, 1);
        }
    }
    
    int cntb = 0, cntc = 0;
    // Count tree edges and cycle edges.
    for (int o = int(graph[i].size()) - 1; o >= 0; o--) {
        int j = graph[i][o];
        if (pp[j] == i)
            cntb++;
        else {
            Mint z = 1;
            for (int k = j; k != i; k = pp[k])
                z *= zz[k];
            jj[cntc] = j;      // store node index as int
            zz_[cntc] = z;     // store computed value as Mint
            cntc++;
        }
    }
    
    int d = cntb + cntc * 2 + (escape ? 1 : 0);
    ww[0] = xx[i] * vv[d];
    for (int c = 1; c <= cntc; c++) {
        ww[c] = ww[c - 1] * Mint(2) * Mint(c) * xx[i] * vv[d - c * 2];
    }
    // Reset dp[0..cntc]
    for (int c = 0; c <= cntc; c++)
        dp[c] = 0;
    dp[0] = 1;
    for (int h = 0; h < cntc; h++) {
        Mint z = zz_[h];
        for (int c = cntc; c > 0; c--) {
            dp[c] += dp[c - 1] * z;
        }
    }
    Mint y = 0;
    for (int c = 0; c <= cntc; c++) {
        y += dp[c] * ww[c];
    }
    // For each tree edge, assign computed value y.
    for (int o = int(graph[i].size()) - 1; o >= 0; o--) {
        int j = graph[i][o];
        if (pp[j] == i)
            yy[j] = y;
    }
    if (escape)
        zz[i] = y;
    
    // Process cycle edges.
    for (int h = 0; h < cntc; h++) {
        Mint z = zz_[h];
        for (int c = 1; c <= cntc; c++)
            dp[c] -= dp[c - 1] * z;
        y = 0;
        for (int c = 0; c <= cntc; c++)
            y += dp[c] * ww[c];
        for (int c = cntc; c > 0; c--)
            dp[c] += dp[c - 1] * z;
        int j = (int) jj[h];
        Mint y_ = y;
        for (int k = j; k != i; k = pp[k]) {
            yy[k] = yy[k] + y_;
            y_ *= zz[k];
        }
        int k = j;
        y_ = y;
        do {
            k = qq[k];
            yy[k] = yy[k] + y_;
            y_ *= zz[k];
        } while (k != j);
    }
}

// -------------------- DFS3 -------------------- //
// Final DFS that computes the answer for each node.
void dfs3(int i, Mint acc) {
    Mint x = Mint(1) - zz[i];
    for (int o = int(graph[i].size()) - 1; o >= 0; o--) {
        int j = graph[i][o];
        if (pp[j] == i) {
            dfs3(j, acc * yy[j]);
            x -= yy[j];
        }
        else {
            for (int k = j; k != i; k = pp[k]) {
                dfs3(k, acc * yy[k]);
                x -= yy[k] * (Mint(1) - zz[k]);
            }
        }
    }
    ans[i] = acc * x;
}

// -------------------- init() -------------------- //
// Precompute the vv array using Mint arithmetic.
void init() {
    vv[1] = 1;
    for (int i = 2; i <= MAX_N; i++) {
        // Note: (MD % i) is computed first; then vv[...] is used.
        vv[i] = vv[i - (MD % i)] * Mint(MD / i + 1);
    }
}

// -------------------- main() -------------------- //
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        graph.clear();
        graph.resize(n);
        for (int i = 0; i < n; i++)
            graph[i].reserve(2);

        // Read and preprocess xx values.
        for (int i = 0; i < n; i++) {
            int tmp;
            cin >> tmp;
            // original: xx[i] = (1 - tmp + MD) % MD;
            xx[i] = Mint(1) - Mint(tmp);
        }
        // Read edges (convert to 0-indexing).
        for (int h = 0; h < m; h++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            append(u, v);
            append(v, u);
        }
        // Reset dd and marked arrays.
        for (int i = 0; i < n; i++) {
            dd[i] = 0;
            marked[i] = 0;
        }
        dfs1(-1, 0, 1);
        // Reset yy and zz arrays.
        for (int i = 0; i < n; i++) {
            yy[i] = 0;
            zz[i] = 0;
        }
        dfs2(0, 0);
        dfs3(0, Mint(1));
        for (int i = 0; i < n; i++)
            cout << ans[i] << (i + 1 < n ? " " : "\n");
    }
    return 0;
}
