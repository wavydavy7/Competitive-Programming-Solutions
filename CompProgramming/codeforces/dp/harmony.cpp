#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
const int MOD = 1e9 + 7;
const int MX = 1e6 + 1;
int N;
vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
vector<int> a(101, 0);
int dp[101][1 << 16];
int mv[101][1 << 16];
int msk[59];
//16 total

int main(){
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> a[i];
    }
    for (int i = 1; i < 60; i++){
        int total = 0;
        for (int j = 0; j < 16; j++){
            if (i % primes[j] == 0){
                total |= (1 << j);
            }
            msk[i] = total;
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    
    for (int i = 0; i < N; i++){
        for (int j = 0; j < (1 << 16); j++){
            for (int cand = 1; cand < 60; cand++){
                if ((j & msk[cand]) == 0){
                    if (dp[i + 1][j | msk[cand]] > dp[i][j] + abs(cand - a[i])){
                        dp[i + 1][j | msk[cand]] = dp[i][j] + abs(cand - a[i]);
                        mv[i + 1][j | msk[cand]] = cand;
                    } 
                }
            }
        }
    }

    vector<int> ans;
    for (int i = N, m = min_element(dp[i], dp[i] + (1 << 16)) - dp[i]; ~i; m &= ~msk[mv[i][m]], i--){
        ans.pb(mv[i][m]);
    }
    for (int i = 0; i < N; i++){
        cout <<  ans[N - 1 - i] << " ";
    }
    
}