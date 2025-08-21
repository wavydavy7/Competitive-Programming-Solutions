#include <bits/stdc++.h>
//#include "debug.h"
using namespace std;
#define pb push_back
typedef long long ll;
const int MOD = 1e9 + 7;
const int MX = 300000;
int N, K;
ll dp[2][1001][201];

void add(ll &a, ll b) {
    a = (a + b) % MOD;
}

int main(){
    cin >> N >> K;
    vector<int> as(N, 0);
    for (int i = 0; i < N; i++){
        cin >> as[i];
    }
    //number of ways to form 
    sort(as.begin(), as.end()); //if you sort, make sure it's the exact size
    //dp[which][total diff][open groups] 
    dp[0][0][0] = 1;
    for (int i = 0; i < N; i++){
        memset(dp[(i + 1) % 2], 0, sizeof(dp[(i + 1) % 2])); //you need to reset
        for (int g = 0; g <= i; g++){
            for (int d = 0; d <= K; d++){
        
                // debug(t);
                // debug(dp[i][d][g]);
                //we add to new, open, group
                //total increase 
                ll inc = (i > 0) ? (as[i] - as[i - 1]) * g : 0;
                if (d + inc > K) continue;
                
                 //add to group 
                add(dp[(i + 1) % 2][d + inc][g + 1], dp[i % 2][d][g]); //make new group 
                add(dp[(i + 1) % 2][d + inc][g], dp[i % 2][d][g]); //make own and end
                if (g > 0) {
                    add(dp[(i + 1) % 2][d + inc][g], dp[i % 2][d][g] * g % MOD);
                    add(dp[(i + 1) % 2][d + inc][g - 1], dp[i % 2][d][g] * g % MOD);
                } //add to group and end 
                
            }
        }
    }

    ll res = 0;
    for (int d = 0; d <= K; d++){
        add(res, dp[N % 2][d][0]);
    }
    cout << res;


}