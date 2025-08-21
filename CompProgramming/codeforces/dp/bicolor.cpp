#include <bits/stdc++.h>
// #include "debug.h"
#define LL long long
#define pb push_back
using namespace std;
int N, K;
string wd;
int mod = 998244353;

void modadd(int &a, int b){
    a = (a + b) % mod;
}
int main(){
    cin >> N >> K;

    vector<vector<vector<int>>> dp(1000 + 1, vector<vector<int>>(2000 + 1, vector<int>(4, 0)));
    dp[1][1][0] = 1;
    dp[1][2][1] = 1;
    dp[1][2][2] = 1;
    dp[1][1][3] = 1;
    // debug(dp);
    for (int i = 1; i < N; i++){
        for (int j = 0; j < K + 1; j++){
            for (int msk = 0; msk < (1 << 2); msk++){
                for (int add = 0; add < (1 << 2); add++){
                    int comp = 0;
                    if ((msk >> 1) ^ (add >> 1)) comp++;
                    if ((msk & 1) ^ (add & 1)) comp++;
                    if ((add == 0 || add == 3) && comp > 0){
                        comp--;
                    }
                    if (j + comp <= K) modadd(dp[i + 1][j + comp][add], dp[i][j][msk]); 

                }
            }
        }
    }
    

    int res = 0;
    for (int msk = 0; msk < (1 << 2); msk++){
        modadd(res, dp[N][K][msk]);
    }
    cout << res;
}