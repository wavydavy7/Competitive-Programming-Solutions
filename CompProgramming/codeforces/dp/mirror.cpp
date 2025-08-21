// #include <bits/stdc++.h>
//#include "debug.h"
// #define LL long long
// #define pb push_back
// using namespace std;
// int N, K;
// int MX = 1e5 + 1;
// vector<vector<int>> tr(MX);
// vector<vector<int>> longest(MX);
// vector<int> visited(MX, 0);
// // vector<int> visited1(MX, 0);
// // vector<int> visited2(MX, 0);
// // vector<int> visited3(MX, 0);
// map<int, int> mp1;
// map<int, int> mp2;
// map<int, int> mp3;
// pair<int, vector<int>> diam = {0, vector<int>(1, 0)};



// void dfs(int v){
//     visited[v] = 1;
//     pair<int, int> mx1 = {0, 0};
//     pair<int, int> mx2 = {0, 0};
//     for (auto kd : tr[v]){
//         if (!visited[kd]){
//             dfs(kd);
//             if (longest[kd].size() > mx1.first){
//                 mx2 = mx1; 
//                 mx1.first = longest[kd].size();
//                 mx1.second = kd;
//             }
//             else if (longest[kd].size() > mx2.first){
//                 mx2.first = longest[kd].size();
//                 mx2.second = kd;
//             }
//             //update the diam
//         }
//     }
//     longest[v] = longest[mx1.second];
//     longest[v].pb(v);
//     // debug(v);
//     // debug(longest[v]);
//     // debug(mx1);
//     // debug(mx2);
//     if (mx1.first + mx2.first + 1 > diam.first){
//         diam.first = mx1.first + mx2.first + 1;
//         diam.second = longest[v];
//         diam.second.insert(diam.second.end(), longest[mx2.second].rbegin(),longest[mx2.second].rend()); //check 
//     }
//     // debug(diam);
    
// }

// int dfs2(int v, int d, vector<int> &vis, map<int, int> &corr){
//     vis[v] = 1;
//     int deg = tr[v].size();
//     if (corr.count(d) > 0 && corr[d] != deg){
//         return 0;
//     }
//     corr[d] = deg;
//     for (auto kd : tr[v]){
//         if (!vis[kd]){
//             if (!dfs2(kd, d + 1, vis, corr)) return 0;
//         }
        
//     }
//     return 1;
// }
// int main(){
//     cin >> N;
//     for (int i = 0; i < N - 1; i++){
//         int a, b;
//         cin >> a >> b;
//         tr[a].pb(b);
//         tr[b].pb(a);
//     }
//     //I want to find the diameter
//     dfs(1);
//     // debug(diam);
//     //now, I want to check 3 points
//     int p1 = diam.second[0];
//     int p2 = diam.second[diam.first - 1];
//     int p3 = 1;
//     int sz = diam.second.size();
//     if (sz % 2){
//         p3 = diam.second[sz >> 1];
//     }
//     fill(visited.begin(), visited.end(), 0);
//     if (dfs2(p1, 0, visited, mp1)) {
//         cout << p1;
//         return 0;
//     }
//     fill(visited.begin(), visited.end(), 0);
//     if (dfs2(p2, 0, visited, mp2)) {
//         cout << p2;
//         return 0;
        
//     }
//     fill(visited.begin(), visited.end(), 0);
//     if (dfs2(p3, 0, visited, mp3)){
//         cout << p3;
//         return 0;
//     }
//     cout << -1;
// }
#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 100000;

int N, M;
// Adjacency list
vector<int> adj[MAXN + 1];
int dist[100000];

pair<int,int> dfsFarthest(int start, int parent, int dist, vector<int> &visited) {
    visited[start] = 1;
    pair<int,int> best = {dist, start};
    for (int nxt : adj[start]) {
        if (nxt == parent) continue;
        if (!visited[nxt]) {
            auto temp = dfsFarthest(nxt, start, dist + 1, visited);
            if (temp.first > best.first) {
                best = temp;
            }
        }
    }
    return best;
}

// Collect the path from 'src' to 'target' in 'path'
bool dfsBuildPath(int src, int target, int parent, vector<int> &path, vector<int> &vis) {
    path.push_back(src);
    if (src == target) return true;
    vis[src] = 1;
    for (int nxt : adj[src]) {
        if (nxt == parent) continue;
        if (!vis[nxt]) {
            if (dfsBuildPath(nxt, target, src, path, vis)) {
                return true;
            }
        }
    }
    path.pop_back();
    return false;
}

bool validateCandidate(int cand) {
    vector<int> visitedLoc(N+1, 0), depthDeg(N+1, -1);

    // DFS stack or recursion: (node, depth)
    stack<pair<int,int>> st;
    st.push({cand, 0});
    visitedLoc[cand] = 1;
    while (!st.empty()) {
        auto [node, depth] = st.top();
        st.pop();

        int deg = (int)adj[node].size();
        if (depthDeg[depth] != -1 && depthDeg[depth] != deg) {
            return false;
        }
        depthDeg[depth] = deg;

        for (int nxt : adj[node]) {
            if (!visitedLoc[nxt]) {
                visitedLoc[nxt] = 1;
                st.push({nxt, depth+1});
            }
        }
    }

    return true;
}


int findLeaf(int start) {
    // If start is already a leaf
    if (adj[start].size() <= 1) return start;
    // BFS to find a leaf
    vector<int> vis(N+1, 0);
    queue<int>q;
    q.push(start);
    vis[start] = 1;
    memset(dist, 0x7f, sizeof(dist));
    dist[start] = 0;
    while(!q.empty()){
        int node = q.front(); q.pop();
        // If this is a leaf
        for(int nxt: adj[node]){
            if(!vis[nxt] && adj[nxt].size() < 3){
                //debug(nxt);
                //debug(adj[nxt].size());
                dist[nxt] = dist[node] + 1;
                vis[nxt] = 1;
                q.push(nxt);
            }
        }
    }
    
    int m = -1;
    dist[m] = 100000;
    for(int i=1;i<=N;i++){
        if(adj[i].size()==1 && (m==-1 || dist[i]<dist[m])) {
            m=i;
            //debug(m);
        }
    }
    
    return m; // fallback, though we should find a leaf eventually
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    // Build adjacency
    for(int i = 1; i <= N-1; i++){
        int a,b; 
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    
    {
        vector<int> visited1(N+1, 0);
        auto far1 = dfsFarthest(1, -1, 0, visited1); 
        // far1.second is the node farthest from 1
        vector<int> visited2(N+1, 0);
        auto far2 = dfsFarthest(far1.second, -1, 0, visited2);
        // far2.second is the node farthest from far1.second => diameter endpoints
        // Build the diameter path
        vector<int> path;
        vector<int> vis(N+1, 0);
        dfsBuildPath(far1.second, far2.second, -1, path, vis);

        
        int p1 = far1.second;
        int p2 = far2.second;
        // We define 'semiTop' as the middle of 'path'
        int len = (int)path.size();
        int semiTop = path[len / 2]; // middle node in the diameter path

        // We'll pick one more node: from 'semiTop', find a leaf
        int leafFromSemi = findLeaf(semiTop);


        vector<int> candidates = {p1, p2, semiTop, leafFromSemi};
        //debug(candidates);
        for(int c: candidates){
            if(validateCandidate(c)){
                cout << c << "\n";
                return 0;
            }
        }
        // If none valid
        cout << -1 << "\n";
    }

    return 0;
}
