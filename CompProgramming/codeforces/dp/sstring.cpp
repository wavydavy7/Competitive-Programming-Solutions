#include <bits/stdc++.h>
// #include "debug.h"
#define LL long long
#define pb push_back
using namespace std;
int N, M;
string wd;
int mod = 1e9 + 7;

int main(){
    cin >> N >> M;
    cin >> wd;
    vector<int> nodes(N, 0);
    map<int, int> deg;
    queue<int> q; 
    map<int, set<int>> rev;
    vector<vector<int>> dp(N, vector<int>(27, 0));
    int cnt = 0;
     

    auto upddeg = [&] (int v, int u){
        rev[v].erase(u);
        deg[u]--;
        for (int i = 0; i < 26; i++){
            dp[u][i] += dp[v][i];
        }
        if (deg[u] == 0) q.push(u);
    };

    for (int i = 0; i < N; i++){
        nodes[i] = wd[i];
        dp[i][wd[i] - 'a'] = 1;
    }

    for (int i = 0; i < N; i++){
        deg[i] = 0;
    }
    // debug(M);
    for (int i = 0; i < M; i++){
        int a, b; 
        cin >> a >> b;
        a--, b--;
        if (rev[b].count(a) == 0) {  // Avoid duplicate edges
            rev[b].insert(a);
            deg[a]++;
        }
    }
    
    for (int i = 0; i < N; i++){
        if (deg[i] == 0) q.push(i);
    }
    // debug(q);
    while (!q.empty()){
        int num = q.front();
        q.pop();
        cnt++;
        for (auto it = rev[num].begin(); it != rev[num].end(); ) {
            int a = *it;
            it = rev[num].erase(it); // Erase and move iterator to the next valid position
            deg[a]--;
            for (int i = 0; i < 26; i++) {
                dp[a][i] = max(dp[a][i], dp[num][i] + (wd[a] - 'a' == i));
            }
            if (deg[a] == 0) q.push(a);
        }
    }
    if (cnt != N){
        cout << -1;
        return 0;
    }
    else{
        int mx =  0;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < 26; j++){
                mx = max(mx, dp[i][j]);
            }
        }
        cout << mx;
    }

}