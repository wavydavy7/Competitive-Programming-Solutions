#include <bits/stdc++.h>
#define pb push_back
using namespace std;

#ifdef LOCAL
#include "../../algo/debug.h"
#else
#define debug(...) 42
#endif

const long long MOD = 998244353;

int main(){
    int n; 
    cin >> n;
    //debug(1);   
    vector<int> a(n, -1);
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        a[i] = x;
    }
    //debug(a);
    int sq = (int) sqrt(n);
    //debug(sq);
    vector<int> dp(n, 1); //this is one because there is de facto one way to get to something
    vector<vector<int>> buck(sq + 1, vector<int>(sq + 1, 0));
    for (int i = n - 1; i >= 0; i--){
        if (a[i] >= sq){
            for (int st = i + a[i]; st < n; st += a[i]){
                dp[i] = (dp[i] + dp[st]) % MOD;
            }
        }
        else {
            dp[i] = (dp[i] + buck[a[i]][i % a[i]]) % MOD;
        }
        //debug(dp);
        for (int jmp = 1; jmp < sq; jmp++){
            buck[jmp][i % jmp] = (buck[jmp][i % jmp] + dp[i]) % MOD; //how many ways to get here 
        }
        //debug(buck);
    }
    cout << dp[0];
    return 0;
}