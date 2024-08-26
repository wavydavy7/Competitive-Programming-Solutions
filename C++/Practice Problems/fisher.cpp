#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF=1e16;
pair<int,int> memo[51][1005];
int toll[51][51];
int travelTime[51][51];
int n,t;
pair<int,int> dp(int cur, int t_left) {
    // returns a pair
    if (t_left < 0) return {INF, INF};
    if (cur == n-1) return {0, 0}; 
    // invalid state, prune
    // at market
    if (memo[cur][t_left] != pair<int,int>{-1,-1}) return memo[cur][t_left];
    pair<int,int> ans = {INF, INF};
    for (int X = 0; X < n; ++X) {
        if (cur != X) {
            // go to another city
            auto [tollpaid, timeneeded] = dp(X, t_left - travelTime[cur][X]);
            if (tollpaid + toll[cur][X] < ans.first) {
                // pick the min cost
                ans.first = tollpaid + toll[cur][X];
                ans.second = timeneeded + travelTime[cur][X];
            }
        }
    }
    return memo[cur][t_left] = ans;
}

void solve() {
    cin >> n >> t;
    if (n == 0 && t == 0) exit(0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= t; j++) memo[i][j] = {-1, -1};
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> travelTime[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> toll[i][j];
        }
    }
    auto res = dp(0, t);
    cout << res.first << " " << res.second << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(1){
        solve();
    }
    
    return 0;
}
