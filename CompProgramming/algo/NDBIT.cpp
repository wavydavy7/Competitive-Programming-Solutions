#include <bits/stdc++.h>
using namespace std; 

#define int long long
#define ld long double
#define ar array
 
const int INF = 1e17;
const int MOD = 998244353;

template<class T, int... Ns> struct BIT {
    T val = 0;
    void upd(T v) { val += v; }
    T query() { return val; }  
};
template<class T, int N, int... Ns> struct BIT<T, N, Ns...> {
    BIT<T, Ns...> bit[N+1];
    template<typename... Args> void upd(int pos, Args... args) {
        for (; pos <= N; pos += pos&-pos) bit[pos].upd(args...);
    }
    template<typename... Args> T sum(int pos, Args... args) {
        T res = 0; for (; pos > 0; pos -= pos&-pos) res += bit[pos].query(args...);
        return res;
    }
    template<typename... Args> T query(int l, int r, Args... args) {
        return sum(r, args...) - sum(l-1, args...);
    }
};

BIT<int, 301, 301, 301> bit2;
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int b, n, d, m; cin>>b>>n>>d>>m;
    int ans = 0;
    if (b == 1) {
        vector<int> a(n); for (int &i : a) cin>>i;
        sort(a.begin(), a.end());
        int lo = 0, hi = 0;
        for (int i = 0; i < n; i++) {
            while (hi + 1 < n && a[hi+1] - a[i] <= d) hi++;
            while (lo < n && a[i] - a[lo] > d) lo++;
            ans += hi - lo;
        }
    } else if (b == 2) {
        vector<ar<int,2>> a(n);
        for (int i = 0; i < n; i++) {
            int x, y; cin>>x>>y;
            a[i] = {x+y, x-y};
        }
        BIT<int, 150001> bit;
        sort(a.begin(), a.end());
        int lo = 0, hi = -1; 
        for (int i = 0; i < n; i++) {
            while (hi + 1 < n && a[hi+1][0] - a[i][0] <= d) bit.upd(a[++hi][1] + m+1, 1);
            while (lo < n && a[i][0] - a[lo][0] > d) bit.upd(a[lo++][1] + m+1, -1);
            ans +=  bit.query(max(1LL, a[i][1] + m+1 - d), min(a[i][1] + m+1 + d, 2*m+1)) - 1;
        }
    } else {
        vector<ar<int,4>> a(n);
        for (int i = 0; i < n; i++) {
            int x, y, z; cin>>x>>y>>z;
            a[i] = {x+y+z, x+y-z, x-y+z, x-y-z}; 
        }
        // [-2*m, 2*m] 1 -> -2*m,  4*m+1 -> 2*m
        sort(a.begin(), a.end());
        int lo = 0, hi = -1;
        for (int i = 0; i < n; i++) {
            while (hi + 1 < n && a[hi+1][0] - a[i][0] <= d) {
                ++hi;
                bit2.upd(a[hi][1] + 2*m+1, a[hi][2] + 2*m+1, a[hi][3] + 2*m+1, 1);
            }
            while (lo < n && a[i][0] - a[lo][0] > d) {
                bit2.upd(a[lo][1] + 2*m+1, a[lo][2] + 2*m+1, a[lo][3] + 2*m+1, -1);
                lo++;
            }
            ans +=  bit2.query(max(1LL, a[i][1] + 2*m+1 - d), min(a[i][1] + 2*m+1 + d, 4*m+1),
                max(1LL, a[i][2] + 2*m+1 - d), min(a[i][2] + 2*m+1 + d, 4*m+1),
                max(1LL, a[i][3] + 2*m+1 - d), min(a[i][3] + 2*m+1 + d, 4*m+1)) - 1;
        }
    }
    cout<<ans/2<<"\n";
} 