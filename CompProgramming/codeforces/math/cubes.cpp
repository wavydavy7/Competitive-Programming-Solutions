#include <bits/stdc++.h>
using namespace std;
constexpr int MOD = 998244353;
constexpr int MAXF = 3e6 + 10;

template<int MOD>
struct Mint {
    int v;
    Mint(): v(0) {}
    Mint(long long _v) {
        v = int(_v % MOD);
        if(v < 0) v += MOD;
    }
    explicit operator int() const { return v; }
    Mint& operator+=(const Mint &o) { v += o.v; if(v >= MOD)v -= MOD; return *this; }
    Mint& operator-=(const Mint &o) { v -= o.v; if(v < 0)v += MOD; return *this; }
    Mint& operator*=(const Mint &o) { v = int((long long)v * o.v % MOD); return *this; }
    friend Mint pow(Mint a, long long p) {
        Mint res = 1;
        while(p) {
            if(p & 1) res *= a;
            a *= a;
            p >>= 1;
        }
        return res;
    }
    friend Mint inv(const Mint &a) { return pow(a, MOD - 2); }
    Mint& operator/=(const Mint &o) { return *this *= inv(o); }
    friend Mint operator+(Mint a, const Mint &b) { return a += b; }
    friend Mint operator-(Mint a, const Mint &b) { return a -= b; }
    friend Mint operator*(Mint a, const Mint &b) { return a *= b; }
    friend Mint operator/(Mint a, const Mint &b) { return a /= b; }
};

using mint = Mint<MOD>;

vector<int> phi(MAXF);
vector<mint> fact(MAXF), ifact(MAXF);

void precompute() {
    // factorials
    fact[0] = 1;
    for (int i = 1; i < MAXF; ++i)
        fact[i] = fact[i - 1] * i;
    ifact[MAXF - 1] = inv(fact[MAXF - 1]);
    for (int i = MAXF - 2; i >= 0; --i)
        ifact[i] = ifact[i + 1] * (i + 1);

    // phi
    for (int i = 0; i < MAXF; i++) phi[i] = i;
    for (int i = 2; i < MAXF; i++) {
        if (phi[i] == i) {
            for (int j = i; j < MAXF; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

vector<int> getDivisors(int x) {
    vector<int> res;
    for (int i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            res.push_back(i);
            if (i * i != x)
                res.push_back(x / i);
        }
    }
    return res;
}

int lcm(int a, int b) {
    return a / __gcd(a, b) * b;
}

// cache for multinomial coefficients
unordered_map<string, mint> mc_cache;

mint multinomial(const vector<int> &a) {
    string key;
    int total = 0;
    for (int x : a) {
        total += x;
        key += to_string(x) + ",";
    }

    if (mc_cache.count(key)) return mc_cache[key];

    mint res = fact[total];
    for (int x : a)
        res /= fact[x];
    return mc_cache[key] = res;
}

void solve() {
    int a, b, c, k;
    cin >> a >> b >> c >> k;
    vector<int> ds(k);
    for (int &x : ds) cin >> x;

    int g = ds[0];
    for (int i = 1; i < k; ++i)
        g = __gcd(g, ds[i]);

    map<int, mint> contrib;
    auto da = getDivisors(a);
    auto db = getDivisors(b);
    auto dc = getDivisors(c);

    for (int x : da)
        for (int y : db)
            for (int z : dc) {
                int N = lcm(x, lcm(y, z));
                if (g % N == 0) {
                    mint weight = phi[x];
                    weight *= phi[y];
                    weight *= phi[z];
                    contrib[N] += weight;
                }
            }

    mint ans = 0;
    for (auto &[cycle, weight] : contrib) {
        vector<int> parts;
        for (int d : ds)
            parts.push_back(d / cycle);
        ans += multinomial(parts) * weight;
    }

    mint total = mint(a) * b * c;
    cout << (int)(ans / total) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    precompute();

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
