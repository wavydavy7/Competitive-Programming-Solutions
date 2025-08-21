#include <bits/stdc++.h>
// #include "debug.h"
#define ll long long
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

int main(){
    int t;
    cin >> t;
    while (t--){
        int n, k;
        cin >> k >> n;
        vector<Mint> ch(18, 1);
        ch[1] = n + 1;
        for (int i = 2; i <= 17; i++){
            ch[i] = ch[i - 1] * (n - i + 1 + 1) / i;
        }
        vector<vector<int>> div(k + 1);
        //from 1 to k
        for (int i = 2; i <= k; i++){
            for (int j = i; j <= k; j += i){
                div[j].push_back(i);
            }
        }

        vector<vector<Mint>> dp(k + 1, vector<Mint>(17, 0));
        dp[1][0] = 1; 
        for (int num = 2; num <= k; num++){
            for (int l = 1; l <= 16; l++){
                for (int d : div[num]){
                    dp[num][l] += dp[num / d][l - 1];
                }
            }
        }
        cout << n % MD << " ";
        for (int x = 2; x <= k; x++){
            Mint ans = 0;
            for (int l = 1; l <= 16; l++){
                ans += dp[x][l] * ch[l + 1];
            }
            cout << ans << " ";
        }
        cout << endl;
    }
}