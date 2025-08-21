#include <bits/stdc++.h>
// #include "debug.h"
#define LL long long
#define pb push_back
using namespace std;
int N, K;
int MX = 200001;
vector<LL> cost(MX, 0);
vector<vector<int>> tr(MX);
vector<int> mxs(MX, 0);
vector<vector<LL>> dp(MX, vector<LL>(2, 0));
vector<int> selected(MX, 0);
vector<LL> total(MX, 0);
void dfs(int v, int p){
    dp[v][1] = 0;
    LL mx = 0;
    int l = 1;
    for (auto kd : tr[v]){
        if (kd != p){
            l = 0;
            dfs(kd, v);
            dp[v][1] += dp[kd][0];
            dp[v][0] += dp[kd][0];
            mx = max(mx, dp[kd][0] - dp[kd][1]);
        }
    }
    total[v] = dp[v][0];
    dp[v][1] -= mx;
    mxs[v] = mx;
    dp[v][0] = min(dp[v][0], cost[v] + dp[v][1]);
    if (l == 1) dp[v][0] = cost[v];
    // debug(v);
    // debug(dp[v][0]);
    // debug(dp[v][1]);
    //now I want to merge all the kids
}
 
void dfs2(int v, int p, pair<int, int> works){
    //we know the final result, so we propagate downwards 
    int lf = 1;
    int nused = 0;
    for (auto kd : tr[v]){
        if (kd != p){ 
            if (dp[v][0] == cost[v] + dp[v][1] && works.first) selected[v] = 1;
            bool validPath = 0;
            if (works.first && dp[v][0] == cost[v] + total[v] - dp[kd][0] + dp[kd][1]) validPath = 1;
            if (works.second && dp[v][1] == total[v] - dp[kd][0] + dp[kd][1]) validPath = 1;
            if (validPath) nused++;
        }
    }
    for (auto kd : tr[v]){
        if (kd != p) {
            int validPath = 0;
            lf = 0;
            //we want to be able to check if dp[kd][0 or 1] works
            //for the 1, we want to exclude one of them
            if (works.first && dp[v][0] == cost[v] + total[v] - dp[kd][0] + dp[kd][1]) validPath = 1;
            if (works.second && dp[v][1] == total[v] - dp[kd][0] + dp[kd][1]) validPath = 1;
            dfs2(kd, v, {!validPath || (works.first && dp[v][0] == total[v]) || (nused - validPath), validPath}); 
        }
    }
    
    if (lf) selected[v] = works.first;
    //what if dp[v][1] is valid? 
 
}
 
int main(){
    //we find the root
    cin >> N;
    vector<int> root(N + 1, 1);
    for (int i = 0; i < N; i++){
        cin >> cost[i + 1]; 
    }
    for (int i = 0; i < N - 1; i++){
        int a, b;
        cin >> a >> b;
        tr[a].pb(b);
        tr[b].pb(a);
    }
 
    dfs(1, -1);
    // call dfs to compute dp states
    //we could compute the optimal vectors with uf... but for all vectors?
    cout << dp[1][0] << " ";
    dfs2(1, -1, {1, 0});
    vector<int> can; 
    for (int i = 1; i <= N + 1; i++){
        if (selected[i]) can.pb(i);
    }
    cout << can.size() << endl;
    for (auto el : can){
        cout << el << " ";
    }
 
}