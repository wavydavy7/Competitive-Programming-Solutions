#include <bits/stdc++.h>
// #include "debug.h"
using namespace std;
#define pb push_back
typedef long long ll;
const int MX = 2001;
const ll INF = 1e15; 
const int MAXK = 100000;
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

 




    
    // debug(comb);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    vector<vector<Mint>> f(2, vector<Mint>(100000 + 1, 0));
    vector<Mint> sm(100000 + 1);
    sm[0] = 1;
    // f[0][1] = 1; //f[1][1] = 1;
    //f[0][0] = 1;
    f[0][0] = 1;
    for (int i = 1; i <= 400; i++){ //using
        fill(f[i % 2].begin(), f[i % 2].end(), 0);
        for (int j = i; j <= 100000; j++){ //total
            f[i % 2][j] = f[i % 2][j - i] + f[(i + 1) % 2][j - i];
            if (i % 2) sm[j] -= f[i % 2][j];
            else sm[j] += f[i % 2][j];
        }
    }
    while(T--){
        int n, k;
        cin >> n >> k;
        Mint ans = 0;
        vector<Mint> comb(k + 1);
        comb[0] = 1;
        for (int i = 1; i <= k; i++){
            comb[i] = comb[i - 1] / i * (n - 1 + i);
            //cout << comb[i] << "\n";
        }
        for (int i = 0; i <= k; i++){
            ans += sm[i] * comb[k - i];
        }
        cout << ans << "\n";
    }
}