#include <bits/stdc++.h>
// #include "debug.h"
#define ll long long
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--){
        int n, q;
        cin >> n >> q;
        vector<vector<ll>> gr(n, vector<ll>(n, 0));
        vector<vector<ll>> psm(n + 1, vector<ll>(n + 1, 0));
        vector<vector<ll>> cs(n + 1, vector<ll>(n + 1, 0));
        vector<vector<ll>> rs(n + 1, vector<ll>(n + 1, 0));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cin >> gr[i][j];
            }
        }
        //pre

        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                psm[i][j] = psm[i - 1][j] + psm[i][j - 1] - psm[i - 1][j - 1] + gr[i - 1][j - 1];
                cs[i][j] = cs[i - 1][j] + cs[i][j - 1] - cs[i - 1][j - 1] + j * gr[i - 1][j - 1];
                rs[i][j] = rs[i - 1][j] + rs[i][j - 1] - rs[i - 1][j - 1] + i * gr[i - 1][j - 1];
            }
        }


        for (int i = 0; i < q; i++){
            ll x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--, y1--, x2--, y2--;
            // vector<ll> qu = {x1, y1, x2, y2};
            // debug(qu);
            ll res = 0;
            res += cs[x2 + 1][y2 + 1] - cs[x1][y2 + 1] - cs[x2 + 1][y1] + cs[x1][y1];
            ll sq = psm[x2 + 1][y2 + 1] - psm[x1][y2 + 1] - psm[x2 + 1][y1] + psm[x1][y1];
            res -= sq * (y1);
            // debug(res);
            ll m = rs[x2 + 1][y2 + 1] - rs[x1][y2 + 1] - rs[x2 + 1][y1] + rs[x1][y1];
            m -= sq * (x1 + 1);
            m *= (y2 - y1 + 1);
            // debug(m);
            res += m;
            cout << res << " ";
        }
        cout << "\n";
    }
}