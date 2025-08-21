#include <bits/stdc++.h>
// #include "debug.h"
#define ll long long
using namespace std;

int main(){
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector<pair<int, int>> ps;
        for (int i = 0; i < n; i++){
            int x;
            cin >> x;
            ps.emplace_back(x, x);
        }
        for (int i = 0; i < n; i++){
            int x;
            cin >> x;
            ps[i].second = x;
        }
        sort(ps.begin(), ps.end(), [&](pair<int, int> a, pair<int, int> b){return min(a.first, a.second) < min(b.first, b.second);});
        vector<vector<int>> dp(4, vector<int>(n, 0));
        dp[0][0] = 1;
        dp[3][0] = 1;
        for (int i = 1; i < n; i++){
            
            if (ps[i].first > ps[i - 1].first && ps[i].second > ps[i - 1].second){
                //we don't need to flip
                // dp[1][i] = dp[2][i - 1];
                // dp[3][i] = dp[0][i - 1];
                dp[0][i] |= dp[0][i - 1]; //we continue
                dp[2][i] |= dp[2][i - 1];
                dp[1][i] |= dp[3][i - 1];
                dp[3][i] |= dp[1][i - 1];
            }

            //there's also the case where we could flip
            if (ps[i].second > ps[i - 1].first && ps[i].first > ps[i - 1].second){
                dp[1][i] |= dp[2][i - 1]; 
                dp[3][i] |= dp[0][i - 1];
                dp[0][i] |= dp[1][i - 1];
                dp[2][i] |= dp[3][i - 1];
            }

        }
        if (dp[0][n - 1] || dp[1][n - 1]) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}