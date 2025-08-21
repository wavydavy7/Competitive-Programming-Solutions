#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
vector<int> adj[MAXN];  // original tree (0-indexed)
int sub[MAXN];          // subtree sizes
bool removed[MAXN];     // whether a node is already chosen as a centroid
int centPar[MAXN];      // parent in the centroid tree

//---------Centroid Decomp---------//

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

function<void(int, int)> decompose = [&](int v, int p) {
    int tot = dfsSubtree(v, -1);
    int centroid = findCentroid(v, -1, tot);
    removed[centroid] = true;
    centPar[centroid] = p;  // p == -1 for root of centroid tree
    for (int u : adj[centroid]) {
        if (!removed[u])
            decompose(u, centroid);
    }
};