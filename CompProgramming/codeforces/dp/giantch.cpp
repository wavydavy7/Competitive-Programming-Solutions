#include <bits/stdc++.h>
// #include "debug.h"
using namespace std;
#define pb push_back
typedef long long ll;
const int MOD = 1e9 + 7;
const int MX = 300000;
int N, D;

template<class T> T invGeneral(T a, T b) {
    a %= b; if (a == 0) return b == 1 ? 0 : -1;
    T x = invGeneral(b,a); 
    return x == -1 ? -1 : ((1-(ll)b*x)/a+b)%b;
}

template<class A, class B> A operator+=(A& l, const B& r) { return l = l+r; }
template<class A, class B> A operator-=(A& l, const B& r) { return l = l-r; }
template<class A, class B> A operator*=(A& l, const B& r) { return l = l*r; }
template<class A, class B> A operator/=(A& l, const B& r) { return l = l/r; }

template<class T> struct modInt {
    T val;
    T mod = 0;
    // static const T mod = MOD;
 
    void normalize() {
        if (mod == 0) return;
        val %= mod; if (val < 0) val += mod;
    }
    modInt(T v = 0, T m = 0) : val(v), mod(m) { normalize(); }
    // modInt(T v = 0, T m = 0) : val(v) { normalize(); }
 
    explicit operator T() const { return val; }
    friend ostream& operator<<(ostream& os, const modInt& a) { return os << a.val; }
    friend bool operator==(const modInt& a, const modInt& b) { return a.val == b.val; }
    friend bool operator!=(const modInt& a, const modInt& b) { return !(a == b); }
 
    friend void check(modInt& a, modInt& b) { // make sure all operations are valid
        // comment out if mod is static const
        if (a.mod > 0 && b.mod > 0) { assert(a.mod == b.mod); return; }
        T mod = max(a.mod,b.mod); if (mod == 0) mod = MOD;
        if (a.mod != mod) { a.mod = mod; a.normalize(); }
        if (b.mod != mod) { b.mod = mod; b.normalize(); }
    }
    friend modInt operator+(modInt a, modInt b) {
        check(a,b); a.val += (T)b;
        if (a.val >= a.mod) a.val -= a.mod;
        return a;
    }
    friend modInt operator-(modInt a, modInt b) {
        check(a,b); a.val -= (T)b; 
        if (a.val < 0) a.val += a.mod; 
        return a;
    }
    friend modInt operator-(const modInt& a) { return modInt(0)-a; }
 
    friend modInt operator*(modInt a, modInt b) {
        check(a,b); a.val = (ll)a.val*(T)b%a.mod; return a;
    }
    friend modInt exp(modInt a, ll p) {
        modInt ans(1,a.mod);
        for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans;
    }
    friend modInt inv(const modInt& a) {
        //return {invGeneral(a.val,a.mod),a.mod};
        return exp(a,a.mod-2);
    }
    friend modInt operator/(modInt a, modInt b) { 
        check(a,b); return a*inv(b); 
    }
};


typedef modInt<ll> mi;
vector<mi> fact(MX + 1, 1);
vector<pair<int, int>> bls; 
map<int, mi> mp;  


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    int h, w, n;
    cin >> h >> w >> n;
    fact[0] = 1;
    for (int i = 1; i <= MX; i++){
        fact[i] = (i) * fact[i - 1];
    }
    for (int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        bls.emplace_back(a, b);
    }
    bls.emplace_back(h, w);
    sort(bls.begin(), bls.end(), [&](pair<int, int> y, pair<int, int> z){
        return (y.first == z.first) ? y.second < z.second : y.first < z.first;
    });

    // debug(bls);

    for (int i = 0; i <= n; i++){
        mp[i] = fact[bls[i].first + bls[i].second - 2] / (fact[bls[i].first - 1] * fact[bls[i].second - 1]);
        for (int j = 0; j < i; j++){
            pair<int, int> f = bls[i];
            pair<int, int> s = bls[j]; //the one above 
            if (s.first <= f.first && s.second <= f.second){
                mp[i] -= mp[j] * fact[bls[i].first + bls[i].second - bls[j].first - bls[j].second] / (fact[bls[i].first - bls[j].first] * fact[bls[i].second- bls[j].second]);
            }
        }
    }
    // debug((int) mp[0]);
    // debug((int) mp[1]);

    cout << mp[n];
}