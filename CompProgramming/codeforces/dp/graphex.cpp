#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct dsu{
    vector<int> p, sz;
    dsu(int n) : p(n), sz(n, 1){
        iota(p.begin(), p.end(), 0);
    }

    int find(int v){
        if (v == p[v]) return v;
        p[v] = find(p[v]);
        return p[v];
    }

    int same(int v1, int v2){
        return find(v1) == find(v2);
    }

    int merge(int v1, int v2){
        if (same(v1, v2)) return 0;
        int p1 = find(v1);
        int p2 = find(v2);
        if (sz[p1] < sz[p2]) swap(p1, p2);
        p[p2] = p1;
        sz[p1] += sz[p2];
        return 1;
    }
};

void solve() {
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::array<int, 3>> edges(m);
    for (int i = 0; i < m; i++) {
        int v, u, w;
        std::cin >> v >> u >> w;
        v--, u--;  
        edges[i] = {v, u, w};
    }

    
    std::sort(edges.begin(), edges.end(), [&](const std::array<int, 3>& a, const std::array<int, 3>& b) {
        return a[2] < b[2];
    });

    constexpr int INF = 1e9;
    std::vector<int> value(m + 1);
    std::vector<std::vector<std::vector<int>>> dis(n + 1, std::vector<std::vector<int>>(n, std::vector<int>(n, INF)));

    
    for (int i = 0; i < n; i++) {
        dis[0][i][i] = 0;
    }
    for (const auto& edge : edges) {
        int v = edge[0], u = edge[1];
        dis[0][v][u] = dis[0][u][v] = 1;
    }

    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dis[0][i][j] = std::min(dis[0][i][j], dis[0][i][k] + dis[0][k][j]);
            }
        }
    }

    
    int p = 1;
    dsu uf(n);
    for (const auto& edge : edges) {
        int v = edge[0], u = edge[1], w = edge[2];
        if (uf.merge(v, u)){
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dis[p][i][j] = std::min({dis[p - 1][i][j], dis[p - 1][i][v] + dis[p - 1][u][j], dis[p - 1][i][u] + dis[p - 1][v][j]});
                }
            }
            value[p++] = w;
        }
    }

    
    while (q--) {
        int v, u, k;
        std::cin >> v >> u >> k;
        v--, u--;  

        int low = -1, high = n;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (dis[mid][v][u] < k) {
                high = mid;
            } else {
                low = mid;
            }
        }
        std::cout << value[high] << " ";
    }
    std::cout << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
