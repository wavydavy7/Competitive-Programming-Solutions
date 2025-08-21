#include <bits/stdc++.h>
// #include "debug.h"
#define ll long long
#define pb push_back
using namespace std;

int main(){
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector<vector<int>> tr(n + 1);
        for (int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u--, v--;
            tr[u].pb(v);
            tr[v].pb(u);
        }
        int lf = 0;
        int twos = 0;
        vector<int> d(n, 0);
        for (int i = 0; i < n; i++){
            if (tr[i].size() == 1) {
                lf++;
                continue;
            }
            for (auto nei : tr[i]){
                if (tr[nei].size() != 1) { //if the above doesn't have more than one kid, place there 
                    d[i]++; //how many nonleafs
                }
            }
            if (d[i] == tr[i].size()) twos++;
        }
        //if p cannot be next to a leaf or a leaf 
        //q must be a leaf
        ll total = 1ll * lf * (n - lf); //when one is a lf, and the other one isn't a lf
        for (int i = 0; i < n; i++){
            if (tr[i].size() > 1 && d[i] != tr[i].size()) total += 1ll * twos * (d[i] - 1); 
        }
        if (n == 2) cout << 0 << endl;
        else cout << total << endl;
    }
}