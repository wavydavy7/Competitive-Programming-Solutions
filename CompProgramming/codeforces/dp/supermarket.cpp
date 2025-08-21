#include <bits/stdc++.h>
// #include "debug.h"
using namespace std;
#define pb push_back
typedef long long ll;
const int MOD = 1e9 + 7;
const int MX = 5001;
const ll INF = 1e15; 
int n, b;

vector<vector<int>> tr;
vector<int> dis;
vector<int> ndis;
vector<ll> dp[MX][2];


vector<ll> merge(vector<ll> v, vector<ll> c){ //combining subtrees is O(N^2) total, use a+b, ab argument 
    vector<ll> comb(v.size() + c.size() - 1, INF);
    for (int i = 0; i < v.size(); i++){
        for (int j = 0; j < c.size(); j++){
            comb[i + j] = min(comb[i + j], v[i] + c[j]);
        }
    }
    return comb;
}
void dfs(int v){

    //how filled is tr? 
    dp[v][0] = {0, ndis[v]};
    dp[v][1] = {INF, dis[v]};
    for (auto c : tr[v]){
        dfs(c);
        dp[v][0] = merge(dp[v][0], dp[c][0]);
        dp[v][1] = merge(dp[v][1], dp[c][1]);
    }
    for (int i = 0; i < dp[v][1].size(); i++){
        dp[v][1][i] = min(dp[v][1][i], dp[v][0][i]);
    }
    
}
int main(){
    cin >> n >> b;
    tr.resize(n + 1);
    dis.resize(n + 1);
    ndis.resize(n + 1);

    for (int i = 0; i < n; i++){
        ll c, d;
        cin >> c >> d;
        ll cst = c - d;
        dis[i] = cst;
        ndis[i] = c;
        if (i) {
            int p;
            cin >> p;
            tr[--p].pb(i);
        }
    } //0-index
    // debug(tr);
    dfs(0);

    int mx = 0;
    for (int tk = 0; tk < 2; tk++){
        for (int sz = 0; sz < dp[0][tk].size(); sz++){
            if (dp[0][tk][sz] <= b) mx = max(mx, sz);
        }
    }

    cout << mx;

}
