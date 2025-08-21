#include <bits/stdc++.h>
//#include "debug.h"
using namespace std;
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

vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);
Mint C(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  while ((int) fact.size() < n + 1) {
    fact.push_back(fact.back() * (int) fact.size());
    inv_fact.push_back(1 / fact.back());
  }
  return fact[n] * inv_fact[k] * inv_fact[n - k];
}

void solve(int n, int c, int m){
    vector<int> sch(m + 1, 0);
    vector<int> cnt(101, 0);
    vector<int> pcnt(101, 0);
    vector<int> lst(101, 0);
    vector<int> emps(m + 1, 0);
    for (int i = 0; i < m; i++){
        int x;
        cin >> x;
        sch[i] = x - 1;
        if (sch[i] == -1) continue;
        cnt[sch[i]]++;
        lst[sch[i]] = i; 
    }

    // pcnt[1] = cnt[1];
    // for (int i = 2; i <= n; i++){
    //     pcnt[i] = cnt[i] + pcnt[i - 1];
    // }  

    for (int i = 0; i < m; i++){
        emps[i + 1] = emps[i] + (sch[i] == -1);
    } //1 based indexing

    //if you only need the previous layer, you can save some space 
    vector<Mint> dp(m + 1, 0);
    dp[0] = 1;
    int sum = 0;
    for (int f = 0; f < n; f++){//start at this floor
        // if (lst[f] > c + pcnt[f] || lst[f] < pcnt[f] || lst[f] > c * f) {
        //     cout << 0;
        //     return;
        // }
        vector<Mint> dpp(m + 1, 0);
        
        //how many you can actually add 
            //if (aadd < 0) continue;
        for (int bef = 0; bef <= m; bef++){ //before 
            if (dp[bef] == 0) continue;
            int lpos = bef + c; 
            if (lst[f] >= lpos) continue;
            for (int add = cnt[f]; add <= c && add + bef <= m; add++){
                int aadd = add - cnt[f];
                if (f == n - 1 && add != c) continue;
                if (bef + add > m) continue;
                //how many openings are there
                int canp = emps[min(m, bef + c)] - (bef - sum); // I need to track the empty spots...we can't use those empty spots, and the 
                dpp[bef + add] += dp[bef] * C(canp, aadd); //there's this many positions to add to 
            }
        } 
        swap(dp, dpp);  
        sum += cnt[f];
    }
    //not on n, but which one you're on
    cout << dp[m] << endl;
}

int main(){
    int t; 
    cin >> t;
    while (t--){
        int n, c, m;
        cin >> n >> c >> m;
        solve(n, c, m);
    }
}


