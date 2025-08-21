#include <bits/stdc++.h>
using namespace std;
constexpr int MD = 998244353;
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
//fenwick<long long> fenw(n);
vector<int> parent, depth, heavy, head, pos, tin, tout, sub;
int cur_pos;
int cnt = 0;

int dfs(int v, vector<vector<int>> const& adj) {
    int size = 1;
    int max_c_size = 0;
    for (int c : adj[v]) {
        if (c != parent[v]) {
            parent[c] = v, depth[c] = depth[v] + 1;
            int c_size = dfs(c, adj);
            size += c_size;
            if (c_size > max_c_size) //we wanna find the max size of a subtree
                max_c_size = c_size, heavy[v] = c; 
        }
    }
    sub[v] = size;
    return size;
}

void decompose(int v, int h, vector<vector<int>> const& adj) {
    tin[v] = cnt++;
    head[v] = h, pos[v] = cur_pos++;
    if (heavy[v] != -1) //it does have a heavy child
        decompose(heavy[v], h, adj); //decompose the heavy child
    for (int c : adj[v]) { //if it only has light children
        if (c != parent[v] && c != heavy[v])
            decompose(c, c, adj); //for the light child, head of light is light
    }
    tout[v] = cnt;
}

void init(vector<vector<int>> const& adj) {
    int n = adj.size();
    parent = vector<int>(n);
    depth = vector<int>(n);
    heavy = vector<int>(n, -1);
    head = vector<int>(n);
    pos = vector<int>(n);
    tin = vector<int>(n);
    tout = vector<int>(n);
    sub = vector<int>(n);
    cur_pos = 0;
    dfs(0, adj);
    parent[0] = -1;
    decompose(0, 0, adj);
}

int main(){
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }

    init(adj); //how we wanna add something to the heavy chain 
    fenwick<Mint> bit(n + 1); //we know that the default is just 0
    fenwick<Mint> hv(n + 1);
    vector<Mint> hold(n, 0);
    Mint tot = 0;
    while (q--){
        int t, v, d;
        cin >> t >> v;
        v--;
        if (t == 1){
            cin >> d;
            tot += d; //tout[v] gives you tin[v] of the next one not visited 
            bit.modify(0, Mint(n - sub[v]) / n * d); //externally
            bit.modify(tin[v], -Mint(n - sub[v]) / n * d);
            bit.modify(tout[v], Mint(n - sub[v]) / n * d); //on the other subtree of the root
            bit.modify(n, Mint(n - sub[v]) / n * d);
            if (heavy[v] != -1){
                hold[v] += d;
                hv.modify(tin[v] + 1, Mint(sub[heavy[v]]) / n * d);
            }
        }
        else{
            //what we wanna do now is query up to the root 
            Mint res = tot;
            res -= bit.get(tin[v]); //we wanna subtract this 
            while (v != -1){
                int h = head[v];
                res -= hv.getr(tin[h], tin[v]);
                int p = parent[h];
                if (p != -1){
                    //there is the chance that we went on a light edge, and we still need to subtract this amount 
                    res -= hold[p] * Mint(sub[h])/n;
                }
                v = p;
            }
            cout << res << endl;
        }
    }




}