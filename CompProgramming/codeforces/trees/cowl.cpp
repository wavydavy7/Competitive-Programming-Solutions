#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
const int MX = 7e4 + 50;
#ifdef LOCAL
#include "../../algo/debug.h"
#else
#define debug(...) 42
#endif

// -------------------- fenwick template -------------------- //
template <typename T>
class fenwick {
 public:
  vector<T> fenw;
  int n;
 
  fenwick(int _n) : n(_n) {
    fenw.resize(n);
  }
 
  void modify(int x, T v) {
    while (x < n) {
      fenw[x] += v;
      x |= (x + 1);
    }
  }

  void modify(int x, int y, T v){
    modify(x, v);
    modify(y + 1, -v);
  }
 
  T get(int x) {
    T v{};
    while (x >= 0) {
      v += fenw[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }

  T getr(int x, int y){
    return get(y) - get(x - 1);
  }
};
//fenwick<long long> fenw(n);

int main(){
    ifstream cin("atlarge.in");
    ofstream cout("atlarge.out");
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    //lets center it at root 0
    vector<int> closest(n, MX + 1);
    vector<int> dist(n);
    vector<int> tin(n);
    vector<int> tout(n);
    vector<int> ans(n, 0);
    int time = 0;
    function<int(int, int, int)> dfs = [&](int v, int p, int cnt){
        dist[v] = cnt;
        tin[v] = time++;
        if (adj[v].size() == 1){
            closest[v] = 0;
        }
        for (auto x : adj[v]){
            if (x != p){
                closest[v] = min(closest[v], 1 + dfs(x, v, cnt + 1));
            }
        }
        tout[v] = time;
        return closest[v];
    };

    int sq = sqrt(n);
    int blocks = (n + sq - 1) / sq; //if it's perfect square, it'll stay like that 
    vector<fenwick<int>> trees(blocks, fenwick<int>(2*MX + 1));
    vector<int> val(n);
    vector<int> cont(n);
    function<void(int, int)> dfs2 = [&](int v, int p){
        //now I need to find the shortest distance including the ones from above 
        if (p != -1){
            closest[v] = min(closest[v], closest[p] + 1);
        }
        cont[tin[v]] = 2 - adj[v].size();
        val[tin[v]] = closest[v] - dist[v] + MX;
        trees[tin[v] / sq].modify(val[tin[v]], cont[tin[v]]);
        for (auto x : adj[v]){
            if (x == p) continue;
            dfs2(x, v);
        }

    };
    dfs(0, -1, 0);
    dfs2(0, -1);

    //we want to run some queries
    vector<int> lazy(blocks, 0);
    int above = 0;
    function<void(int, int)> dfs3 = [&](int v, int p){
        //what I want is
        for (int b = 0; b < blocks; b++){
            ans[v] += trees[b].get(MX + above - lazy[b]);
        }
        for (auto x : adj[v]){
            if (x == p) continue;
            int st = tin[x] / sq; 
            int end = (tout[x] - 1) / sq; //which blocks 
            //I want to adjust from beginning the st
            //and then we want everything outside, up until 
            //I need to rebuild the ones here
            if (st == end){
                for (int i = tin[x]; i < tout[x]; i++){
                //all the ones here should decrease by 2
                    trees[st].modify(val[i], -cont[i]);
                    val[i] += 2;
                    trees[st].modify(val[i], cont[i]);
                }
                above++;
                dfs3(x, v);
                above--;
                for (int i = tin[x]; i < tout[x]; i++){
                //all the ones here should decrease by 2
                    trees[st].modify(val[i], -cont[i]);
                    val[i] -= 2;
                    trees[st].modify(val[i], cont[i]);
                }
                continue;
            }
            for (int i = tin[x]; i < (st + 1) * sq; i++){
                //all the ones here should decrease by 2
                trees[st].modify(val[i], -cont[i]);
                val[i] += 2;
                trees[st].modify(val[i], cont[i]);
            }
            for (int i = end * sq; i < tout[x]; i++){
                //all the ones here should decrease by 2
                trees[end].modify(val[i], -cont[i]);
                val[i] += 2;
                trees[end].modify(val[i], cont[i]);
            }
            for (int b = st + 1; b < end; b++){
                lazy[b] += 2;
            }
            above++;
            dfs3(x, v);
            above--;
            for (int i = tin[x]; i < (st + 1) * sq; i++){
                //all the ones here should decrease by 2
                trees[st].modify(val[i], -cont[i]);
                val[i] -= 2;
                trees[st].modify(val[i], cont[i]);
            }
            for (int i = end * sq; i < tout[x]; i++){
                //all the ones here should decrease by 2
                trees[end].modify(val[i], -cont[i]);
                val[i] -= 2;
                trees[end].modify(val[i], cont[i]);
            }
            for (int b = st + 1; b < end; b++){
                lazy[b] -= 2;
            }
            //once you finish, you need to undo those changes
        }
    };
    //we have the closest
    dfs3(0, -1);
    for (int i = 0; i < ans.size(); i++){
        if (adj[i].size() == 1)
            ans[i] = 1;
        cout << ans[i] << endl;
    }
}