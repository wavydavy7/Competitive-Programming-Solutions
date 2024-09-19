#include <bits/stdc++.h>
#define pb push_back
using namespace std;

pair<int, int> adj[410][410];
int n;
int MX = 41000;
int matches[210];
int matching(int node, int sink){
    int par[410], visited[410], d[410];
    fill(par, par + 410, -1);
    fill(visited, visited + 410, 0);
    fill(d, d + 410, MX);
    d[node] = 0;

    auto avail = [&](){
        queue<int> q;
        q.push(node);
        while (!q.empty()){
            int val = q.front();
            q.pop();
            visited[val] = 0;
            for (int i = 0; i < 410; i++){
                if (adj[val][i].first != -1){
                    if (adj[val][i].first > 0 && (d[i] > d[val] + adj[val][i].second)){
                        d[i] = d[val] + adj[val][i].second;
                        // cout << i << " ";
                        par[i] = val;
                        if (!visited[i]){
                            visited[i] = 1;
                            q.push(i);
                        }
                    }
                }
            }
        }
        // cout << "sink: " << par[sink];
        // for (int i = 0; i < 410; i++){
        //     cout << i << " = " << par[i] << " ";
        // }
        return par[sink] != -1;

    };

    int total_cost = 0;
    while (avail()){
        // cout << "avail";
        int on = sink;
        int red = MX;
        while (on != node){
            red = min(red, adj[par[on]][on].first);
            if (par[on] > 0 && par[on] <= n && on > n && on <= 2 * n) {
                matches[par[on]] = on - n;
            }
            on = par[on];
        }
        on = sink;
        while (on != node){
            adj[par[on]][on].first -= red;
            adj[on][par[on]].first += red;
            on = par[on];
        }
        total_cost += d[sink] * red; // Multiply by the flow
        fill(par, par + 410, -1);
        fill(visited, visited + 410, 0);
        fill(d, d + 410, MX);
        d[node] = 0;
    }
    return total_cost;
}

int main(){
    cin >> n;
    for (int i = 0; i < 410; i++){
        for (int j = 0; j < 410; j++){
            adj[i][j] = {-1, -1};
        }
    }
    for (int i = 1; i <= n; i++){
        adj[0][i] = {1, 0};
        for (int j = 1; j <= n; j++){
            int val;
            cin >> val;
            adj[i][n + j] = {1, val};
            adj[n + j][i] = {0, -val};
        }
        adj[i + n][2*n + 1] = {1, 0};
    }
    // for (int i = 0; i < 410; i++){
    //     for (int j = 0; j < 410; j++){
    //         cout << adj[i][j].first << "," << adj[i][j].second << " ";
    //     }
    //     cout << "\n";
    // }
    
    cout << matching(0, 2*n + 1) << "\n";
    for (int i = 1; i <= n; i++){
        cout << i << " " << matches[i] << "\n";
    }
}
