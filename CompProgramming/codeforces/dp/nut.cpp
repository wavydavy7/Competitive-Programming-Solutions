#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<array<ll,3>> pts(n+1);
    pts[0] = {0,0,0};
    for(int i = 1; i <= n; i++)
        cin >> pts[i][0] >> pts[i][1] >> pts[i][2];
    sort(pts.begin()+1, pts.end(), [](auto &A, auto &B){
        if (A[0] != B[0]) return A[0] < B[0];
        return A[1] > B[1];
    });
    vector<ll> dp(n+1);
    deque<int> d;
    d.push_back(0);
    ll ans = 0;
    auto bad = [&](int i, int j, int k){
        long double lhs = (long double)(dp[k] - dp[j]) * (pts[j][0] - pts[i][0]);
        long double rhs = (long double)(dp[j] - dp[i]) * (pts[k][0] - pts[j][0]);
        return lhs >= rhs;
    };
    for(int i = 1; i <= n; i++) {
        while(d.size() > 1) {
            int j0 = d[0], j1 = d[1];
            ll v0 = -pts[j0][0] * pts[i][1] + dp[j0];
            ll v1 = -pts[j1][0] * pts[i][1] + dp[j1];
            if (v0 <= v1) d.pop_front();
            else break;
        }
        int j = d.front();
        dp[i] = dp[j] - pts[j][0] * pts[i][1] + pts[i][0] * pts[i][1] - pts[i][2];
        ans = max(ans, dp[i]);
        while(d.size() > 1 && bad(d[d.size() - 2], d.back(), i))
            d.pop_back();
        d.push_back(i);
    }
    cout << ans;
    return 0;
}
