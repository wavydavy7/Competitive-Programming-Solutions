#include <bits/stdc++.h>
#define pb push_back
using namespace std;

int n, m;
vector<vector<pair<int, int> > > adj;
vector<int> used;
vector<int> path;
vector<int> degrees;
void dfs(int node) {
	while (!adj[node].empty()) { //using a while loop is faster?
		auto [son, idx] = adj[node].back();
		adj[node].pop_back(); //we know we can't go here anymore 
		if (used[idx]) { continue; }
		used[idx] = true;
		dfs(son);
	}
	path.push_back(node);
}


int main(){
    cin >> n >> m;
    adj.resize(n + 1);
    used.resize(m + 1);
    degrees.resize(n + 1);
    fill(used.begin(), used.end(), 0);
    int copy = m;
    while (m--){
        int a, b;
        cin >> a >> b;
        adj[--a].pb(make_pair(--b, m));
        adj[b].pb(make_pair(a, m)); //we start with edge value m - 1... go to edge value 0
        degrees[a]++;
        degrees[b]++;
    }
    for (int i = 0; i < n; i++){
        if (degrees[i] % 2){
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    dfs(0);

    if(path.size() != copy + 1){
        cout << "IMPOSSIBLE";
        return 0;
    }
    for (auto p : path){
        cout << p + 1 << " ";
    }
    
}