#include <bits/stdc++.h>
// #include "debug.h"
#define ll long long 
using namespace std;
const int MOD = 1e9 + 7;

int main(){
    int N;
    cin >> N;
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
    int cnt[71][2];
    vector<vector<int>> dp(1 << 19, vector<int>(71, 0));
    int mask[71] = {0};
    for (int i = 1; i <= 70; i++){
        cnt[i][0] = 1;
        cnt[i][1] = 0;
    }
    for (int i = 0; i < N; i++){
        int num;
        cin >> num;
        int temp = cnt[num][0];
        cnt[num][0] = (cnt[num][0] + cnt[num][1]) % MOD;
        cnt[num][1] = (cnt[num][1] + temp) % MOD;
    }

    for (int i = 1; i <= 70; i++){
        for (int p = 0; p < 19; p++){
            int amt = 0;
            int at = i;
            while (at % primes[p] == 0) {
                amt++;
                at /= primes[p];
            }
            mask[i] |= (amt % 2) << p; 
        }
    }
    dp[0][0] = 1;
    for (int i = 1; i <= 70; i++){
        for (int msk = 0; msk < (1 << 19); msk++){
            dp[msk][i] = (dp[msk][i - 1] * 1LL * cnt[i][0]) % MOD;
            dp[msk][i] += (dp[msk ^ mask[i]][i - 1] * 1LL * cnt[i][1]) % MOD;
            dp[msk][i] %= MOD;
        }
    }
    cout << (dp[0][70] + MOD - 1) % MOD;
    return 0;

}