#include "bits/stdc++.h"
#define pb push_back
using namespace std;
const int MX = 1e5 + 5;

vector<vector<int> > AdjList(MX);
vector<bool> visited(MX, false);
vector<int> dfs_low(MX, 0), dfs_num(MX, -1);
int dfsNumberCounter = 0;
vector<int> res(MX);
vector<int> S;
int numSCC = 0;

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
    S.pb(u);
    visited[u] = true;
    for (int v : AdjList[u]) {
        if (dfs_num[v] == -1)
            tarjanSCC(v);
        if (visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    if (dfs_low[u] == dfs_num[u]) {
        numSCC++;
        while (true) {
            int v = S.back(); S.pop_back(); visited[v] = false;
            res[v] = numSCC;
            if (u == v) break;
        }
        printf("\n");
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        AdjList[a].pb(b);
    }

    for (int i = 1; i <= n; i++)
        if (dfs_num[i] == -1)
            tarjanSCC(i);
    
    cout << numSCC << "\n";
    for (int i = 1; i <= n; i++){
        cout << res[i] << " ";
    }
}