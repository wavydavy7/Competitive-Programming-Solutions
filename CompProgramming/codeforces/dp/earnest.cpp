#include <bits/stdc++.h>
//#include "debug.h"
#define ll long long
#define pb push_back
using namespace std;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--){
        int n, m, k;
        cin >> n >> m >> k;
        vector<vector<int>> a(n, vector<int>(m, 0));        
        vector<int> cnt(k + 1, 0);

        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cin >> a[i][j];
            }
            
        }

        vector<ll> dp(k + 1, 0);
        vector<int> ee(n, 0);
        for (int i = 0; i < n; i++){
            ee[i] = count(a[i].begin(), a[i].end(), -1);
        }
        ll ans = 0;
        for (int i = 1; i < n; i++){

            for (int j = 0; j < m; j++){
                if (a[i - 1][j] != -1) cnt[a[i - 1][j]]++;
            }

            for (int j = 0; j < m; j++){
                if (a[i][j] != -1) ans += cnt[a[i][j]];
            }

            for (int j = 0; j < m; j++){
                if (a[i - 1][j] != -1) cnt[a[i - 1][j]]--;
            }

        } //initially

        // for (int i = 0; i < m: i++){
        //     if (a[n - 1][i] != -1) cnt[a[n - 1][i]] = 0;
        // }
        fill(cnt.begin(), cnt.end(), 0);
    
        // pair<int, int> mx = {0, 0};
        ll mx = 0;
        ll cmx = 0;
        for (int i = 1; i < n; i++){
            //this is hard because you need to keep a running max...cmx keeps track of some part of the dp recurrence
            for (auto x : a[i]){
                if (x >= 0) cnt[x]++;
            }
            for (auto x : a[i]){
                if (x >= 0){
                    dp[x] = max(dp[x], cmx) + 1ll*ee[i - 1]*cnt[x]; //cmx revisited if there is something in the previous row
                    mx = max(mx, dp[x]); 
                    cnt[x] = 0; //don't need to process again
                }
                
            }
            for (auto x : a[i - 1]){
                if (x >= 0) cnt[x]++;
            }
            ll e = 1ll*ee[i]*ee[i - 1];
            ll ch = max(mx, cmx) - e; //you change 
            ll omx = mx;
            for (auto x : a[i - 1]){
                if (x >= 0){
                    dp[x] = max({dp[x], cmx, omx - e}) + cnt[x]*ee[i];
                    mx = max(mx, dp[x]);
                    cnt[x] = 0;
                }
            }
            cmx = max(cmx, ch);
            ans += e;
        }
        cout << max(mx, cmx) + ans << endl;
    }
}
 