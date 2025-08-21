#include <bits/stdc++.h>
//#include "debug.h"
using namespace std;
#define pb push_back
typedef long long ll;
const int MOD = 1e9 + 7;
const int MX = 300000;
int N, L;
vector<int> bs;

// template<class T> T invGeneral(T a, T b) {
//     a %= b; if (a == 0) return b == 1 ? 0 : -1;
//     T x = invGeneral(b,a); 
//     return x == -1 ? -1 : ((1-(ll)b*x)/a+b)%b;
// }


// template<class A, class B> 
// typename std::enable_if<!std::is_same<A, std::string>::value, A>::type 
// operator+=(A& l, const B& r) { return l = l+r; }

// template<class A, class B> 
// typename std::enable_if<!std::is_same<A, std::string>::value, A>::type 
// operator-=(A& l, const B& r) { return l = l-r; }

// template<class A, class B> 
// typename std::enable_if<!std::is_same<A, std::string>::value, A>::type 
// operator*=(A& l, const B& r) { return l = l*r; }

// template<class A, class B> 
// typename std::enable_if<!std::is_same<A, std::string>::value, A>::type 
// operator/=(A& l, const B& r) { return l = l/r; }

// template<class T> struct modInt {
//     T val;
//     T mod = 0;
//     // static const T mod = MOD;
 
//     void normalize() {
//         if (mod == 0) return;
//         val %= mod; if (val < 0) val += mod;
//     }
//     modInt(T v = 0, T m = 0) : val(v), mod(m) { normalize(); }
//     // modInt(T v = 0, T m = 0) : val(v) { normalize(); }
 
//     explicit operator T() const { return val; }
//     friend ostream& operator<<(ostream& os, const modInt& a) { return os << a.val; }
//     friend bool operator==(const modInt& a, const modInt& b) { return a.val == b.val; }
//     friend bool operator!=(const modInt& a, const modInt& b) { return !(a == b); }
 
//     friend void check(modInt& a, modInt& b) { // make sure all operations are valid
//         // comment out if mod is static const
//         if (a.mod > 0 && b.mod > 0) { assert(a.mod == b.mod); return; }
//         T mod = max(a.mod,b.mod); if (mod == 0) mod = MOD;
//         if (a.mod != mod) { a.mod = mod; a.normalize(); }
//         if (b.mod != mod) { b.mod = mod; b.normalize(); }
//     }
//     friend modInt operator+(modInt a, modInt b) {
//         check(a,b); a.val += (T)b;
//         if (a.val >= a.mod) a.val -= a.mod;
//         return a;
//     }
//     friend modInt operator-(modInt a, modInt b) {
//         check(a,b); a.val -= (T)b; 
//         if (a.val < 0) a.val += a.mod; 
//         return a;
//     }
//     friend modInt operator-(const modInt& a) { return modInt(0)-a; }
 
//     friend modInt operator*(modInt a, modInt b) {
//         check(a,b); a.val = (ll)a.val*(T)b%a.mod; return a;
//     }
//     friend modInt exp(modInt a, ll p) {
//         modInt ans(1,a.mod);
//         for (; p; p /= 2, a *= a) if (p&1) ans *= a;
//         return ans;
//     }
//     friend modInt inv(const modInt& a) {
//         //return {invGeneral(a.val,a.mod),a.mod};
//         return exp(a,a.mod-2);
//     }
//     friend modInt operator/(modInt a, modInt b) { 
//         check(a,b); return a*inv(b); 
//     }
// };


// typedef modInt<ll> mi;

ll dp[101][101][1001][2][2]; //what is the maximal cost 



ll dfs(int i, int comp, int cst, int lend, int rend){
    int cstp = cst + (bs[i] - bs[i - 1]) * (2*comp + lend + rend); 
    if (cstp > L) return 0;
    if (comp < 0) return 0;
    if (i == N){
        if (comp == 0) return 1;
        else return 0;
    } 
    

    if (dp[i][comp][cst][lend][rend] != -1) return dp[i][comp][cst][lend][rend];
    
    ll val = 0;
    //sps lend, rend aren't comp
    val += dfs(i + 1, comp, cstp, 1, rend) % MOD; //add to left end
    val += dfs(i + 1, comp - 1, cstp, 1, rend) * comp % MOD; //join middle to left 
    val += dfs(i + 1, comp, cstp, lend, 1) % MOD; //add to right 
    val += dfs(i + 1, comp - 1, cstp, lend, 1) * comp % MOD; //join middle to right 

    if (comp > 1) val += dfs(i + 1, comp - 1, cstp, lend, rend) * (comp) * (comp - 1) % MOD; //merge two comps in the middle
    val += dfs(i + 1, comp, cstp, lend, rend) * 2 *comp % MOD; //add to a component 
    val += dfs(i + 1, comp + 1, cstp, lend, rend) % MOD; //start new one 

    
    //tuple t = {i, comp, cst, lend, rend};
    // debug(t);
    // debug((ll) dp[i][comp][cst][lend][rend]);
    return dp[i][comp][cst][lend][rend] = val % MOD;;
}

int main(){
    cin >> N >> L;
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < N; i++){
        int x;
        cin >> x;
        bs.pb(x);
    }
    
    sort(bs.begin(), bs.end());
    bs.insert(bs.begin(), bs[0]);
    cout << dfs(1, 0, 0, 0, 0) << endl;
}   