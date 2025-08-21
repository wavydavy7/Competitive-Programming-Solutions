#include <bits/stdc++.h>
// #include "debug.h"
using namespace std;
#define pb push_back
typedef long long ll;
const int MOD = 1e9 + 7;
const int MX = 5001;
const ll INF = 1e15; 
int n, b;
vector<ll> t(MX, 0);
vector<ll> x(MX, 0);
vector<ll> mn(MX, INF);

vector<vector<int>> dp(MX, vector<int>(MX, 0));
int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        int tp, xp;
        cin >> tp >> xp;
        t[i] = tp;
        x[i] = xp;
    }

    
    mn[0] = 0; //out of bounds is common error
    for (int i = 0; i < n; i++){
        if (mn[i] <= t[i]){
            mn[i + 1] = min(mn[i + 1], max(mn[i] + abs(x[i + 1] - x[i]), t[i])); //drop a clone on i 
            for (int j = i + 2; j <= n; j++){
                //we do the mins 
                if (t[i + 1] >= max(t[i], mn[i] + abs(x[i] - x[j])) + abs(x[j] - x[i + 1])) dp[i + 1][j] = 1; //here you use mn[0], which should be 0
                if (dp[i][j] && (abs(x[i + 1] - x[i]) <= abs(t[i + 1] - t[i]))) dp[i + 1][j] = 1;
            }
        }
        
        if (i + 1 < n && dp[i][i+1]){ //if we can even reach dp[i][j]
            int jp = i + 1; //we have bot on jp, we're on i
            mn[jp + 1] = min(mn[jp + 1], max(t[jp], t[jp - 1] + abs(x[jp + 1] - x[jp - 1])));
            for (int k = jp + 2; k <= n; k++){
                if (max(t[i] + abs(x[i] - x[k]), t[jp]) + abs(x[k] - x[jp + 1]) <= t[jp + 1]) dp[jp + 1][k] = 1;
            }
        }
    }

    if (dp[n-1][n] || mn[n] <= t[n]) cout << "YES";
    else cout << "NO";

    return 0;
}