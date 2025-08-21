#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    
    while (t--){
        int n;
        cin >> n;
        vector<vector<int>> adj(n);
        vector<int> sub(n);
        vector<int> removed(n, 0);
        pair<int, int> rem = {INT_MAX, -1};
        int color = 0;
        vector<int> colors(n, -1);
        function<int(int, int, int)> dfs2 = [&](int v, int p, int dist) {
            colors[v] = color++ % ((n-1)/2) + 1;
            if (adj[v].size() == 1 && dist < rem.first){
                rem.first = dist;
                rem.second = v;
            }
            for (int u : adj[v]) {
                if (u == p || removed[u])
                    continue;
                dfs2(u, v, dist + 1);
            }
            return 0;
        };
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
                if (sub[u] > tot / 2) //any of the subtrees 
                    return findCentroid(u, v, tot);
            }//we find one with the one including the centroid <= tot - 1 / 2
            return v; 
        };

        for (int i = 0; i < n - 1; i++){
            int a, b;
            cin >> a >> b;
            a--, b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        dfsSubtree(0, -1);
        int v = findCentroid(0, -1, n);
        dfs2(v, -1, 0);
        //we need to remove v 
        int merged = max(rem.second, adj[rem.second][0]);
        colors[v] = colors[merged];
        colors[merged] = 0;
        cout << rem.second + 1 << " " << adj[rem.second][0] + 1 << endl;
        for (auto x : colors){
            cout << x << " ";
        }
        cout << endl;
    }

    
}