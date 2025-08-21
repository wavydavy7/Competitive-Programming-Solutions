#include <bits/stdc++.h>
// #include "debug.h"
#define LL long long
#define pb push_back
using namespace std;
int N, K;
string wd;
vector<vector<int>> tr(401, vector<int>(401, 0));
vector<vector<int>> dp(401, vector<int>(401, 401));
vector<int> visited(401, 0);
vector<int> pe(401, 0);
vector<vector<vector<int>>> saved(401, vector<vector<int>>(401));


void dfs(int node){
    visited[node] = 1;
    dp[node][1] = 0; 
    for (int i = 1; i <= N; i++){
        if (tr[node][i] && !visited[i]){
            dfs(i);
            int e = tr[node][i];
            pe[i] = e;
            for (int s1 = N - 1; s1; s1--){
                for (int s2 = 1; s2 <= N; s2++){
                    if (s1 + s2 <= N && dp[node][s1 + s2] > dp[node][s1] + dp[i][s2]){
                        dp[node][s1 + s2] = dp[node][s1] + dp[i][s2];
                        saved[node][s1 + s2] = saved[node][s1];
                        saved[node][s1 + s2].insert(saved[node][s1 + s2].end(), saved[i][s2].begin(), saved[i][s2].end());
                    }
                }
                dp[node][s1]++; //not including it in 
                saved[node][s1].pb(e);
            }
            
        }
    }
}

int main(){
    cin >> N >> K;

    for (int i = 1; i <= N - 1; i++){
        int a, b;
        cin >> a >> b;
        tr[a][b] = i;
        tr[b][a] = i;
    }
    dfs(1);
    vector<int> res = saved[1][K];
    int cuts = dp[1][K];
    for (int i = 2; i <= N; i++){
        if (dp[i][K] + 1 < cuts){
            cuts = dp[i][K] + 1;
            res = saved[i][K];
            res.pb(pe[i]);
            // debug(res);
            // debug(cuts);
        }
    }
    cout << cuts << endl;
    for (auto a : res){
        cout << a << endl;
    }
    
}