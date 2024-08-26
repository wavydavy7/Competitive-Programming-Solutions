#include <iterator>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <array>
using namespace std;
typedef long long ll;
#define MOD 1000000007
int N, M;
int Q;
unordered_map<int, vector<int>> adj;
unordered_map<int, vector<int>> upd;
unordered_map<int, set<int>> cycle;
int special_count[100001];
set<int> visited;
set<int> special;
set<array<int, 2>> illegal;

int depth[100001];
int up[100001][20];
int dfs(int node, int par)
{

    if (visited.find(node) != visited.end()) // if alr visited, we want to have all pts connected to the src
    {
        illegal.insert({node, par});
        special.insert(node);
        return node;
    }
    int flag = -1;

    visited.insert(node);
    for (int next : adj[node])
    {
        if (next == par || illegal.find({node, next}) != illegal.end())
        {
            continue;
        }

        int next_out = dfs(next, node);
        if (next_out == -1)
        {

            upd[node].push_back(next);
        }
        else if (next_out != -1 and next_out != node)
        {

            upd[next_out].push_back(node);
            cycle[next_out].insert(node);
            flag = next_out;
        }
    }

    if (node == flag)
    {
        // upd[node].pop_back();
        flag = -1;
    }
    return flag;
}

void dfs2(int v)
{
    for (int i = 1; i < 20; i++)
    {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    special_count[v] = special_count[up[v][0]] + (special.find(v) != special.end() ? 1 : 0);
    for (int x : upd[v])
    {
        if (x != up[v][0]) // if x isn't the parent
        {
            up[x][0] = v; // v is the parent
            depth[x] = depth[up[x][0]] + 1;

            dfs2(x);
        }
    }
}

int jump(int x, int d)
{
    for (int i = 0; i < 20; i++)
    {
        if (d & (1 << i))
        {
            x = up[x][i];
        }
    }
    return x;
}

int lca(int a, int b)
{
    if (depth[a] < depth[b])
    {
        swap(a, b);
    }
    a = jump(a, depth[a] - depth[b]);
    if (a == b)
        return a;
    for (int i = 19; i >= 0; i--)
    {
        int aT = up[a][i];
        int bT = up[b][i];
        if (aT != bT)
        {
            a = aT;
            b = bT;
        }
    }

    return up[a][0];
}

int to_one(int i)
{
    int res = 0;
    while (i != 0)
    {
        if (special.find(i) != special.end())
        {
            res++;
        }
        i = up[i][0];
    }
    return res;
}

ll mod_exp(ll base, ll exp, ll mod)
{
    ll result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int fr;
        int to;
        cin >> fr >> to;
        adj[fr].push_back(to);
        adj[to].push_back(fr);
    }
    dfs(1, 0);
    // if (special.find(1) != special.end())
    // {
    //     special.insert(0);
    // }
    // for (auto it : upd)
    // {
    //     cout << " " << it.first << ":";
    //     for (int connect : it.second)
    //     {
    //         cout << connect << " ";
    //     }
    // }
    up[1][0] = 0, depth[1] = 0;
    depth[0] = -1;
    special_count[0] = 0;
    // if (special.find(1) != special.end())
    //     amt[1] = 1;
    dfs2(1);
    // cout << lca(10, 11);
    // cout << (special.find(11) != special.end());
    // for (int i : depth)
    // {
    //     if (i != 0)
    //     {
    //         cout << i;
    //     }
    // }
    // cout << lca(10, 11);
    // cout << (special.find(10) != special.end());
    // cout << (special.find(11) != special.end());
    // cout << (special.find(up[10][0]) != special.end());
    int power = 0;
    cin >> Q;
    for (int j = 0; j < Q; j++)
    {
        int fr, to;
        cin >> fr >> to;
        int anc = lca(fr, to);
        // ll res = (1 << to_one(fr)) % MOD;
        // res *= (1 << to_one(to)) % MOD;
        // res /= (1 << 2 * to_one(anc)) % MOD;
        // int power = to_one(fr) + to_one(to) - 2 * to_one(anc);
        int power = special_count[fr] + special_count[to] - 2 * special_count[anc];

        // cout << "lca is " << (lca(fr, to)) << "\n";
        if (special.find(anc) != special.end() || (special.find(up[anc][0]) != special.end() && cycle[up[anc][0]].find(anc) != cycle[up[anc][0]].end()))
        {
            power++;
            // res *= 2;
        }
        // int res = (1 << power) % MOD;
        cout << "\n"
             << mod_exp(2, power, MOD) % MOD;
    }

    // for (int s : special)
    // {
    //     cout << "special " << s;
    // }
}
