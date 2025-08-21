#include <bits/stdc++.h>
#define pb push_back
using namespace std;

#ifdef LOCAL
#include "../../algo/debug.h"
#else
#define debug(...) 42
#endif

int main(){
    int n;
    cin >> n;
    vector<int> a(n, -1);
    int sq = (int) sqrt(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int q;
    cin >> q;
    vector<pair<int, int>> qs(q); //tells me what queries there are 
    for (int i = 0; i < q; i++){
        int ap, b;
        cin >> ap >> b;
        ap--, b--;
        qs[i] = {ap, b};
    }
    auto mosort = [&](int ap, int b){
        int b1 = qs[ap].first / sq;
        int b2 = qs[b].first / sq;
        if (b1 == b2) {
            return qs[ap].second < qs[b].second;
        }
        else{
            return (qs[ap].first / sq) < (qs[b].first / sq);
        }
    };
    int bl = -1;
    int beg = -1;
    int to = -1;
    unordered_map<int, int> mp;
    int res = 0;
    vector<int> qss(q);
    iota(qss.begin(), qss.end(), 0);
    sort(qss.begin(), qss.end(), mosort);
    auto reset = [&](int b){
        to = -1;
        bl = b;
        beg = -1;
        res = 0;
        mp.clear();
    };
    vector<int> ans(q);

    for (int i = 0; i < q; i++){
        int query = qss[i];
        pair<int, int> ql = qs[query];
        //we want to check if they are in the same block 
        if (bl != ql.first / sq){
            //we have to process some queries 
            reset(ql.first / sq);
            beg = ql.first;
            to = ql.second;
            for (int j = ql.first; j <= ql.second; j++){
                mp[a[j]]++;
                if (mp[a[j]] == 1){
                    res++;
                }
            } //I'm just gonna store the inclusive values in range
        }
        else{
            //looking at the same block
            while (to < ql.second){
                to++;
                mp[a[to]]++;
                if (mp[a[to]] == 1){
                    res++;
                }
            }
            while (beg < ql.first){
                mp[a[beg]]--;;
                if (mp[a[beg]] == 0){
                    res--;
                }
                beg++;
            }
            while (beg > ql.first){
                beg--;
                mp[a[beg]]++;
                if (mp[a[beg]] == 1){
                    res++;
                }
            }
        }
        ans[query] = res; 
        //debug(mp);
    }
    for (int j = 0; j < q; j++){
        cout << ans[j];
        if (j != q-1) cout << "\n";
    }
}