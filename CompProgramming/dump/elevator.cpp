#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, k;
    cin >> n >> k;
    vector<ll> a(n); // Use vector for dynamic array
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<pair<ll, ll>> dp(1 << n); // Use vector for dynamic array
    dp[0] = make_pair(0, k + 1);
    for (int s = 1; s < (1 << n); s++) // for all bitmasks
    {
        dp[s] = make_pair(25, 0);
        for (int i = 0; i < n; i++) // for all peeps
        {
            if (s >> i & 1) // if you're looking at the config and peep's there
            {
                pair<ll, ll> prev = dp[s ^ (1 << i)]; // look at prev config without the peep
                ll c = prev.first;
                ll w = prev.second;
                if (w + a[i] > k) // if overweight, add new elevator
                {
                    c++;
                    w = min(a[i], w); // find minimum of peep's weight and current weight
                }
                else
                {
                    w += a[i]; // add the weight to elevator
                }
                dp[s] = min(dp[s], make_pair(c, w)); // you want min of current and new pair (# elevators, weight)
            }
        }
    }
    cout << dp[(1 << n) - 1].first << endl;
    return 0;
}