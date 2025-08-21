#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    vector<int> e;
    void init(int N) { e = vector<int>(N, -1); }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool unite(int x, int y)
    {
        x = get(x), y = get(y);
        if (x == y)
            return 0;
        if (e[x] > e[y])
            swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return 1;
    }
};

int main()
{
    int N;
    cin >> N;
    vector<tuple<int, int, int>> edges;
    for (int i = 1; i <= N; ++i)
    {
        int a, v;
        cin >> a >> v;
        edges.push_back({v, i, a});
    }
    sort(edges.rbegin(), edges.rend());
    DSU D;
    D.init(N + 1);
    int64_t ans = 0;
    for (auto [v, x, y] : edges)
        if (D.unite(x, y))
            ans += v;
    cout << ans << "\n";
}
