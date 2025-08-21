#include <bits/stdc++.h>
using namespace std;

string nar = "narek";
int main(){
    int t;
    cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        vector<int> dp(5, int(-1e8)), dp2;
        vector<string> inp(n);
        for (int i = 0; i < n; i++){
            cin >> inp[i];
        }

        dp[0] = 0;
        for (int i = 0; i < n; i++){
            dp2 = dp;
            
            for (int let = 0; let < 5; let++){
                int cum = 0;
                int on = let;
                for (int pos = 0; pos < m; pos++){
                    if (nar.find(inp[i][pos]) == -1) continue;
                    if (on == nar.find(inp[i][pos])) {
                        cum++;
                        on = (on + 1) % 5;
                    }                    
                    else cum--;
                }
                dp2[on] = max(dp2[on], dp[let] + cum);
            }
            dp = dp2;
        }

        int ans = 0;
        for (int i = 0; i < 5; i++){
            ans = max(ans, dp[i] - 2*i);
        }
        cout << ans << endl;
    }
}