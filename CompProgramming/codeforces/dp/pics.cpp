#include <bits/stdc++.h>
// #include "debug.h"
#define LL long long
#define pb push_back
using namespace std;
int N, M;
const int MX = 151;
LL mod = 998244353;

vector<int> a(MX, 0);
vector<int> w(MX, 0);
//dp[rnd][pos][neg]
LL dp[MX][MX][MX];

LL modexp(LL base, LL exp, LL mod) {
    LL res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

void modadd(LL &a, LL b){
    a = (a + b) % mod;
}

int main(){
    cin >> N >> M;
    
    int sump = 0;
    int sumn = 0;
    for (int i = 0; i < N; i++){
        cin >> a[i];
    }
    
    for (int i = 0; i < N; i++){
        cin >> w[i];
        if (a[i] == 1) sump += w[i];
        else sumn += w[i];
    }
    
    for (int wh = 0; wh < N; wh++){
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;
        int cpp = sump;
        int cpn = sumn;
        if (a[wh] == 1) cpp -= w[wh];
        else cpn -= w[wh];
        for (int i = 0; i < M; i++){
            for (int j = 0; j <= i; j++){
                for (int k = 0; k <= i - j; k++){
                    LL own = i - j - k; 
                    LL total = own * (a[wh] == 1 ? 1 : -1) + w[wh] + (cpp + j) + (cpn - k);
                    // if (own * (a[wh] == 1 ? 1 : -1) + w[wh] <= 0) continue;
                    if (total <= 0) continue;
                    modadd(dp[i + 1][j][k + 1], (cpn - k) * modexp(total, mod-2, mod) % mod * dp[i][j][k] % mod);
                    modadd(dp[i + 1][j + 1][k], (cpp + j) * modexp(total, mod-2, mod) % mod * dp[i][j][k] % mod);
                    modadd(dp[i + 1][j][k], (own*(a[wh] == 1 ? 1 : -1) + w[wh]) * modexp(total, mod-2, mod) % mod * dp[i][j][k] % mod);
                    // debug(own*(a[wh] == 1 ? 1 : -1) + w[wh]);
                    // debug(i + 1, j, k + 1); 
                    // debug(dp[i + 1][j][k + 1]);
                    // debug(i + 1, j + 1, k); 
                    // debug(dp[i + 1][j + 1][k]);
                    // debug(i + 1, j, k); 
                    // debug(dp[i + 1][j][k]);
                }
            }
        }
        LL ans = 0;
        for (int j = 0; j <= M; j++){
            for (int k = 0; k <= M; k++){
                int own = M - j - k;
                if (own * (a[wh] == 1 ? 1 : -1) + w[wh] <= 0) continue;
                // debug(M, j, k);
                // debug(dp[M][j][k]);
                // debug(own);
                modadd(ans, (own * (a[wh] == 1 ? 1 : -1) + w[wh])*dp[M][j][k] % mod);
            }
        }
        cout << ans << endl;
    }
}