#include <bits/stdc++.h>
// #include "debug.h"
using namespace std;
#define pb push_back
typedef long long ll;
const int MOD = 1e9 + 7;
const int MX = 300000;
int N, M;
vector<ll> cities;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        int x;
        cin >> x;
        cities.pb(x);
    }
    map<int, vector<tuple<int, int, int>>> mp;

    for (int i = 0; i < M; i++){
        int s, f, c, r;
        cin >> s >> f >> c >> r;
        mp[--s].pb({--f, c, r});
    }

    // vector<vector<vector<ll>>> dp(N, vector<vector<ll>>(N, vector<ll>(N + 1, 0)));
    ll dp[N][N + 1];
    memset(dp, 0, sizeof(dp));
    ll ans = 0;
    for (int l = 0; l < N; l++){
        for (int rp = l; rp < N; rp++) dp[rp][0] = cities[rp] - cities[l];

        for (int k = 1; k < N + 1; k++){
            int op = l; //op can be anything that is less, varying upon r 
            for (int r = l; r < N; r++){
                while (op < r && max(dp[op][k - 1], cities[r] - cities[op]) >= max(dp[op + 1][k - 1], cities[r] - cities[op + 1])) { //if the distance from here gets too small, you can only worsen
                    op++;
                }
                dp[r][k] = max(dp[op][k - 1], cities[r] - cities[op]);
                // debug(tuple<int, int, int> {l, r, k});
                // debug(dp[l][r][k]);
            }
        }
        for (auto tup : mp[l]){
            ans = max(ans, dp[get<0>(tup)][get<2>(tup)] * get<1>(tup));
        }
    }

    // debug(dp);


    // ll res = 0;
    // for (int i = 0; i < M; i++){
    //     int s, f, c, r;
    //     cin >> s >> f >> c >> r;
    //     // debug(dp[s - 1][f - 1][r] * c);
    //     res = max(res, dp[s - 1][f - 1][r] * c);
    // }

    cout << ans;
}