#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
const int MX = 6e5 + 50;
#ifdef LOCAL
#include "../../algo/debug.h"
#else
#define debug(...) 42
#endif
vector<int> tin, tout;
vector<vector<int>> up;
vector<vector<int>> adj(MX);
vector<pair<int, int>> t1[MX];
vector<pair<int, int>> t2[MX];
map<pair<int, int>, pair<ll, ll>> mp;
int np;
int n;
int l;
int comp = 1;


//we wanna get the distance 

int main(){
    auto compare = [&](const pair<ll, ll>& a, const pair<ll, ll>& b){
        if (a.first == b.first){
            return a.second < b.second;
        }
        return a.first < b.first;
    };
    cin >> n;
    vector<ll> cross(n + 1, 0);
    set<pair<ll, ll>, decltype(compare)> s(compare); 
    for (int i = 0; i < n; i++){
        cin >> cross[i];
        s.insert({cross[i], i});
    }
    

    vector<ll> idxe(2*n);

    for (int i = 0; i < n - 1; i++){
        int x, y;
        ll w1, w2;
        cin >> x >> y >> w1 >> w2; //we have edge from
        //how to store... maybe edge to edge?
        x--;
        y--;
        idxe[2*i] = w1;
        idxe[2*i + 1] = w2; 
        adj[x].push_back(y);
        adj[y].push_back(x);
        t1[x].push_back({y, i});
        t1[y].push_back({x, i});
        mp[{x, y}] = {w1, w2};
        mp[{y, x}] = {w2, w1};
    }

    while (!s.empty()){
        ll idx = s.begin()->second;
        ll w = s.begin()->first;
        s.erase(s.begin());

        for (auto x : adj[idx]){
            if (cross[x] > w + mp[{idx, x}].first + mp[{idx, x}].second){
                auto it = s.find({cross[x], x});
                if (it != s.end()) {
                    s.erase(it);
                }
                cross[x] = w + mp[{idx, x}].first + mp[{idx, x}].second;
                s.insert({cross[x], x});
            }
        }
    }

    int q;
    cin >> q;
    vector<vector<int>> qqs(q, vector<int>(2));
    vector<vector<int>> assoc(n);
    vector<ll> qans(q, 0);
    vector<ll> ans(q, -1);

    vector<int> sub(n);      
    vector<bool> removed(n, false);     
    vector<int> centPar(n, -1); 
    vector<ll> centd(n, LLONG_MAX);     

    
    function<int(int, int)> dfsSubtree = [&](int v, int p) {
        sub[v] = 1;
        for (int u : adj[v]) {
            if (u == p || removed[u])
                continue;
            sub[v] += dfsSubtree(u, v);
        }
        return sub[v];
    };

    function<int(int, int, int)> findCentroid = [&](int v, int p, int tot) -> int{
        for (int u : adj[v]) {
            if (u == p || removed[u])
                continue;
            if (sub[u] > tot / 2)
                return findCentroid(u, v, tot);
        }
        return v;
    };

    vector<vector<ll>> dp(2*n, vector<ll>(2, 0));
    vector<int> proc;
    function<void(int, int, int)> dfs2 = [&](int v, int p, int idx){ //v is the overlapped index
        //find everything in its subtree
        if (p == -1){
            dp[2*v][0] = 0;
            dp[2*v][1] = cross[v];
            dp[2*v + 1][1] = 0;
            dp[2*v+ 1][0] = cross[v];
        }
        else{
            dp[2*v][0] = min(dp[2*p][0] + idxe[2*idx], dp[2*p + 1][0] + idxe[2*idx + 1] + cross[v]);
            dp[2*v][1] = min(dp[2*p][1] + idxe[2*idx], dp[2*p + 1][1] + idxe[2*idx + 1] + cross[v]); 
            dp[2*v + 1][1] = min(dp[2*p + 1][1] + idxe[2*idx + 1], dp[2*p][1] + idxe[2*idx] + cross[v]);
            dp[2*v + 1][0] = min(dp[2*p + 1][0] + idxe[2*idx + 1], dp[2*p][0] + idxe[2*idx] + cross[v]);
        }
        for (auto x : t1[v]){
            if (x.first != p && removed[x.first] == false){
                dfs2(x.first, v, x.second); //give you the edge weight 
            }
        }

        for (auto x : assoc[v]){
            if (ans[x] != -1) continue;
            if (qans[x] == comp){
                proc.push_back(x);
            }
            else{
                qans[x] = comp;
            }
        }
    };

    function<void(int, int)> decompose2 = [&](int v, int p) {
        int tot = dfsSubtree(v, -1);
        int centroid = findCentroid(v, -1, tot);
        //you found the centroid
        //once you do this, you wanna see if there was anything that was contained in both that centroid 
        removed[centroid] = true;
        for (int u : adj[centroid]) {
            if (!removed[u]){
                decompose2(u, centroid);
            }
        }
        removed[centroid] = false;
        dfs2(centroid, -1, -1);
        for (auto aq : proc){
            ans[aq] = min(dp[qqs[aq][0]][0] + dp[qqs[aq][1]][0], dp[qqs[aq][0]][1] + dp[qqs[aq][1]][1]);
        }
        proc.clear();
        comp++;
    };
    //storing the queries in an array and doing offline processing is kinda smart
    
    for (int i = 0; i < q; i++){
        int u, v;
        cin >> u >> v;
        //if it's even we use first, else second
        u--, v--;
        //need to make a query 
        qqs[i][0] = u;
        qqs[i][1] = v;
        //we need to look at the index
        assoc[u / 2].push_back(i); //need to find the 2 new nodes 
        assoc[v / 2].push_back(i);

    }
    decompose2(0, -1);
    for (auto aq : ans){
        cout << aq << endl;
    }
}

