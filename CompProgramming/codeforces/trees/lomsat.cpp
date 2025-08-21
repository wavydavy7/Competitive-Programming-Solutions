#include <bits/stdc++.h>
#define pb push_back
using namespace std;

#ifdef LOCAL
#include "../../algo/debug.h"
#else
#define debug(...) 42
#endif

 

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> colors(n);
    vector<vector<int>> gr(n);
    vector<map<int, int>> mps(n);
    vector<int> nmost(n);
    vector<long long> sm(n);
    vector<long long> res(n);
    function<void(int, int)>mx = [&](int nd, int p){
        mps[nd][colors[nd]] = 1;
        nmost[nd] = 1;
        sm[nd] = colors[nd];
        for (int i = 0; i < gr[nd].size(); i++){
            if (gr[nd][i] == p) continue; //we get the max for this one
            mx(gr[nd][i], nd);
            if (mps[nd].size() < mps[gr[nd][i]].size()){
                swap(mps[nd], mps[gr[nd][i]]); //so ours is definitely the largest 
                swap(nmost[nd], nmost[gr[nd][i]]);
                swap(sm[nd], sm[gr[nd][i]]);
            }
            for (const auto& [k, v] : mps[gr[nd][i]]){
                mps[nd][k] += v; //for this color
                //I just want to get the smaller set 
                if (mps[nd][k] > nmost[nd]){
                    nmost[nd] = mps[nd][k]; //how many copies
                    sm[nd] = k;
                }
                else if (mps[nd][k] == nmost[nd]){
                    sm[nd] += k; //add the color
                }
            }
        }   
        res[nd] = sm[nd];
    };

    for (int i = 0; i < n; i++){
        int c;
        cin >> c;
        colors[i] = c;
    }
    for (int i = 0; i < n - 1; i++){
        int x, y;
        cin >> x >> y;
        x--, y--;
        gr[x].push_back(y);
        gr[y].push_back(x);
    }
    mx(0, -1);
    //debug(nmost);

    for (int i = 0; i < n; i++){
        cout << res[i];
        if (i != n - 1) cout << " ";
    }
    cout << endl;
    return 0;
}